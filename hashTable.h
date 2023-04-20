#include <stdio.h>
#include <malloc.h>

#include "ClassicList/list.h"

typedef unsigned char uchar;
typedef size_t (*HashFunc_t)(const char *string);

const size_t POISON_HASH      = 0xDEADBEEF;
const size_t DEFAULT_GNU_HASH = 0xDED;
const size_t DEFAULT_ARR_SIZE = 100;

struct HashMap_t {
    List_t **data       = nullptr;

    size_t capacity     = 0;
    HashFunc_t hashFunc = nullptr;
};
//===========HASH MAP FUNCS=============
namespace HashMap {
    HashMap_t *ctor  (HashFunc_t hashFunc);
    void       insert(HashMap_t *hashMap, const char *key, const char *value);
    void       dtor  (HashMap_t *hashMap);
};

//==========HASH FUNCTIONS============
uchar rotr(uchar value);
uchar rotl(uchar value);

size_t numberHash(const char *string);
size_t asciiHash (const char *string);
size_t lenHash   (const char *string);
size_t rotrHash  (const char *string);
size_t rotlHash  (const char *string);
size_t gnuHash   (const char *string);


#define ON_ERROR(expr, errStr, retVal) {                 \
    if (expr) {                                           \
        fprintf(stderr, "FATAL ERROR: %s\n", errStr);      \
        return retVal;                                      \
    }                                                        \
}                                                             \
