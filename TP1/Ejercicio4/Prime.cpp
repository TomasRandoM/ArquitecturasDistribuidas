#include "Prime.h"
#include <vector> 
#include <algorithm>
Prime::Prime() {}

bool Prime::isPrimeNumber(long long int number) {
    if (number == 1 || number == 0) {
        return false;
    }

    for (long long int i = 2; i < number; i++) {
        if ((number % i) == 0) {
            return false;
        }  
    }
    return true;
}

void Prime::isPrimeNumberThreads(long long int number, std::vector<long long int>& rta) {
    if (number == 1) {
        return;
    }

    for (long long int i = 2; i < number; i++) {
        if ((number % i) == 0) {
            return;
        }  
    }
    mtx.lock();
    if (rta.size() != 10) {
        rta.push_back(number);
    } else {
        std::sort(rta.begin(), rta.end());
        if (rta[rta.size() - 1] > number) {
            rta.pop_back();
            rta.push_back(number);
        }
    }
    mtx.unlock();
}

void Prime::calculatePrimeNumbers(long long int from, long long int to, std::vector<long long int>& rta) {
    std::vector<long long int> rtaAux;
    for (long long int i = from; i < to; i++){
        if (isPrimeNumber(i)) {
            rtaAux.push_back(i);
        }
    }

    mtx.lock();
    for (long long int i = 0; i < rtaAux.size(); i++) {
        rta.push_back(rtaAux[i]);
    }
    mtx.unlock();
}