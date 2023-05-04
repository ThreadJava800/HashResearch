#include <chrono>

typedef uint64_t (*TestFunc_t)(const char *string);

double medianTime(TestFunc_t func, const char *string, int repeatCount) {
    double allTime = 0;
    auto start = std::chrono::high_resolution_clock::now(); 
    for (int i = 0; i < repeatCount; i++) {
        func(string);
    }
    auto end   = std::chrono::high_resolution_clock::now(); 
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    allTime += duration.count();

    return allTime;
}