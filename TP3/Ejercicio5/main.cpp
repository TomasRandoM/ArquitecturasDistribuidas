#include "Prime.h"
#include <thread>
#include <functional>
#include <mpi.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

//Función que calcula los números primos en un rango solicitado
void calculate(int rank, int size, long long int n) {
int number = size;
chrono::time_point<chrono::high_resolution_clock> end, start;

//Se crea un objeto de la clase Prime
Prime prime;
//Se crea un vector que almacena los números primos
vector<long long int> rta;
//Se calcula el incremento de los rangos a calcular
long long int increment = n / number;
//Se inicializa el valor de inicio
long long int from = rank * increment;
//Se inicializa el valor de fin
long long int to;
if (rank == number - 1) {
    to = n;
} else {
    to = (rank + 1) * increment;
}

if (size == 1) {

    //Calcula los números primos en el primer rango
    start = chrono::high_resolution_clock::now();
    prime.calculatePrimeNumbers(0, n + 1, ref(rta));

    //Se detiene el cronómetro
    end = chrono::high_resolution_clock::now();

    sort(rta.begin(), rta.end());

    cout << "10 números primos más grandes hasta N con 1 proceso: " << endl;
    //Se imprimen los números primos calculados
    for (int i = rta.size() - 11; i < rta.size(); i++) {
        if (i == rta.size() - 11) {
        cout << rta[i];
        } else {
        cout << ", " << rta[i];
        }   
    }
    cout << endl;
    cout << "Cantidad de números primos menores a N con 1 proceso: " << rta.size() << endl;


    //Se calcula el tiempo de ejecución
    chrono::duration<double> elapsed = end - start;

    cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << endl;

} else  {
    if (rank == 0) {
        start = chrono::high_resolution_clock::now();
    }
    //Se calculan los números primos en los rangos solicitados
    prime.calculatePrimeNumbers(from, to, ref(rta));

    int vectorSize = rta.size();
    int aux;
    vector<int> recvSizes(size);
    vector<int> displ(size);
    int totalSize = 0;
    if (rank != 0) {  
        MPI_Send(&vectorSize, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
        for (int i = 1; i < size; i++) {
            MPI_Recv(&aux, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            recvSizes[i] = aux;
            vectorSize += aux;
            displ[i] = totalSize;
            totalSize += aux;
        }
    }
    vector<long long int> finalRta(vectorSize);

    MPI_Gatherv(rta.data(), rta.size(), MPI_LONG_LONG_INT, finalRta.data(), displ.data(), recvSizes.data(), MPI_LONG_LONG_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        end = chrono::high_resolution_clock::now();

        //Se calcula el tiempo de ejecución
        double time = chrono::duration_cast<chrono::seconds>(end - start).count();

        sort(finalRta.begin(), finalRta.end());

        cout << "10 números primos más grandes hasta N con " << size << " procesos: " << endl;

        //Se imprimen los números primos calculados
        for (int i = finalRta.size() - 11; i < finalRta.size(); i++) {
            if (i == finalRta.size() - 11) {
            cout << finalRta[i];
            } else {
            cout << ", " << finalRta[i];
            }   
        }
        cout << endl;
        cout << "Cantidad de números primos menores a N con " << size << " procesos: " << finalRta.size() << endl;
        rta.clear();

        cout << "Tiempo de ejecución: " << time << " segundos" << endl;
    }
}
MPI_Finalize();
}

int main(int argc, char** argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    long long int parametro;
    if (argc > 1) {
        parametro = atoi(argv[1]); 
    } else {
        parametro = 10000000;
    }
    calculate(rank, size, parametro);
}




/*
//Calcula los números primos en el segundo rango
index = n;
int count = 0;
while (count != 10) {
    if (prime.isPrimeNumber(index)) {
        count++;
        rtaAux.push_back(index);
    }
    index++;
}
*/

/*
//Se almacenan los números primos calculados por los hilos restantes en el vector de números primos
for (int i = 0; i < rtaAux.size(); i++) {
    rta.push_back(rtaAux[i]);
}
*/

/*
//Se crea un vector auxiliar para almacenar los números primos calculados por los hilos restantes
vector<long long int> rtaAux;
//Se inicializa el valor de inicio
long long int index = n;
//Se calculan los números primos del segundo rango
while (rtaAux.size() != 10) {
    for (int i = 10; i < threadNumber; i++) {
        index = index + 1;
        threadArray[i] = thread(&Prime::isPrimeNumberThreads, &prime, index, ref(rtaAux));
    }

    for (int i = 10; i < threadNumber; i++) {
        if (threadArray[i].joinable()) {
            threadArray[i].join();
        }
    }
}
*/