#include "hashTable.h"

HashMap_t *createHashMapFromFile(HashFunc_t hashFunc) {
    HashMap_t *hashMap = hashMapNew(hashFunc);

    FILE *file = fopen(DICTIONARY_FILE, "r");
    ON_ERROR(!file, "Couldn't open file", nullptr);

    char *keyLine   = NULL;
    char *valueLine = NULL;
    size_t lineLen  = 0;
    
    int count = 0;

    // get eng word
    while (getline(&keyLine, &lineLen, file) != -1) {
        // get rus word
        getline(&valueLine, &lineLen, file);
        hashMapInsert(hashMap, keyLine, valueLine);

        free(keyLine);
        free(valueLine);
        keyLine = NULL;
        valueLine = NULL;
    }
    free(keyLine);
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
    }
}

void measureHashDistribution() {
    HashMap_t *hashMaps[HASH_COUNT]   = {};

    // pushing words to lists
    hashMaps[0] = createHashMapFromFile(numberHash);
    hashMaps[1] = createHashMapFromFile(asciiHash);
    hashMaps[2] = createHashMapFromFile(lenHash);
    hashMaps[3] = createHashMapFromFile(rotrHash);
    hashMaps[4] = createHashMapFromFile(rotlHash);
    hashMaps[5] = createHashMapFromFile(gnuHash);

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

    // delete hashMaps
    for (int i = 0; i < HASH_COUNT; i++) {
        hashMapDelete(hashMaps[i]);
    }
} 

void shuffleArray(const char **arr, size_t arrSize) {
    ON_ERROR(!arr, "Nullptr",);

    for (size_t i = 0; i < arrSize; i++) {
        int replIndex = i + rand() % (arrSize - i);

        const char *temp = arr[i];
        arr[i] = arr[replIndex];   // random element after i
        arr[replIndex] = temp;
    }
}

void measureHashMapFindTime() {
    srand((unsigned) time(NULL));

    HashMap_t   *hashMap = createHashMapFromFile(rotlHash);
    const char **strArr  = (const char **) calloc(WORD_COUNT, sizeof(const char *));
    ON_ERROR(!strArr, "Nullptr", );

    // getting keys
    int wordCnt = 0;
    for (int i = 0; i < hashMap->listCnt; i++) {
        for (int j = 0; j < hashMap->listArr[i].size; j++) {
            Pair_t checkPair  = listGet(&(hashMap->listArr[i]), j);
            strArr[wordCnt++] = checkPair.key;
        }
    }

    shuffleArray(strArr, WORD_COUNT);

    auto start = std::chrono::high_resolution_clock::now(); 
    for (int i = 0;  i < SEARCH_TEST_CNT; i++) {
        hashMapSearch(hashMap, strArr[i]);
    }
    auto end      = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("%lld\n", duration.count());

    free(strArr);
    hashMapDelete(hashMap);
}
