#include <bits/stdc++.h>
using namespace std;

class Estudiante {
    public:
        string nombre, carnet;
        vector<float> calificaciones;
        Estudiante(string name, string dni) {
            nombre = name;
            carnet = dni;
        }
        void agregarCalificacion(double nota) {
                if (nota < 0 || nota > 100) {
                    cout << "Calificacion invalida\n";
                    return;
                }
                calificaciones.push_back(nota);
        }

        double calcularPromedio() {
            if (calificaciones.empty()) return 0.0;
            double suma = 0.0;
            for (double c : calificaciones) suma += c;
            return suma / calificaciones.size();
        }

};
int main() {

    Estudiante e("Juan Perez", "2023001");
    e.agregarCalificacion(85);
    e.agregarCalificacion(92);
    e.agregarCalificacion(78);
    cout << "Promedio de " << e.nombre << ": " << e.calcularPromedio() << endl;

    return 0;
}