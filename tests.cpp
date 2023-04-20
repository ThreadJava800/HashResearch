#include "hashTable.h"

HashMap_t *parseFile(HashFunc_t hashFunc) {
    HashMap_t *hashMap = HashMap::ctor(hashFunc);

    FILE *file = fopen(dictionaryFile, "rb");
    ON_ERROR(!file, "Couldn't open file",);

    char *keyLine   = nullptr;
    char *valueLine = nullptr;
    size_t lineLen  = 0;
    
    // get eng word
    while (getline(&keyLine, &lineLen, file) != -1) {
        // get rus word
        getline(&valueLine, &lineLen, file);

        // push into each hashMap
        for (int i = 0; i < HASH_COUNT; i++) {
            HashMap::insert(hashMap, keyLine, valueLine);
        }
    }
    fclose(file);

    return hashMap;
}

void testHashes() {
    HashMap_t *hashMaps[HASH_COUNT] = {};
    double    *deviations = (double*) calloc(HASH_COUNT, sizeof(long));

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

    double median = 0;
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < HASH_COUNT; j++) {
            fprintf(file, "%ld,", hashMaps[j]->data[i]->size);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    // count median
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        median += hashMaps[0]->data[i]->size;
    }
    median /= DEFAULT_ARR_SIZE;

    // count deviation
    for (int i = 0; i < DEFAULT_ARR_SIZE; i++) {
        for (int j = 0; j < HASH_COUNT; j++) {
            deviations[j] += (hashMaps[j]->data[i]->size - median) * (hashMaps[j]->data[i]->size - median);
        }
    }

    for (int i = 0; i < HASH_COUNT; i++) {
        deviations[i] /= DEFAULT_ARR_SIZE;
        printf("%lf %lf\n", sqrt(deviations[i]), median);

        HashMap::dtor(hashMaps[i]);
    }

    free(deviations);
} 