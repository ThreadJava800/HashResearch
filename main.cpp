#include "hashTable.h"
#include "measure.hpp"

int main() {
    // HashMap_t *hashMap = HashMap::ctor(rotlHash);
    // HashMap::insert(hashMap, "test", "me");
    // HashMap::dtor(hashMap);

    // testHashes();

    const char *str = "Doubtless there exists in this world precisely the right woman for any given man to marry and vice versa; but when you consider that a human being has the opportunity of being acquainted with only a few hundred people, and out of the few hundred that there are but a dozen or less whom he knows intimately, and out of the dozen, one or two friends at most, it will easily be seen, when we remember the number of millions who inhabit this world, that probably, since the earth was created, the right man has never yet met the right woman.";

    double res = medianTime(rotlHash, str, 1e6);
    printf("%lf\n", res);

    // HashMap_t *hashMap = parseFile(rotlHash);
    // const char *value = HashMap::search(hashMap, "I asked Tom where he had been.\n");
    // if (value) printf("%s\n", value);
    // else       printf("NULL\n");
    
    // stressTest();


    // double allTime = 0;
    // auto start = std::chrono::high_resolution_clock::now(); 
    // for (long i = 0; i < 10000000; i++) {
    //     mstrcmp2("Doubtless there exists in this world precisely the right woman for any given man to marry and vice versa; but when you consider that a human being has the opportunity of being acquainted with only a few hundred people, and out of the few hundred that there are but a dozen or less whom he knows intimately, and out of the dozen, one or two friends at most, it will easily be seen, when we remember the number of millions who inhabit this world, that probably, since the earth was created, the right man has never yet met the right woman.", 539,
    //     "Doubtless there exists in this world precisely the right woman for any given man to marry and vice versa; but when you consider that a human being has the opportunity of being acquainted with only a few hundred people, and out of the few hundred that there are but a dozen or less whom he knows intimately, and out of the dozen, one or two friends at most, it will easily be seen, when we remember the number of millions who inhabit this world, that probably, since the earth was created, the right man has never yet met the right woman.", 539);
    // }
    // auto end   = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // printf("%d\n", mstrcmp("test", "tetst"));

    return 0;
}