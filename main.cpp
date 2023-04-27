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

    double allTime = 0;
    auto start = std::chrono::high_resolution_clock::now(); 
    for (long i = 0; i < 1000000000; i++) {
        rotlHash("I asked Tom where he had been.\n");
    }
    auto end   = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    printf("%lld\n", duration.count());

    return 0;
}