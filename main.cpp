#include "hashTable.h"
#include <chrono>

int main() {
    // HashMap_t *hashMap = HashMap::ctor(rotlHash);
    // HashMap::insert(hashMap, "test", "me");
    // HashMap::dtor(hashMap);

    // testHashes();

    // HashMap_t *hashMap = parseFile(rotlHash);
    // const char *value = HashMap::search(hashMap, "I asked Tom where he had been.\n");
    // if (value) printf("%s\n", value);
    // else       printf("NULL\n");
    
    // auto start = std::chrono::high_resolution_clock::now(); 
    // stressTest();
    // auto end   = std::chrono::high_resolution_clock::now(); 

    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // printf("%lld\n", duration.count());

    printf("%d\n", mstrcmp2("Tom lost so much weight that one of his friends walked straight past him in the street, without recognising him.", 112, "Tom lost so much weight that one of his friends walked straight past him in the street, without recognising him.", 112));

    return 0;
}