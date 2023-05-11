#include "hashTable.h"

HashMap_t *parseFile(HashFunc_t hashFunc) {
    HashMap_t *hashMap = hashMapCtor(hashFunc);

    FILE *file = fopen(dictionaryFile, "rb");
    ON_ERROR(!file, "Couldn't open file",);

    char *keyLine   = nullptr;
    char *valueLine = nullptr;
    size_t lineLen  = 0;
    
    // get eng word
    while (getline(&keyLine, &lineLen, file) != -1) {
        // get rus word
        getline(&valueLine, &lineLen, file);
        hashMapInsert(hashMap, keyLine, valueLine);
    }
    fclose(file);

    return hashMap;
}

void countDeviation(HashMap_t *hashMapArr[HASH_COUNT]) {
    double median = 0;
    double deviations[HASH_COUNT] = {};

    // count median
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        median += hashMapArr[0]->listArr[i].size;
    }
    median /= DEFAULT_ARR_SIZE;

    // count deviation
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < HASH_COUNT; j++) {
            deviations[j] += (hashMapArr[j]->listArr[i].size - median) * 
                                                (hashMapArr[j]->listArr[i].size - median);
        }
    }

    // print deviations and median for each hashMap
    for (int i = 0; i < HASH_COUNT; i++) {
        deviations[i] /= DEFAULT_ARR_SIZE;
        printf("%lf %lf\n", sqrt(deviations[i]), median);

        hashMapDtor(hashMapArr[i]);
    }
}

void testHashes() {
    HashMap_t *hashMaps[HASH_COUNT]   = {};

    // pushing words to lists
    hashMaps[0] = parseFile(numberHash);
    hashMaps[1] = parseFile(asciiHash);
    hashMaps[2] = parseFile(lenHash);
    hashMaps[3] = parseFile(rotrHash);
    hashMaps[4] = parseFile(rotlHash);
    hashMaps[5] = parseFile(gnuHash);

    // printing results
    FILE *file = fopen("hashTests.csv", "wb");
    fprintf(file, "NUMBER,ASCII,LENGTH,ROTR,ROTL,GNU\n");

    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < HASH_COUNT; j++) {
            fprintf(file, "%ld,", hashMaps[j]->listArr->size);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    countDeviation(hashMaps);
} 

void stressTest() {
    srand((unsigned) time(NULL));

    HashMap_t *hashMap = parseFile(rotlHash);
    const char **strArr = (const char **) calloc(WORD_COUNT, sizeof(const char *));

    // getting keys
    int wordCnt = 0;
    for (int i = 0; i < hashMap->listCnt; i++) {
        for (int j = 0; j < hashMap->listArr[i].size; j++) {
            Pair_t checkPair  = listGet(&(hashMap->listArr[i]), j);
            strArr[wordCnt++] = checkPair.key;
        }
    }

    auto start = std::chrono::high_resolution_clock::now(); 
    for (int i = 0;  i < (int) 1e5; i++) {
        int index = rand() % WORD_COUNT;
        hashMapSearch(hashMap, strArr[index]);
    }
    auto end      = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("%lld\n", duration.count());
}
