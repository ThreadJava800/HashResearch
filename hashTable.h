#include <stdio.h>

typedef unsigned char uchar;

const size_t POISON_HASH      = 0xDEADBEEF;
const size_t DEFAULT_GNU_HASH = 0xDED;

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
