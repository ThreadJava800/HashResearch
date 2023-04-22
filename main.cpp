#include "hashTable.h"

int main() {
    // HashMap_t *hashMap = HashMap::ctor(rotlHash);
    // HashMap::insert(hashMap, "test", "me");
    // HashMap::dtor(hashMap);

    // testHashes();

    HashMap_t *hashMap = parseFile(rotlHash);
    const char *value = HashMap::search(hashMap, "I asked Tom where he had been.\n");
    if (value) printf("%s\n", value);
    else       printf("NULL\n");

    // stressTest();

    return 0;
}