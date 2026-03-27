#include <bits/stdc++.h>
using namespace std;

class Contacto {
        
    public:
        string nombre, email, telefono;
        Contacto(string n, string e, string t) {
            nombre = n;
            email = e;
            telefono = t;
        }
};

class Agenda {
    public:
        vector<Contacto> contactos;
        Agenda(const vector<Contacto>& cont) {
            contactos = cont;
        }

        void agregar(Contacto a) {
            for(auto x : contactos) {
                if(x.nombre == a.nombre) {
                    cout << "Contacto existente\n";
                    return;
                }
            }
            contactos.push_back(a);
        }

        void eliminar(string name) {
            for(size_t i = 0; i < contactos.size(); i++) {
                if(contactos[i].nombre == name) {
                    contactos.erase(contactos.begin() + i);
                    return;
                }
            }
            cout << "No existe ese contacto\n";
        }

        void buscar(string name) {
            for(auto x : contactos) {
                if(x.nombre == name) {
                    cout << x.nombre << "\n" << x.email << "\n" << x.telefono << "\n";
                    return;
                }
            }
            cout << "No se encontro el contacto\n";
        }

        void mostrarTodos() {
            for(auto x : contactos){
                cout << "----------------" << endl;
                cout << x.nombre << endl;
                cout << x.email << endl;
                cout << x.telefono << endl;
            }
        }
};
int main() {

    vector<Contacto> cont;

    Contacto a("a", "b", "c");
    cont.push_back(a);

    Agenda age(cont);

    age.mostrarTodos();
    

    return 0;
}