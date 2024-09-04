#include "Matrix.h"

Matrix::Matrix() {
}

void Matrix::multiply(float **matrix1, float **matrix2, float **matrixResult, double sumResult, int n, int from, int to){
    float** resAux = new float*[to-from + 1];
    for (int i = 0; i < to-from + 1; ++i) {
        resAux[i] = new float[n]();
    }
    int index = 0;
    double sumAux = 0;

    for (int i = from; i < to; i++) {
        for (int j = 0; j < n; j++){
            for (int k = 0; k < n; k++){
                resAux[index][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
        index++;
     }
    
    mtx.lock();
    for (int i = from; i < to; i++) {
        for (int j = 0; j < n; j++){
            sumAux += resAux[i-from][j];
            matrixResult[i][j] = resAux[i-from][j];
        }
    }
    sumResult += sumAux;
    mtx.unlock();

    for (int i = 0; i < to-from + 1; ++i) {
        delete[] resAux[i];
    }
    delete[] resAux;
}