#include "Matrix.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
using namespace std;

void initializeMatrix(float** matrix, int n, float a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = a;
        }
    }
}

//Función que calcula la multiplicación de dos matrices
void calculate() {
    double result = 0;
    thread threads[32];
    int n = 1000;
    int numberThreads = 10;
    cout << "Ingrese la cantidad de filas y columnas: ";
    cin >> n;
    if (cin.fail()) {
        throw invalid_argument("El número no es válido");
        cin.get();
    } else if (n < 0) {
        throw invalid_argument("El número no puede ser negativo");
        cin.get();
    } else if (n % numberThreads) {
        throw invalid_argument("El número debe ser múltiplo del número de hilos");
        cin.get();
    }
    
    int increment = n / 10;
    int from = 0;
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
    
    //Se inicia el cronómetro para medir el tiempo de ejecución



    //CON HILOS
    cout << "Con hilos" << endl;

    //Se inicia el cronómetro
    auto start = chrono::high_resolution_clock::now();

    //Se inician los hilos llamando a la función recognizePattern, cada uno con un patrón distinto 
    

    for (int i = 0; i < numberThreads; i++) {
        threads[i] = thread(&Matrix::multiply, &matrix, ref(matrix1), ref(matrix2), ref(matrixResultsThreads), ref(result), n, from, from + increment);
        from = from + increment;
    }

    //Se espera a que todos los hilos terminen
    for (int i = 0; i < numberThreads; i++) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
   
    //Se imprimen los resultados
    cout << "Primer elemento: " << endl;
    cout << matrixResultsThreads[0][0] << endl;
    cout << "Ùltimo elemento: " << endl;
    cout << matrixResultsThreads[n - 1][n - 1] << endl;
    cout << "Sumatoria: " << result << endl;

    //Se detiene el cronómetro
    auto end = chrono::high_resolution_clock::now();

    //Se calcula el tiempo de ejecución
    chrono::duration<double> elapsed = end - start;

    cout << "Tiempo de ejecución con hilos: " << elapsed.count() << "s" << endl;

    //SIN HILOS
    cout << "Sin hilos" << endl;
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
    elapsed = end - start;
    
    cout << "Tiempo de ejecución sin hilos: " << elapsed.count() << "s" << endl; 
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

//Función principal
int main() {
    try {
        calculate();
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}