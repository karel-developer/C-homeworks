#include <bits/stdc++.h>
using namespace std;

bool validarFecha(int d, int m, int a) {
            if(d < 1 || d > 31 || m < 1 || m > 12 || a < 0) {
                return false;
            }
            switch(m) {
                case 2:
                    if(d > 29) return false;
                    else if(!((a % 4 == 0 && a % 100 != 0) || a % 400 == 0) && d == 29) return false;
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if(d > 30) return false;
                    break;
            }
            return true;
}

class Fecha {
    private:
        int dia, mes, ano;
    public:
        Fecha(int d, int m, int a) {
            int d1 = d;
            int m1 = m;
            int a1 = a;
            if(!validarFecha(d1,m1,a1)) {
                while(!validarFecha(d1,m1,a1)) {
                    cout << "Fecha invalida\n";
                    cout << "Ingrese un dia correcto\n";
                    cin >> d1;
                    cout << "Ingrese un mes correcto\n";
                    cin >> m1;
                    cout << "Ingrese un ano correcto\n";
                    cin >> a1;
                }
            }
            dia = d1;
            mes = m1;
            ano = a1;
        }

        void avanzarDia() {
            dia++;
            switch(mes) {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                    if(dia == 32) {
                        dia = 1;
                        mes++;
                        return;
                    }
                case 12:
                    if(dia == 32) {
                        dia = 1;
                        mes = 1;
                        ano++;
                        return;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if(dia == 31) {
                        dia = 1;
                        mes++;
                        return;
                    }
                    break;
                case 2:
                    if(((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && dia == 30) {
                        dia = 1;
                        mes++;
                        return;
                    } else if(((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) && dia == 29) {
                        dia = 1;
                        mes++;
                        return;
                    }
            }
        }
        void mostrarFecha() {
            cout << dia << " " << mes << " " << ano;
        }
};

int main() {

    Fecha dia(31,12,2024);

    dia.avanzarDia();

    dia.mostrarFecha();

    return 0;
}