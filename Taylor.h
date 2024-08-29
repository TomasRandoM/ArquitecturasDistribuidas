#ifndef TAYLOR_H
#define TAYLOR_H
#include <mutex>

class Taylor {
    public:
        Taylor();
        void calculateTerms(int from, int to, long double x, long double& res);
    private:
        std::mutex mtx;
};
#endif