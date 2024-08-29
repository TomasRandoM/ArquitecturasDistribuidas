#include <stdio.h>
#include <stdlib.h>
#include "Taylor.h"
#include <cmath>
#include <mutex>

Taylor::Taylor() {};

void Taylor::calculateTerms(int from, int to, long double x, long double& res) {
    long double sum = 0;
    for (int i = from; i < to; i++) {
        sum = sum + (1/(2*i + 1)) * pow(((x-1)/(x+1)), 2*i + 1);
    }
    mtx.lock();
    res = 2 * sum;
    mtx.unlock();
};