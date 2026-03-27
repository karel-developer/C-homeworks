#include <bits/stdc++.h>
using namespace std;

class Fraccion {
    private:
        int numerador;
        int denominador;

        int mcd(int a, int b) {
            a = abs(a);
            b = abs(b);
            while (b != 0) {
                int temp = b;
                b = a % b;
                a = temp;
            }
            return a;
        }

        void simplificar() {
            int divisor = mcd(numerador, denominador);
            numerador /= divisor;
            denominador /= divisor;
            if (denominador < 0) {
                numerador = -numerador;
                denominador = -denominador;
            }
        }

    public:
        Fraccion(int num, int den) {
            int den1 = den;
            if (den == 0) {
                do {
                    cout << "Denominador invalido\n";
                    cout << "Ingresa uno valido\n";
                    cin >> den1;
                } while(den1 == 0);
            }
            numerador = num;
            denominador = den1;
            simplificar();
        }

        Fraccion sumar(const Fraccion& otra) {
            int num = numerador * otra.denominador + otra.numerador * denominador;
            int den = denominador * otra.denominador;
            return Fraccion(num, den);
        }

        Fraccion restar(const Fraccion& otra) {
            int num = numerador * otra.denominador - otra.numerador * denominador;
            int den = denominador * otra.denominador;
            return Fraccion(num, den);
        }

        Fraccion multiplicar(const Fraccion& otra) {
            return Fraccion(numerador * otra.numerador, denominador * otra.denominador);
        }

        Fraccion dividir(const Fraccion& otra) {
            return Fraccion(numerador * otra.denominador, denominador * otra.numerador);
        }

        double valorReal() {
            return (double) numerador / denominador;
        }

        void mostrar() {
            cout << numerador << "/" << denominador;
        }
};

int main() {

    Fraccion f1(2, 4);
    Fraccion f2(3, 6);
    Fraccion suma = f1.sumar(f2);
    cout << "Suma: "; suma.mostrar(); cout << " = " << suma.valorReal() << endl;
    Fraccion prod = f1.multiplicar(f2);
    cout << "Producto: "; prod.mostrar(); cout << " = " << prod.valorReal() << endl;

    return 0;
}