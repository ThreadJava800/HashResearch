#include "hashTable.h"

HashMap_t *hashMapCtor(HashFunc_t hashFunc) {
    ON_ERROR(!hashFunc, "HashFunc pointer was NULL", nullptr);

    HashMap_t *hashMap = (HashMap_t*) calloc(1, sizeof(HashMap_t));
    ON_ERROR(!hashMap, "Unable to alloc memory", nullptr);

    List_t *listArr = (List_t *) calloc(DEFAULT_ARR_SIZE, sizeof(List_t));
    ON_ERROR(!listArr,"Unable to alloc memory", nullptr);

    for (size_t i = 0; i < DEFAULT_ARR_SIZE; i++) {
        _listCtor(&listArr[i], WORD_COUNT, 0);
    }

    hashMap->listArr  = listArr;
    hashMap->hashFunc = hashFunc;
    hashMap->listCnt  = DEFAULT_ARR_SIZE;

    return hashMap;    
}

void hashMapInsert(HashMap_t *hashMap, const char *key, const char *value) {
    ON_ERROR(!hashMap || !key || !value, "Nullptr",);

    size_t hashSum = hashMap->hashFunc(key) % hashMap->listCnt;
    
    Pair_t addPair = {
        .key       = strdup(key),
        .value     = strdup(value),
        .keyLength = strlen(key)
    };
    listPushBack(&(hashMap->listArr[hashSum]), addPair);
}

int myStrcmpAVX(const char *string1, const char *string2, long strlen1, long strlen2) {
    ON_ERROR(!string1 || !string2, "Nullptr", -1);

    if (strlen1 != strlen2) return -1;

    int pos = 0;
    for (; pos < strlen1 - 32; pos += 32) {
        __m256i str1 = _mm256_set_epi8(
            string1[pos + 31], string1[pos + 30], string1[pos + 29], string1[pos + 28],
            string1[pos + 27], string1[pos + 26], string1[pos + 25], string1[pos + 24],
            string1[pos + 23], string1[pos + 22], string1[pos + 21], string1[pos + 20],
            string1[pos + 19], string1[pos + 18], string1[pos + 17], string1[pos + 16],
            string1[pos + 15], string1[pos + 14], string1[pos + 13], string1[pos + 12],
            string1[pos + 11], string1[pos + 10], string1[pos + 9],  string1[pos + 8],
            string1[pos + 7],  string1[pos + 6],  string1[pos + 5],  string1[pos + 4],
            string1[pos + 3],  string1[pos + 2],  string1[pos + 1],  string1[pos]
        );

        __m256i str2 = _mm256_set_epi8(
            string2[pos + 31], string2[pos + 30], string2[pos + 29], string2[pos + 28],
            string2[pos + 27], string2[pos + 26], string2[pos + 25], string2[pos + 24],
            string2[pos + 23], string2[pos + 22], string2[pos + 21], string2[pos + 20],
            string2[pos + 19], string2[pos + 18], string2[pos + 17], string2[pos + 16],
            string2[pos + 15], string2[pos + 14], string2[pos + 13], string2[pos + 12],
            string2[pos + 11], string2[pos + 10], string2[pos + 9],  string2[pos + 8],
            string2[pos + 7],  string2[pos + 6],  string2[pos + 5],  string2[pos + 4],
            string2[pos + 3],  string2[pos + 2],  string2[pos + 1],  string2[pos]
        );

        int cmpMask = _mm256_extract_epi32(_mm256_cmpeq_epi8(str1, str2), 0);
        if (cmpMask != 0xFFFFFFFF) return -1;
    }

    for (; pos < strlen1; pos++) {
        if (string1[pos] < string2[pos]) return -1;
        if (string1[pos] > string2[pos]) return  1;
    }

    return 0;
}

bool comparator(Elem_t val1, Elem_t val2) {
    if (!myStrcmpAVX(val1.key, val2.key, val1.keyLength, val2.keyLength)) {
        return true;
    }
    return false;
}

const char *hashMapSearch(HashMap_t *hashMap, const char *key) {
    ON_ERROR(!hashMap || !(hashMap->data) || !key, "Nullptr", nullptr);

    size_t  hashSum    = hashMap->hashFunc(key) % hashMap->listCnt;
    List_t  searchList = hashMap->listArr[hashSum];

    Elem_t compareElement = {
        .key = key,
        .keyLength = (size_t) strlen(key)
    };

    return listFind(&searchList, compareElement, comparator)->value.value;
}

void hashMapDtor(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);
    ON_ERROR(!hashMap->data, "Nullptr",);

    for (size_t i = 0; i < hashMap->listCnt; i++) {
        List_t listToFree = hashMap->listArr[i];

        for (size_t j = 0; j < listToFree.size; j++) {
            free((char*) listToFree.values[j].value.key);
            free((char*) listToFree.values[j].value.value);
        }

        listDtor(&listToFree);
    }

    free(hashMap->listArr);
    free(hashMap);
}