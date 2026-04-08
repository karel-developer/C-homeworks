#pragma once
#include <iostream>
#include "./Persona.hpp"
#include "../Modulos/json.hpp"
using namespace std;
class Empleado : public Persona {
    private:
        string cargo;
        double salario;
    public:
        Empleado(string name, string lastName, string phoneNumber, int id, string duty, double salary)
            : Persona(name, lastName, phoneNumber, id) {
                setCargo(duty);
                setSalario(salary);
        }
        Empleado() : cargo(""), salario(0.0) { }
        string getCargo() const { return cargo; }
        double getSalario() const { return salario; }
        void setCargo(string duty) { cargo = duty; }
        void setSalario(double salary) {
            if(salary < 0) __throw_invalid_argument("El salario debe ser un numero no negativo\n");
            salario = salary;
        }
        void mostrarInformacion() const override {
            cout << "------------------------\n";
            cout << "ID: " << getId() << '\n';
            cout << "Nombre: " << getNombre() << '\n';
            cout << "Apellido: " << getApellido() << '\n';
            cout << "Telefono: " << getTelefono() << '\n';
            cout << "Cargo: " << getCargo() << '\n';
            cout << "Salario: " << getSalario() << '\n';
            cout << "------------------------\n";
        }
        void actualizarSalario(double salary) { setSalario(salary); }
    };

    inline void to_json(nlohmann::json& j, const Empleado& e) {
        j = nlohmann::json{
            {"id", e.getId()},
            {"nombre", e.getNombre()},
            {"apellido", e.getApellido()},
            {"telefono", e.getTelefono()},
            {"cargo", e.getCargo()},
            {"salario", e.getSalario()}
        };
    }

    inline void from_json(const nlohmann::json& j, Empleado& e) {
        e.setId(j.at("id").get<int>());
        e.setNombre(j.at("nombre").get<string>());
        e.setApellido(j.at("apellido").get<string>());
        e.setTelefono(j.at("telefono").get<string>());
        e.setCargo(j.at("cargo").get<string>());
        e.setSalario(j.at("salario").get<double>());
    }
