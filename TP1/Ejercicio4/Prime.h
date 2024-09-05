#ifndef PRIME_H
#define PRIME_H
#include <mutex>
#include <vector>

class Prime {
    private:
    std::mutex mtx;

    public:

    Prime();
    bool isPrimeNumber(long long int number);
    void calculatePrimeNumbers(long long int from, long long int to, std::vector<long long int>& rta);

};

#endif