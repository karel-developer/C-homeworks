#pragma once
#include <iostream>
#include <limits>
#include <string>

using namespace std;

inline void limpiarBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

inline int leerEntero() {
    int valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cout << "Error: Debe ingresar un numero entero.\n";
            limpiarBuffer();
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

inline double leerDouble() {
    double valor;
    while (true) {
        cin >> valor;
        if (cin.fail()) {
            cout << "Error: Debe ingresar un numero valido.\n";
            limpiarBuffer();
        } else {
            limpiarBuffer();
            return valor;
        }
    }
}

inline string leerString() {
    string valor;
    while (true) {
        getline(cin, valor);
        if (valor.empty()) {
            cout << "Error: El campo no puede estar vacio.\n";
        } else {
            return valor;
        }
    }
}

inline char leerCharacter() {
    string entrada;
    while (true) {
        getline(cin, entrada);
        size_t inicio = entrada.find_first_not_of(" \t");
        if (inicio != string::npos) {
            entrada = entrada.substr(inicio);
        }
        size_t fin = entrada.find_last_not_of(" \t");
        if (fin != string::npos) {
            entrada = entrada.substr(0, fin + 1);
        }
        
        if (entrada.length() != 1) {
            cout << "Error: Debe ingresar exactamente UN carácter.\n";
            continue;
        }
        
        char c = tolower(entrada[0]);
        return c;
    }
}