#include <stdio.h>
#include <stdlib.h>
#include "Taylor.h"
#include <cmath>
#include <mutex>
#include <iostream>

//Constructor
Taylor::Taylor() {};

//Función que calcula el logaritmo natural de x utilizando la serie de Taylor
void Taylor::calculateSeries(int from, int to, long double x, long double& res) {
    long double sum = 0.0F;
    for (long double i = from; i < to; i++) {
        //Se calcula la suma de la serie
        sum = sum + (1.0L/(2.0L*i + 1.0L)) * pow(((x-1.0L)/(x+1.0L)), 2.0L*i + 1.0L);
    }
    //Se guarda el resultado en la variable res utilizando un mutex
    mtx.lock();
    res = 2.0L * sum;
    //Se desbloquea el mutex
    mtx.unlock();
};