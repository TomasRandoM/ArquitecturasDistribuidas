#include "Prime.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>

using namespace std;

//Función que calcula los números primos en un rango solicitado
void calculate() {
//Se crean 20 hilos
int threadNumber = 10;
thread threadArray[threadNumber];
//Se almacena el número n solicitado
long long int n;

cout << "Ingrese el número n: ";
cin >> n;
if (cin.fail()) {
    throw invalid_argument("El número no es válido");
    cin.get();
} else if (n < 0) {
    throw invalid_argument("El número no puede ser negativo");
    cin.get();
} else if (n % (threadNumber)) {
    throw invalid_argument("El número debe ser múltiplo del número de hilos / 2");
    cin.get();
}

//Se crea un objeto de la clase Prime
Prime prime;
//Se crea un vector que almacena los números primos
vector<long long int> rta;
//Se calcula el incremento de los rangos a calcular
long long int increment = n / threadNumber;
//Se inicializa el valor de inicio
long long int from = 0;

//Con hilos
auto start = chrono::high_resolution_clock::now();
//Se calculan los números primos en los rangos solicitados
for (int i = 0; i < threadNumber; i++) {
    threadArray[i] = thread(&Prime::calculatePrimeNumbers, &prime, from, from + increment, ref(rta));
    from = from + increment;
}

//Se espera a que los hilos terminen de ejecutarse
for (int i = 0; i < threadNumber; i++) {
    if (threadArray[i].joinable()) {
        threadArray[i].join();
    }
}


//Se detiene el cronómetro
auto end = chrono::high_resolution_clock::now();

//Se calcula el tiempo de ejecución
double time = chrono::duration_cast<chrono::seconds>(end - start).count();

sort(rta.begin(), rta.end());

cout << "10 números primos más grandes hasta N CON hilos: " << endl;

//Se imprimen los números primos calculados
for (int i = rta.size() - 11; i < rta.size(); i++) {
    if (i == rta.size() - 11) {
    cout << rta[i];
    } else {
    cout << ", " << rta[i];
    }   
}
cout << endl;
cout << "Cantidad de números primos menores a N CON hilos: " << rta.size() << endl;
rta.clear();

cout << "Tiempo de ejecución CON hilos: " << time << " segundos" << endl;


//Sin hilos

//Calcula los números primos en el primer rango
start = chrono::high_resolution_clock::now();
prime.calculatePrimeNumbers(0, n + 1, ref(rta));

//Se detiene el cronómetro
end = chrono::high_resolution_clock::now();

sort(rta.begin(), rta.end());

cout << "10 números primos más grandes hasta N SIN hilos: " << endl;
//Se imprimen los números primos calculados
for (int i = rta.size() - 11; i < rta.size(); i++) {
    if (i == rta.size() - 11) {
    cout << rta[i];
    } else {
    cout << ", " << rta[i];
    }   
}
cout << endl;
cout << "Cantidad de números primos menores a N SIN hilos: " << rta.size() << endl;


//Se calcula el tiempo de ejecución
time = chrono::duration_cast<chrono::seconds>(end - start).count();

cout << "Tiempo de ejecución SIN hilos: " << time << " segundos" << endl;

cin.ignore(numeric_limits<streamsize>::max(), '\n');
cin.get();
}

int main() {
    try {
        calculate();
    } catch (const invalid_argument e) {
        cout << e.what() << endl;
    }
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