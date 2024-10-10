#include "Pattern.h"
#include <mpi.h>
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <fstream>
using namespace std;


//Función que calcula la cantidad de veces que aparece un patrón en un archivo de texto
void calculate(int rank, int n) {
    chrono::time_point<chrono::high_resolution_clock> end, start;
    long int result[32] = {0};
    long int resultIn = 0;
    vector<long int> resultThreads(32);
    string patterns[32];
    Pattern pattern;
    
    //Se inicia el cronómetro para medir el tiempo de ejecución

    fstream file("patrones.txt");
    if (!file.is_open()) {
        throw invalid_argument("No se pudo abrir el archivo de patrones");
    }

    for (int i = 0; i < 32; i++) {
        getline(file, patterns[i]);
    }

    file.close();

    if (n != 1) {
        if (rank == 0) {
            //Se inicia el cronómetro
            start = chrono::high_resolution_clock::now();
        }
        //Se inician los hilos llamando a la función recognizePattern, cada uno con un patrón distinto
        pattern.recognizePattern(patterns[rank], ref(resultIn));   

        MPI_Gather(&resultIn, 1, MPI_LONG_INT, resultThreads.data(), 1, MPI_LONG_INT, 0, MPI_COMM_WORLD);
        if (rank == 0) {
            //Se imprimen los resultados
            for (int i = 0; i < 32; i++) {
                cout << "El patrón " << i << " aparece " << resultThreads[i] << " veces" << endl;
            }
            
            //Se detiene el cronómetro
            end = chrono::high_resolution_clock::now();

            //Se calcula el tiempo de ejecución
            chrono::duration<double> elapsed = end - start;

            cout << "Tiempo de ejecución con " << n << " procesos: " << elapsed.count() << "s" << endl;
        }
    } else {
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
    chrono::duration<double> elapsed = end - start;
    
    cout << "Tiempo de ejecución con " << n << " procesos: " << elapsed.count() << "s" << endl;    
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