#include <mpi.h>
#include "Taylor.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

//Función que calcula el logaritmo natural de x utilizando la serie de Taylor
void calculate(int rank, int n) {
    //Declaración de variables
    Taylor taylor;
    long double finalRes = 0.0;
    chrono::time_point<chrono::high_resolution_clock> end, start;
    int to;
    long double x = 1500000;
    int total = 10000000;
    int range = total / n;
    int from = rank * (range);
    vector<int> recvcounts(n);
    if (rank == n - 1) {
        to = total;
    } else {
        to = (rank + 1) * range;
    }


    //Se inicia el cronómetro para medir el tiempo de ejecución
    if (rank == 0) {
        start = chrono::high_resolution_clock::now();
    }
    //Si n == 1, se calcula sin utilizar hilos
    if (n == 1) {
        //Se llama a la función calculateSeries de la clase Taylor
        taylor.calculateSeries(from, to, x, ref(finalRes));
        cout << setprecision(15) << "Resultado 1 proceso: " << finalRes << endl;
        end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cout << "Tiempo de ejecución: " << elapsed.count() << "s" << endl; 
        cin.get();
    } else {
        //Se crea un arreglo donde se almacenará el resultado
        long double results = 0.0;
        
        taylor.calculateSeries(from, to, x, ref(results));
        
        //Se envía el resultado al proceso 0
        if (rank != 0) {
            MPI_Send(&results, 1, MPI_LONG_DOUBLE, 0, 0, MPI_COMM_WORLD);
        } else {
            finalRes = finalRes + results;
            for (int i = 1; i < n; i++) {
                MPI_Recv(&results, 1, MPI_LONG_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                finalRes = finalRes + results;
            }
            cout << setprecision(15) << "Resultado con " << n << " procesos: " << finalRes << endl;
            //Se detiene el cronómetro
            end = chrono::high_resolution_clock::now();
            //Se calcula el tiempo de ejecución
            chrono::duration<double> elapsed = end - start;
            cout << "Tiempo de ejecución: " << elapsed.count() << "s" << endl; 
        }

        MPI_Finalize();
    }
    

}

//Función principal
int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    calculate(rank, size);
}