#include <chrono>

typedef int (*TestFunc_t)(const char *string1, long int len1, const char *string2, long int len2);

double medianTime(TestFunc_t func, const char *string1, size_t len1, const char *string2, size_t len2, int repeatCount) {
    double allTime = 0;
    auto start = std::chrono::high_resolution_clock::now(); 
    for (int i = 0; i < repeatCount; i++) {
        func(string1, len1, string2, len2);
    }
    auto end   = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    allTime += duration.count();

    return allTime;
}