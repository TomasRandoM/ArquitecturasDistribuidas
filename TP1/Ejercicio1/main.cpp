#include "Taylor.h"
#include <thread>
#include <functional>
#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

//Función que pregunta al usuario si desea continuar, devuelve true si la respuesta es 's' o 'S', false en caso contrario
bool continueSN() {
    cout << "¿Desea continuar? (s/n): ";
    char c;
    cin >> c;

    if (cin.fail()) {
        cin.clear();
        throw invalid_argument("El número no es válido");
        cin.get();
    }

    if ((c == 's') || (c == 'S')) {
        return true;
    } else {
        return false;
    }
}

//Función que calcula el logaritmo natural de x utilizando la serie de Taylor
void calculate() {
    //Declaración de variables
    int n;
    Taylor taylor;
    long double finalRes;
    long double x = 1500000;
    int from = 0;
    int to = 10000000;
    
    //Entrada de datos
    cout << "Ingrese la cantidad de hilos: ";
    //Se solicita la cantidad de hilos, 1 si se calcula sin hilos
    cin >> n;
    if (cin.fail()) {
        cin.clear();
        throw invalid_argument("El número no es válido");
    } else if (n <= 0) {
        throw invalid_argument("El número no puede ser negativo");
    } else if (10000000 % n != 0) {
        throw invalid_argument("El número no es divisor de 10000000");
    }
    //Se solicita el valor a calcular
    cout << "Ingrese el valor a calcular: ";
    cin >> x;
    if (cin.fail()) {
        cin.clear();
        throw invalid_argument("El número no es válido");
        cin.get();
    } else if (x < 0) {
        throw invalid_argument("El número no puede ser negativo");
        cin.get();
    }

    //Se inicia el cronómetro para medir el tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();
    //Si n == 1, se calcula sin utilizar hilos
    if (n == 1) {
        //Se llama a la función calculateSeries de la clase Taylor
        taylor.calculateSeries(from, to, x, ref(finalRes));
        cout << setprecision(15) << "Resultado sin hilos: " << finalRes << endl;

    } else {
        //Se crea un arreglo de hilos
        thread threadArray[n];
        //Se crea un arreglo donde se almacenará el resultado
        long double results[n];
        //Se calcula el incremento, que será utilizado para calcular el rango de cada hilo
        int increment = to / n;
        
        //Se crean los hilos
        for (int i = 0; i <n; i++) {
            //Se llama a la función calculateSeries de la clase Taylor en cada hilo
            threadArray[i] = thread(&Taylor::calculateSeries, &taylor, from, from + increment, x, ref(results[i]));
            from = from + increment;    
        }

        //Se espera a que todos los hilos terminen
        for (int i = 0; i <n; i++) {
            if (threadArray[i].joinable() == true) {
                threadArray[i].join();
            }
        }

        //Se suman los resultados de cada hilo para obtener el resultado final
        long double finalRes = 0;
        for (int i = 0; i < n; i++) {
            finalRes = finalRes + results[i];
        }
        cout << setprecision(15) << "Resultado con hilos: " << finalRes << endl;
    }
    //Se detiene el cronómetro
    auto end = chrono::high_resolution_clock::now();
    //Se calcula el tiempo de ejecución
    chrono::duration<double> elapsed = end - start;
    cout << "Tiempo de ejecución: " << elapsed.count() << "s" << endl; 
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

        if (!continueSN()) {
            return 0;
        }
    }
}