#include <bits/stdc++.h>
using namespace std;

const double PI = 3.1415;

class Figura {
    public:
        virtual double area() = 0;
        virtual double perimetro() = 0;
        Figura() {}
};

class Rectangulo : public Figura {
    private:
        double largo, ancho;
    public:
        Rectangulo(double l, double a) {
            double l1 = l;
            double a1 = a;
            if(l <= 0) {
                while(l1 <= 0) {
                    cout << "Largo invalido\n";
                    cout << "Ingrese un largo valido\n";
                    cin >> l1;
                }
            }
            if(a <= 0) {
                while(a1 <= 0) {
                    cout << "Ancho invalido\n";
                    cout << "Ingrese un ancho valido\n";
                    cin >> a1;
                }
            }
            largo = l1;
            ancho = a1;
        }

        double area() override {
            return largo * ancho;
        }

        double perimetro() override {
            return 2 * (largo + ancho);
        }
};

class Circulo : public Figura {
    private:
        double radio;
    public:
        Circulo(double r) {
            double r1 = r;
            if(r <= 0) {
                while(r1 <= 0) {
                    cout << "Radio invalido\n";
                    cout << "Ingrese un valor de radio valido\n";
                    cin >> r1;
                }
            }
            radio = r1;
        }
        double area() override {
            return PI * radio * radio;
        }

        double perimetro() override {
            return 2 * PI * radio;
        }
};

class Triangulo : public Figura {
    private:
        double l1, l2, l3;
    public:
        Triangulo(double a, double b, double c) {
            double a1 = a;
            double b1 = b;
            double c1 = c;
            while(a1 <= 0) {
                cout << "Lado invalido\n";
                cout << "Ingrese un valor de lado valido\n";
                cin >> a1;
            }
            while(b1 <= 0) {
                cout << "Lado invalido\n";
                cout << "Ingrese un valor de lado valido\n";
                cin >> b1;
            }
            while(c1 <= 0) {
                cout << "Lado invalido\n";
                cout << "Ingrese un valor de lado valido\n";
                cin >> c1;
            }

            while(!(a1 + b1 > c1 && a1 + c1 > b1 && b1 + c1 > a1)) {
                cout << "No se cumple la desigualdad triangular\n";
                cout << "Ingrese nuevo valor para el lado 1: ";
                cin >> a1;
                cout << "Ingrese nuevo valor para el lado 2: ";
                cin >> b1;
                cout << "Ingrese nuevo valor para el lado 3: ";
                cin >> c1;

                while(a1 <= 0) {
                    cout << "Lado invalido\n";
                    cout << "Ingrese un valor de lado valido\n";
                    cin >> a1;
                }
                while(b1 <= 0) {
                    cout << "Lado invalido\n";
                    cout << "Ingrese un valor de lado valido\n";
                    cin >> b1;
                }
                while(c1 <= 0) {
                    cout << "Lado invalido\n";
                    cout << "Ingrese un valor de lado valido\n";
                    cin >> c1;
                }
            }

            l1 = a1;
            l2 = b1;
            l3 = c1;
        }
        double area() override {
            double s = (l1 + l2 + l3) / 2;
            return sqrt(s * (s - l1) * (s - l2) * (s - l3));
        }
        double perimetro() override {
            return l1 + l2 + l3;
        }
};
int main() {

    vector<Figura*> figuras;

    figuras.push_back(new Rectangulo(2, 4));
    figuras.push_back(new Circulo(9));
    figuras.push_back(new Triangulo(3,4,5));

    double areaT = 0;

    for(auto x : figuras) {
        areaT += x->area();
    }
    
    cout << "Area total : " << areaT;
    return 0;
}