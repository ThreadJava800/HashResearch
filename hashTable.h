#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <immintrin.h>

#include <chrono>

#include "LinkedList/list.h"

#define MAKE_CHECKS 0

typedef unsigned char uchar;
typedef size_t (*HashFunc_t)(const char *string);

const size_t POISON_HASH      = 0xDEADBEEF;
const size_t DEFAULT_GNU_HASH = 0xDED;
const size_t DEFAULT_ARR_SIZE = 127;

static const int MAX_WORD_LEN = 100;
static const int WORD_COUNT = 250948;
static const char *dictionaryFile = "data/cleaned.txt";

struct HashMap_t {
    List_t **data       = nullptr;

    size_t capacity     = 0;
    HashFunc_t hashFunc = nullptr;
};
//===========HASH MAP FUNCS=============
long mstrlen(const char *string);
int mstrcmp(const char *string1, const char *string2);
int mstrcmp2(const char *string1, long strlen1, const char *string2, long strlen2);

namespace HashMap {
    HashMap_t  *ctor  (HashFunc_t hashFunc);
    void        insert(HashMap_t *hashMap, const char *key, const char *value);
    const char *search(HashMap_t *hashMap, const char *key);
    void        dtor  (HashMap_t *hashMap);
};

//==========HASH FUNCTIONS============
uint64_t rotr(uint64_t value);
uint64_t rotl(uint64_t value);

static const int HASH_COUNT = 6;

uint64_t numberHash(const char *string);
uint64_t asciiHash (const char *string);
uint64_t lenHash   (const char *string);
uint64_t rotrHash  (const char *string);
uint64_t rotlHash  (const char *string);
uint64_t gnuHash   (const char *string);

//==========TESTING==========
HashMap_t *parseFile(HashFunc_t hashFunc);
void testHashes();
void stressTest();


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