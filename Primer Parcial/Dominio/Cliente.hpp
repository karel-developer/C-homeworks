#pragma once
#include <iostream>
#include <vector>
#include "./Persona.hpp"
#include "./Venta.hpp"
#include "../Modulos/json.hpp"
using namespace std;

class Cliente : public Persona {
    private:
        string correo;
        vector<Venta> historialCompras;
    public:
        Cliente(string name, string lastName, string phoneNumber, int id, string email, const vector<Venta>& history)
            : Persona(name, lastName, phoneNumber, id) {
                setCorreo(email);
                setHistorial(history);
        }
        Cliente() : correo("example@email.com"), Persona("", "", "00000000", 0) { }
        string getCorreo() const { return correo; }
        const vector<Venta>& getHistorial() const { return historialCompras; }
        void setCorreo(string email) {
            if(email.find_first_of('@') == email.npos) {
                __throw_invalid_argument("El email deberia contener un caracter de arroba\n");
            }
            if(email.find_first_of('.') == email.npos) {
                __throw_invalid_argument("El email deberia contener un caracter de punto\n");
            }
            correo = email;
        }
        void setHistorial(const vector<Venta>& history) { historialCompras = history; }

        void mostrarHistorial() const {
            cout << "Historial de Compra:" << '\n';
            for(Venta v : historialCompras) {
                v.mostrarResumen();
            }
        }
        void mostrarInformacion() const override {
            cout << "------------INFORMACION-DEL-CLIENTE------------\n";
            cout << "Nombre: " << getNombre() << '\n';
            cout << "Apellido: " << getApellido() << '\n';
            cout << "Telefono: " << getTelefono() << '\n';
            mostrarHistorial();
        }

        void agregarCompra(Venta v) {
            historialCompras.push_back(v);
        }
    };

inline void to_json(nlohmann::json& j, const Cliente& c) {
    j = nlohmann::json{
        {"id", c.getId()},
        {"nombre", c.getNombre()},
        {"apellido", c.getApellido()},
        {"telefono", c.getTelefono()},
        {"correo", c.getCorreo()},
        {"historialCompras", c.getHistorial()}
    };
}

inline void from_json(const nlohmann::json& j, Cliente& c) {
    c.setId(j.at("id").get<int>());
    c.setNombre(j.at("nombre").get<string>());
    c.setApellido(j.at("apellido").get<string>());
    c.setTelefono(j.at("telefono").get<string>());
    c.setCorreo(j.at("correo").get<string>());
    c.setHistorial(j.at("historialCompras").get<vector<Venta>>());
}