#include "hashTable.h"

int main() {
    const char *test = "intrinsics";
    size_t result = gnuHash(test);

    printf("%lld\n", result);

    return 0;
}