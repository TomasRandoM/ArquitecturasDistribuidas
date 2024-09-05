#include "Prime.h"
#include <vector> 
#include <algorithm>
#include <cmath>

Prime::Prime() {}

bool Prime::isPrimeNumber(long long int number) {
    if (number == 1 || number == 0) {
        return false;
    }

    long long int numberSqrt = (long long int) std:: floor(std:: sqrt(number));
    
    for (long long int i = 2; i <= numberSqrt; i++) {
        if ((number % i) == 0) {
            return false;
        }  
    }
    return true;
}

void Prime::calculatePrimeNumbers(long long int from, long long int to, std::vector<long long int>& rta) {
    for (long long int i = from; i < to; i++){
        if (isPrimeNumber(i)) {
            mtx.lock();
            rta.push_back(i);
            mtx.unlock();
        }
    }

}