#include <bits/stdc++.h>
using namespace std;

string formatearDato(int n) {
    return ((n > 9) ? to_string(n) : "0" + to_string(n));
}

class Reloj {
    private:
        int horas, minutos, segundos;
    public:
        Reloj(int h, int m, int s) {
            int hora1 = h;
            int minutos1 = m;
            int segundos1 = s;
            if(h < 0 || h >= 60 || m < 0 || m >= 60 || s < 0 || s >= 60) {
                while(hora1 < 0 || hora1 >= 60 || minutos1 < 0 || minutos1 >= 60 || segundos1 < 0 || segundos1 >= 60) {
                    cout << "Hora invalida\n";
                    cout << "Ingrese un valor de hora valida\n";
                    cin >> hora1;
                    cout << "Ingrese un valor de minutos valido\n";
                    cin >> minutos1;
                    cout << "Ingrese un valor de segundos valido\n";
                    cin >> segundos1;
                }
            }
            horas = hora1;
            minutos = minutos1;
            segundos = segundos1;
        }

        void avanzarSegundo() {
            if(segundos == 59) {
                segundos = 0;
                if(minutos == 59) {
                    minutos = 0;
                    if(horas == 23) {
                        horas = 0;
                    } else {
                        horas++;
                    }
                } else {
                    minutos++;
                }
            } else {
                segundos++;
            }
        }

        void mostrarHora() {
            cout << formatearDato(horas) << " " << formatearDato(minutos) << " " << formatearDato(segundos) << endl;
        }
};
int main() {

    auto reloj = new Reloj(80, 47, 10);

    reloj->mostrarHora();

    reloj->avanzarSegundo();

    reloj->mostrarHora();

    return 0;
}