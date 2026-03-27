#include <bits/stdc++.h>
using namespace std;

class Matriz {
private:
    int filas, columnas;
    double** datos;

public:
    Matriz(int f, int c) : filas(f), columnas(c) {
        if (f <= 0 || c <= 0) throw invalid_argument("Dimensiones deben ser positivas");
        datos = new double*[filas];
        for (int i = 0; i < filas; ++i)
            datos[i] = new double[columnas]();
    }

    ~Matriz() {
        for (int i = 0; i < filas; ++i)
            delete[] datos[i];
        delete[] datos;
    }

    Matriz(const Matriz& otra) : filas(otra.filas), columnas(otra.columnas) {
        datos = new double*[filas];
        for (int i = 0; i < filas; ++i) {
            datos[i] = new double[columnas];
            for (int j = 0; j < columnas; ++j)
                datos[i][j] = otra.datos[i][j];
        }
    }

    Matriz& operator=(const Matriz& otra) {
        if (this != &otra) {
            for (int i = 0; i < filas; ++i)
                delete[] datos[i];
            delete[] datos;
            filas = otra.filas;
            columnas = otra.columnas;
            datos = new double*[filas];
            for (int i = 0; i < filas; ++i) {
                datos[i] = new double[columnas];
                for (int j = 0; j < columnas; ++j)
                    datos[i][j] = otra.datos[i][j];
            }
        }
        return *this;
    }

    double& operator()(int i, int j) {
        if (i < 0 || i >= filas || j < 0 || j >= columnas)
            throw out_of_range("Índice fuera de rango");
        return datos[i][j];
    }

    double operator()(int i, int j) const {
        if (i < 0 || i >= filas || j < 0 || j >= columnas)
            throw out_of_range("Índice fuera de rango");
        return datos[i][j];
    }

    Matriz operator+(const Matriz& otra) const {
        if (filas != otra.filas || columnas != otra.columnas)
            throw invalid_argument("Dimensiones no coinciden para suma");
        Matriz res(filas, columnas);
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < columnas; ++j)
                res.datos[i][j] = datos[i][j] + otra.datos[i][j];
        return res;
    }

    Matriz operator-(const Matriz& otra) const {
        if (filas != otra.filas || columnas != otra.columnas)
            throw invalid_argument("Dimensiones no coinciden para resta");
        Matriz res(filas, columnas);
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < columnas; ++j)
                res.datos[i][j] = datos[i][j] - otra.datos[i][j];
        return res;
    }

    Matriz operator*(const Matriz& otra) const {
        if (columnas != otra.filas)
            throw invalid_argument("Dimensiones no válidas para multiplicación");
        Matriz res(filas, otra.columnas);
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < otra.columnas; ++j)
                for (int k = 0; k < columnas; ++k)
                    res.datos[i][j] += datos[i][k] * otra.datos[k][j];
        return res;
    }

    Matriz transponer() const {
        Matriz res(columnas, filas);
        for (int i = 0; i < filas; ++i)
            for (int j = 0; j < columnas; ++j)
                res.datos[j][i] = datos[i][j];
        return res;
    }

    friend ostream& operator<<(ostream& os, const Matriz& m) {
        for (int i = 0; i < m.filas; ++i) {
            for (int j = 0; j < m.columnas; ++j)
                os << setw(6) << m.datos[i][j];
            os << endl;
        }
        return os;
    }
};
int main() {

    Matriz A(2, 3);
    A(0,0) = 1; A(0,1)=2; A(0,2)=3;
    A(1,0) = 4; A(1,1)=5; A(1,2)=6;
    cout << "Matriz A:\n" << A;
    Matriz B(3, 2);
    B(0,0)=7; B(0,1)=8;
    B(1,0)=9; B(1,1)=10;
    B(2,0)=11; B(2,1)=12;
    cout << "Matriz B:\n" << B;
    Matriz C = A * B;
    cout << "A * B:\n" << C;
    Matriz T = C.transponer();
    cout << "Transpuesta de C:\n" << T;

    return 0;
}