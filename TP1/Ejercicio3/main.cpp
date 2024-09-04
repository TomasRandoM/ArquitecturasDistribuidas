#include "Matrix.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
using namespace std;

void initializeMatrix(float** matrix, int n, float a) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = a;
        }
    }
}

//Función que calcula la cantidad de veces que aparece un patrón en un archivo de texto
void calculate() {
    double result = 0;
    thread threads[32];
    int n = 1000;
    float** matrix1 = new float*[n];
    float** matrix2 = new float*[n];
    float** matrixResults = new float*[n];
    for (int i = 0; i < n; ++i) {
        matrix1[i] = new float[n];
        matrix2[i] = new float[n];
        matrixResults[i] = new float[n];
    }
    initializeMatrix(ref(matrix1), n, 0.1);
    initializeMatrix(ref(matrix2), n, 0.2);
    initializeMatrix(ref(matrixResults), n, 0);
    
    Matrix matrix;
    
    //Se inicia el cronómetro para medir el tiempo de ejecución



    //CON HILOS
    cout << "Con hilos" << endl;

    //Se inicia el cronómetro
    auto start = chrono::high_resolution_clock::now();

    //Se inician los hilos llamando a la función recognizePattern, cada uno con un patrón distinto 
    /*  
    for (int i = 0; i < 1; i++) {
        threads[i] = thread(&Matrix::multiply, &matrix, ref(matrix1), ref(matrix2), ref(matrixResults), ref(result), 3, 0, 3);
    }

    //Se espera a que todos los hilos terminen
    for (int i = 0; i < 1; i++) {
        continue;
    }
    */
    matrix.multiply(ref(matrix1), ref(matrix2), ref(matrixResults), ref(result), n, 0, n);
   
    //Se imprimen los resultados
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrixResults[i][j] << " ";
        }
        cout << endl;
    }
    
    //Se detiene el cronómetro
    auto end = chrono::high_resolution_clock::now();

    //Se calcula el tiempo de ejecución
    chrono::duration<double> elapsed = end - start;

    cout << "Tiempo de ejecución con hilos: " << elapsed.count() << "s" << endl;

    //SIN HILOS
    cout << "Sin hilos" << endl;
    //Se inicia el cronómetro
    start = chrono::high_resolution_clock::now();
    

    //Se imprimen los resultados
    

    //Se detiene el cronómetro
    end = chrono::high_resolution_clock::now();

    //Se calcula el tiempo de ejecución
    elapsed = end - start;
    
    cout << "Tiempo de ejecución sin hilos: " << elapsed.count() << "s" << endl; 
    
    cin.get();
    cin.get();
}

//Función principal
int main() {
    while (true) {
        try {
            calculate();
        } catch (const invalid_argument& e) {
            cout << e.what() << endl;
        }

    }
}