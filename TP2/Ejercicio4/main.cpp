#include "Matrix.h"
#include <thread>
#include <mpi.h>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;

void printMatrix(float** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << matrix[i][j] << " ";  // Imprime con formato de 10 caracteres de ancho
        }
        cout << endl;
    }
}


void initializeMatrix(float** matrix, int n, float a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = a;
        }
    }
}

//Función que calcula la multiplicación de dos matrices
void calculate(int rank, int size) {
    chrono::time_point<chrono::high_resolution_clock> end, start;
    double result = 0;
    //Filas y columnas de las matrices
    int n = 300;
    int numberMPI = size;
    int to;
    int increment = n / numberMPI;
    int from = rank * increment;
    if (rank == numberMPI - 1) {
        to = n;
    } else {
        to = (rank + 1) * increment;
    }
    float** matrix1 = new float*[n];
    float** matrix2 = new float*[n];
    float** matrixResults = new float*[n];
    float** matrixResultsThreads = new float*[n];
    for (int i = 0; i < n; ++i) {
        matrix1[i] = new float[n];
        matrix2[i] = new float[n];
        matrixResults[i] = new float[n];
        matrixResultsThreads[i] = new float[n];
    }
    initializeMatrix(ref(matrix1), n, 0.1);
    initializeMatrix(ref(matrix2), n, 0.2);
    initializeMatrix(ref(matrixResults), n, 0);
    initializeMatrix(ref(matrixResultsThreads), n, 0);
    
    Matrix matrix;
    
    if (size == 1) {
        result = 0;
        //Se inicia el cronómetro
        start = chrono::high_resolution_clock::now();

        matrix.multiply(ref(matrix1), ref(matrix2), ref(matrixResults), ref(result), n, 0, n);

        //Se imprimen los resultados
        cout << "Primer elemento: " << endl;
        cout << matrixResults[0][0] << endl;
        cout << "Ùltimo elemento: " << endl;
        cout << matrixResults[n - 1][n - 1] << endl;
        cout << "Sumatoria: " << result << endl;
        //Se detiene el cronómetro
        end = chrono::high_resolution_clock::now();

        //Se calcula el tiempo de ejecución
        chrono::duration<double> elapsed = end - start;
        
        cout << "Tiempo de ejecución con 1 proceso " << elapsed.count() << "s" << endl; 
        
    } else {

        if (rank == 0) {
            //Se inicia el cronómetro
            start = chrono::high_resolution_clock::now();
        }

        //Se inician los hilos llamando a la función recognizePattern, cada uno con un patrón distinto 
        matrix.multiply(ref(matrix1), ref(matrix2), ref(matrixResults), ref(result), n, from, to);

        if (rank == 0) {
            for (int i = 1; i < size; i++) {
                int recvFrom = i * increment;
                int recvTo;
                if (i == size - 1) {
                    recvTo = n;
                } else {
                    recvTo = (i + 1) * increment;
                }
            for (int j = recvFrom; j < recvTo; j++) {
                MPI_Recv(&(matrixResults[j][0]), n, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
            }
        } else {
            for (int i = from; i < to; i++) {
                MPI_Send(&(matrixResults[i][0]), n, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
            }
        }
        double resultAux;
        if (rank == 0) {
            for (int i = 1; i < size; i++) {
                MPI_Recv(&resultAux, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                result += resultAux;
            }
        } else {
            MPI_Send(&result, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
 
        /*
        if (rank == 0) {
            for (int i = 1; i < size; i++) {
                if (i == size - 1) {
                    MPI_Recv(&(matrixResults[i * increment][0]), (n - i * increment) * n, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                } else {
                    MPI_Recv(&(matrixResults[i * increment][0]), increment * n, MPI_FLOAT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                }
            }
        } else {
            if (rank == size - 1) {
                MPI_Send(&(matrixResults[from][0]), (n - 1 * increment) * n, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
            } else {
                MPI_Send(&(matrixResults[from][0]), increment * n, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
            }
        }
        */
        
        if (rank == 0) {
            //Se imprimen los resultados
            cout << "Primer elemento: " << endl;
            cout << matrixResults[0][0] << endl;
            cout << "Ùltimo elemento: " << endl;
            cout << matrixResults[n - 1][n - 1] << endl;
            cout << "Sumatoria: " << result << endl;

            //Se detiene el cronómetro
            end = chrono::high_resolution_clock::now();

            //Se calcula el tiempo de ejecución
            chrono::duration<double> elapsed = end - start;

            cout << "Tiempo de ejecución con " << size << " procesos: " << elapsed.count() << "s" << endl;
        }
    }
    
}

//Función principal
int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    calculate(rank, size);
    MPI_Finalize();
}