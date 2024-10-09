#include "Pattern.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <fstream>
using namespace std;


//Función que calcula la cantidad de veces que aparece un patrón en un archivo de texto
void calculate() {
    long int result[32] = {0};
    long int resultThreads[32] = {0};
    string patterns[32];
    thread threads[32];
    Pattern pattern;
    
    //Se inicia el cronómetro para medir el tiempo de ejecución

    fstream file("patrones.txt");
    if (!file.is_open()) {
        throw invalid_argument("No se pudo abrir el archivo");
    }

    for (int i = 0; i < 32; i++) {
        getline(file, patterns[i]);
    }

    file.close();


    //CON HILOS
    cout << "Con hilos" << endl;

    //Se inicia el cronómetro
    auto start = chrono::high_resolution_clock::now();

    //Se inician los hilos llamando a la función recognizePattern, cada uno con un patrón distinto    
    for (int i = 0; i < 32; i++) {
        threads[i] = thread(&Pattern::recognizePattern, &pattern, patterns[i], ref(resultThreads[i]));
    }

    //Se espera a que todos los hilos terminen
    for (int i = 0; i < 32; i++) {
        threads[i].join();
    }
    
    //Se imprimen los resultados
    for (int i = 0; i < 32; i++) {
        cout << "El patrón " << i << " aparece " << resultThreads[i] << " veces" << endl;
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
    
    for (int i = 0; i < 32; i++) {
        pattern.recognizePattern(patterns[i], ref(result[i]));
    }

    //Se imprimen los resultados
    for (int i = 0; i < 32; i++) {
        cout << "El patrón " << i << " aparece " << result[i] << " veces" << endl;
    }

    //Se detiene el cronómetro
    end = chrono::high_resolution_clock::now();

    //Se calcula el tiempo de ejecución
    elapsed = end - start;
    
    cout << "Tiempo de ejecución sin hilos: " << elapsed.count() << "s" << endl; 
    
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