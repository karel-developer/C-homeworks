#include <bits/stdc++.h>
using namespace std;

const double pi = 3.1415;

class Punto {
    public:
        double x, y;
        Punto(double X, double Y) {
            x = X;
            y = Y;
        }
};

double distancia(const Punto& a, const Punto& b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

class Circulo {
    public:
        Punto centro;
        double radio;
        Circulo(double r, const Punto& p) : centro(p) {
            double rad = r;
            if(r <= 0) {
                while(rad <= 0) {
                    cout << "Valor de radio invalido\n";
                    cout << "Ingrese un valor valido\n";
                    cin >> rad;
                }
            }
            radio = rad;
        }

        double area() {
            return pi * radio * radio;
        }

        double perimetro() {
            return 2 * pi * radio;
        }

        bool contienePunto(const Punto& p) {
            return distancia(centro, p) <= radio;
        }
};

int main() {

    Punto p(2.0, 2.0);

    Circulo c(4.0, p);

    cout << c.perimetro();

    return 0;
}