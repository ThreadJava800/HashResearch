#include "hashTable.h"

HashMap_t *HashMap::ctor(HashFunc_t hashFunc) {
    HashMap_t *hashMap = (HashMap_t*) calloc(1, sizeof(HashMap_t));
    ON_ERROR(!hashMap, "Unable to alloc memory", nullptr);

    List_t **listArr = (List_t **) calloc(DEFAULT_ARR_SIZE, sizeof(List_t*));
    ON_ERROR(!listArr,"Unable to alloc memory", nullptr);

    for (size_t i = 0; i < DEFAULT_ARR_SIZE; i++) {
        listArr[i] = (List_t *) calloc(1, sizeof(List_t));
        ON_ERROR(!(listArr[i]), "Unable to alloc memory", nullptr);

        int ctorErr = 0;
        _listCtor(listArr[i], WORD_COUNT, 0, &ctorErr);
    }

    hashMap->data     = listArr;
    hashMap->hashFunc = hashFunc;
    hashMap->capacity = DEFAULT_ARR_SIZE;

    return hashMap;    
}

void HashMap::insert(HashMap_t *hashMap, const char *key, const char *value) {
    ON_ERROR(!hashMap || !key || !value, "Nullptr",);

    size_t hashSum = hashMap->hashFunc(key) % DEFAULT_ARR_SIZE;

    Pair_t addPair = {
        .key   = strdup(key),
        .value = strdup(value)
    };
    listPushBack(hashMap->data[hashSum], addPair);
}

int mstrcmp(const char *string1, const char *string2) {
    ON_ERROR(!string1 || !string2, "Nullptr", -1);

    while (string1 && string2)
    {
        if (*string1 < *string2) return -1;
        if (*string1 > *string2) return  1;

        string1++;
        string2++;
    }

    if (!string1) {
        if (!string2) return 0;
        return -1;
    }
    
    // else (string1 && !string2)
    return 1;
}

const char *HashMap::search(HashMap_t *hashMap, const char *key) {
    ON_ERROR(!hashMap || !(hashMap->data) || !key, "Nullptr", nullptr);

    size_t  hashSum    = hashMap->hashFunc(key) % DEFAULT_ARR_SIZE;
    List_t *searchList = hashMap->data[hashSum];

    for (long i = 0; i < searchList->size; i++) {
        Pair_t checkPair = listGet(searchList, i);
        if (!strcmp(key, checkPair.key)) {
            return checkPair.value;
        }
    }

    return nullptr;
}

void HashMap::dtor(HashMap_t *hashMap) {
    ON_ERROR(!hashMap, "Nullptr",);
    ON_ERROR(!hashMap->data, "Nullptr",);

    for (size_t i = 0; i < DEFAULT_ARR_SIZE; i++) {
        ON_ERROR(!hashMap->data[i], "Nullptr",);

        free(hashMap->data[i]);
    }

    free(hashMap->data);
    free(hashMap);
}