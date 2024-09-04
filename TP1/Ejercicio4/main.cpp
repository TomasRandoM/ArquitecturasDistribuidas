#include "Prime.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>

using namespace std;

void calculate() {
int threadNumber = 20;
thread threadArray[threadNumber];
long long int n = 10000;
Prime prime;
vector<long long int> rta;
long long int increment = n / threadNumber;
long long int from = 0;
cout << "hola";
for (int i = 0; i < 10; i++) {
    threadArray[i] = thread(&Prime::calculatePrimeNumbers, &prime, from, from + increment, ref(rta));
    from = from + increment;
}

vector<long long int> rtaAux;
long long int index = n;
while (rtaAux.size() != 10) {
    for (int i = 10; i < threadNumber; i++) {
        index = index + 1;
        threadArray[i] = thread(&Prime::isPrimeNumberThreads, &prime, index, ref(rtaAux));
    }

    for (int i = 10; i < threadNumber; i++) {
        if (threadArray[i].joinable()) {
            threadArray[i].join();
        }
    }
}

for (int i = 0; i < threadNumber; i++) {
    if (threadArray[i].joinable()) {
        threadArray[i].join();
    }
}

for (int i = 0; i < rtaAux.size(); i++) {
    rta.push_back(rtaAux[i]);
}

for (int i = 0; i < rta.size(); i++) {
    cout << rta[i] << endl;
}
}

int main() {
    cout << "Hello";
    try {
        calculate();
    } catch (const invalid_argument e) {
        cout << e.what() << endl;
    }
}