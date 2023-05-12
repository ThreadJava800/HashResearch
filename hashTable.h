#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <immintrin.h>

#include <chrono>

#include "LinkedList/list.h"

#define MAKE_CHECKS 0

typedef unsigned char uchar;
typedef size_t (*HashFunc_t)(const char *string);

//=========CONSTANT SECTION==========
const size_t POISON_HASH          = 0xDEADBEEF;
const size_t DEFAULT_GNU_HASH     = 0xDED;
const size_t DEFAULT_ARR_SIZE     = 127;
const int    SEARCH_TEST_CNT      = 1e5;

static const int   HASH_COUNT     = 6;
static const int   MAX_WORD_LEN   = 100;
static const int   WORD_COUNT     = 251171;
static const char *dictionaryFile = "data/cleaned.txt";
//===================================

struct HashMap_t {
    List_t *listArr     = nullptr;
    size_t  listCnt     = 0;

    HashFunc_t hashFunc = nullptr;
};
//===========HASH MAP FUNCS=============
HashMap_t  *hashMapCtor  (HashFunc_t hashFunc);
void        hashMapInsert(HashMap_t *hashMap, const char *key, const char *value);
const char *hashMapSearch(HashMap_t *hashMap, const char *key);
void        hashMapDtor  (HashMap_t *hashMap);
//======================================

uint64_t rotr(uint64_t value);  // rotate byte right
uint64_t rotl(uint64_t value);  // rotate byte left

int myStrcmpAVX(const char *string1, const char *string2, long strlen1, long strlen2);

//==========HASH FUNCTIONS============
uint64_t numberHash(const char *string);
uint64_t asciiHash (const char *string);
uint64_t lenHash   (const char *string);
uint64_t rotrHash  (const char *string);
uint64_t rotlHash  (const char *string);
uint64_t gnuHash   (const char *string);

//==========TESTING==========
HashMap_t *fillHashMap(HashFunc_t hashFunc);
void countDeviation(HashMap_t *hashMapArr[HASH_COUNT]);
void measureHashDistribution();
void shuffleArray(const char **arr, size_t arrSize);
void measureHashMapFind();


#if MAKE_CHECKS
#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}                                                             \

#else
#define ON_ERROR(expr, errStr, retVal) {}
#endif