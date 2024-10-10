#include "Pattern.h"
#include <fstream>
#include <iostream>
#include <string>
//Constructor
Pattern::Pattern() {};

//Función que reconoce el patrón en la cadena de texto
void Pattern::recognizePattern(std::string pattern, long int& res) {
    int result = 0;
    bool stop = false;
    //Se abre el archivo que contiene el texto a analizar
    std::ifstream file("texto.txt");
    if (!file.is_open()) {
        throw std::invalid_argument("No se pudo abrir el archivo");
    }

    //Se lee la línea que contiene el texto a analizar y se guarda en la variable c

    std::string c;
    getline(file, c);
    
    file.close();

    //Rabin-karp
    long int n = c.size();
    int m = pattern.size();
    // Valor hash para el patrón
    int p = 0; 
    // Valor hash para el texto
    int t = 0; 
    int h = 1;
    int count = 0;
    // Caracteres posibles
    const int d = 256; 
    // Número primo
    const int q = 101; 

    // Se calcula h = d^(m-1) % q
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Se calculan los hash del patrón y del texto
    for (int i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + c[i]) % q;
    }

    // Se recorre el texto
    for (int i = 0; i <= n - m; i++) {
        if (p == t) {
            bool match = true;
            //Si ambos hashes son iguales, se comparan los caracteres
            for (int j = 0; j < m; j++) {
                if (c[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }

            if (match)
                count++; 
        }
        // Se calcula el hash del siguiente bloque de texto
        if (i < n - m) {
            t = (d * (t - c[i] * h) + c[i + m]) % q;

            // Se asegura que t sea positivo
            if (t < 0)
                t = (t + q);
        }
    }

    mtx.lock();
    res = count;
    mtx.unlock();
}
