#include "hashTable.h"

uint64_t rotr(uint64_t value) {
    return (value >> 1) | (value << 63);
}

uint64_t rotl(uint64_t value) {
    return (value << 1) | (value >> 63);
}

uint64_t numberHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    return 1;
}

uint64_t asciiHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    return (uint64_t) string[0];
}

uint64_t lenHash (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uint64_t length = 0;
    while (*string != '\0')
    {
        length++;
        string++;
    }
    
    return length;
}

uint64_t rotrHash  (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uint64_t hash = 0;

    while (*string != '\0')
    {
        hash = rotr(hash) ^ (*string);

        string++;
    }
    
    return hash;
}

uint64_t rotlHash  (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uint64_t hash = 0;

    while (*string != '\0')
    {
        hash = rotl(hash) ^ ((uint64_t) (*string));

        string++;
    }
    
    return hash;
}

uint64_t gnuHash   (const char *string) {
    ON_ERROR(!string, "Nullptr", POISON_HASH);

    uint64_t hash = DEFAULT_GNU_HASH;

    while (*string != '\0')
    {
        hash = hash * 3 + (uint64_t) *string;

        string++;
    }

    return hash;
}