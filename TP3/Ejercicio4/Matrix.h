#ifndef MATRIX_H
#define MATRIX_H
#include <mutex>

class Matrix {
    private:
    std::mutex mtx;

    public: 
    // Constructor
    Matrix();

    // Función que multiplica dos matrices
    void multiply(float **matrix1, float **matrix2, float **matrixResult, double& sumResult, int n, int from, int to);

};

#endif