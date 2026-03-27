#include <bits/stdc++.h>
using namespace std;

class Rectangulo {
    private:
        double base, altura;
    public:
        Rectangulo(double b, double a) {
            setBase(b);
            setAltura(a);
        }
        void setBase(double b) {
            base = abs(b);
        }
        void setAltura(double a) {
            altura = abs(a);
        }
        double getBase() {
            return base;
        }

        double getAltura() {
            return altura;
        }
        double calcularArea() {
            return base * altura;
        }
        double calcularPerimetro() {
            return 2 * (base + altura);
        }
};

int main() {

    auto rect1 = new Rectangulo(1.2,2.5);

    cout << rect1->calcularArea();

    return 0;
}