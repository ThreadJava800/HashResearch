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
        .key       = strdup(key),
        .value     = strdup(value),
        .keyLength = strlen(key)
    };
    listPushBack(hashMap->data[hashSum], addPair);
}

long mstrlen(const char *string) {
    ON_ERROR(!string, "Nullptr", -1);

    long strLen = 0;
    while (*string != '\0') {
        strLen++;
        string++;
    }

    return strLen;
}

// long mstrlen(const char *string) {
//     ON_ERROR(!string, "Nullptr", -1);

//     __asm__(
//     ".intel_syntax noprefix\n"

//         "\txor rax, rax\n"
//         "\tcmp BYTE PTR [rdi], 0\n"
//         "\tje .leave\n"

//     ".mstrloop:\n"
//         "\tinc rax\n"
//         "\tcmp BYTE PTR [rdi + rax], 0\n"
//         "\tjne .mstrloop\n"

//     ".leave:\n"
//         "\tret\n"

//     ".att_syntax prefix\n"
//     );
// }

// search with inline assembly
// int mstrcmp(const char *string1, const char *string2) {
//     ON_ERROR(!string1 || !string2, "Nullptr", -1);

//     __asm__ (
//         ".intel_syntax noprefix\n"

//         "\txor eax, eax\n"
//         "\txor ecx, ecx\n"
//     "\t_loop:\n"
//         "\tmovb al, BYTE PTR [rdi]\n"
//         "\tmovb cl, BYTE PTR [rsi]\n"

//         "\tcmp al, 0\n"
//         "\tje _retNeg\n"

//         "\tcmp cl, 0\n"
//         "\tje _ret1\n"

//         "\tcmp al, cl\n"
//         "\tjne _default_ret\n"

//         "\tinc rsi\n"
//         "\tinc rdi\n"

//         "\tjmp _loop\n"

// "\t_ret0:\n"
//         "\tmov eax, 0\n"
//         "\tpop rbp\n"
//         "\tret\n"

// "\t_ret1:\n"
//         "\tcmp al, cl\n"
//         "\tje _ret0\n"

//         "\tmov eax, 1\n"
//         "\tpop rbp\n"
//         "\tret\n"
        
// "\t_retNeg:\n"
//         "\tcmp al, cl\n"
//         "\tje _ret0\n"

//         "\tmov eax, 1\n"
//         "\tpop rbp\n"
//         "\tret\n"

// "\t_default_ret:\n"
//         "\tsub eax, ecx\n"
//         "\tret\n"

//         ".att_syntax prefix\n"
//     );
// }

int mstrcmp2(const char *string1, long strlen1, const char *string2, long strlen2) {
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

// naive strcmp
// int mstrcmp(const char *string1, const char *string2) {
//     ON_ERROR(!string1 || !string2, "Nullptr", -1);

//     while (*string1 != '\0' && *string2 != '\0')
//     {
//         if (*string1 < *string2) return -1;
//         if (*string1 > *string2) return  1;

//         string1++;
//         string2++;
//     }

//     if (*string1 == '\0') {
//         if (*string2 == '\0') return 0;
//         return -1;
//     }
    
//     // else (string1 && !string2)
//     return 1;
// }


// naive search
const char *HashMap::search(HashMap_t *hashMap, const char *key) {
    ON_ERROR(!hashMap || !(hashMap->data) || !key, "Nullptr", nullptr);

    size_t  hashSum    = hashMap->hashFunc(key) % DEFAULT_ARR_SIZE;
    List_t *searchList = hashMap->data[hashSum];
    long    keyLength  = strlen(key);

    for (long i = 0; i < searchList->size; i++) {
        Pair_t checkPair = listGet(searchList, i);
        if (!mstrcmp2(key, keyLength, checkPair.key, checkPair.keyLength)) {
            return checkPair.value;
        }
    }

    return nullptr;
}

// const char *HashMap::search(HashMap_t *hashMap, const char *key) {
//     ON_ERROR(!hashMap || !(hashMap->data) || !key, "Nullptr", nullptr);

//     size_t  hashSum    = hashMap->hashFunc(key) % DEFAULT_ARR_SIZE;
//     List_t *searchList = hashMap->data[hashSum];
//     long    listSize   = searchList->size;

//     for (long i = 0; i < listSize - 32; i += 32) {
//         Pair_t pairs[32] = {};

//         for (int j = 0; j < 32; j++) {
//             pairs[j] = listGet(searchList, i + j);
//         }

//         for (int m = 0; m < MAX_WORD_LEN; m++) {
//             char mPosLetters[32] = {};
//             for (int j = 0; j < 32; j++) {
//                 if (pairs[j].keyLength > m) mPosLetters[j] = 0;
//                 else                        mPosLetters[j] = pairs[j].key[m];
//             }

//             __m256i hashStrings = _mm256_set_epi8(
//                 mPosLetters[31], mPosLetters[30], mPosLetters[29], mPosLetters[28],
//                 mPosLetters[27], mPosLetters[26], mPosLetters[25], mPosLetters[24],
//                 mPosLetters[23], mPosLetters[22], mPosLetters[21], mPosLetters[20],
//                 mPosLetters[19], mPosLetters[18], mPosLetters[17], mPosLetters[16],
//                 mPosLetters[15], mPosLetters[14], mPosLetters[13], mPosLetters[12],
//                 mPosLetters[11], mPosLetters[10], mPosLetters[9],  mPosLetters[8],
//                 mPosLetters[7],  mPosLetters[6],  mPosLetters[5],  mPosLetters[4],
//                 mPosLetters[3],  mPosLetters[2],  mPosLetters[1],  mPosLetters[0]
//             );


//         }
//     }

//     for (long i = listSize - 32; i < listSize; i++) {
//         Pair_t checkPair = listGet(searchList, i);
//         if (!mstrcmp(key, checkPair.key)) {
//             return checkPair.value;
//         }
//     }

//     return nullptr;
// }

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