#include "Taylor.h"
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <functional>
#include <iostream>

using namespace std;

int main() {
    int n = 5;
    thread threadArray[n];
    long double results[n];
    Taylor taylor;
    long double x = 1500000;
    int from = 0;
    int increment = 10000000 / n; 
    for (int i = 0; i <n; i++) {
        threadArray[i] = thread(&Taylor::calculateTerms, &taylor, from, from + increment, x, ref(results[i]));
        from = from + increment;    
    }

    for (int i = 0; i <n; i++) {
        if (threadArray[i].joinable() == true) {
            threadArray[i].join();
        }
    }

    long double finalRes = 0;
    for (int i = 0; i < n; i++) {
        finalRes = finalRes + results[i];
    }
    
    long double finalWithoutThreads;
    
    taylor.calculateTerms(0, 10000000, x, ref(finalWithoutThreads));
    
    cout << finalWithoutThreads;
    return 0;
}