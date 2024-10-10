#ifndef TAYLOR_H
#define TAYLOR_H
#include <mutex>

//Clase Taylor
class Taylor {
    public:
        //Constructor
        Taylor();
        //Función que calcula el logaritmo natural de x utilizando la serie de Taylor
        void calculateSeries(int from, int to, long double x, long double& res);
    private:
        //Mutex
        std::mutex mtx;
};
#endif