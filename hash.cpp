#include "hashTable.h"

uchar rotr(uchar value) {
    return (value >> 1) | (value << 7);
}

uchar rotl(uchar value) {
    return (value << 1) | (value >> 7);
}

size_t numberHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    return 1;
}

size_t asciiHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    return (size_t) string[0];
}

size_t lenHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    size_t length = 0;
    while (*string != '\0')
    {
        length++;
        string++;
    }
    
    return length;
}

size_t rotrHash  (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uchar prevHash = rotr(*string);
    string++;

    size_t resultHash = prevHash;

    while (*string != '\0')
    {
        prevHash    = rotr(prevHash) ^ (*string);
        resultHash += prevHash;

        string++;
    }
    
    return resultHash;
}

size_t rotlHash  (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uchar prevHash = rotl(*string);
    string++;

    size_t resultHash = prevHash;

    while (*string != '\0')
    {
        prevHash    = rotl(prevHash) ^ (*string);
        resultHash += prevHash;

        string++;
    }
    
    return resultHash;
}

size_t gnuHash   (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    size_t hash = DEFAULT_GNU_HASH;

    while (*string != '\0')
    {
        hash = hash * 3 + (size_t) *string;

        string++;
    }

    return hash;
}