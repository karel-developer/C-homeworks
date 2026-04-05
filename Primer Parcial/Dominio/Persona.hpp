#pragma once
#include <string>
#include <stdexcept>
#include "../Modulos/json.hpp"
using namespace std;

class Persona {
    protected:
        string nombre;
        string apellido;
        string telefono;
        int id;
    public:
        Persona(string name, string lastName, string phoneNumber, int ID) {
            setNombre(name);
            setApellido(lastName);
            setTelefono(phoneNumber);
            setId(ID);
        }
        Persona() : nombre(""), apellido(""), telefono("00000000"), id(0) { }
        string getNombre() const { return nombre;}
        string getApellido() const { return apellido; }
        string getTelefono() const { return telefono; }
        int getId() const { return id; }
        void setNombre(string name) { nombre = name; }
        void setApellido(string lastName) { apellido = lastName; }
        void setTelefono(string phoneNumber) {
            if(phoneNumber.length() < 8) { 
                __throw_invalid_argument("El numero de telefono debe tener al menos 8 caracteres.\n");
            }
            for(const char l : phoneNumber) {
                if(l - '0' > 9 || l - '0' < 0) {
                    __throw_invalid_argument("El numero de telefono no debe contener ninguna letra del abecedario.\n");
                }
            }
            telefono = phoneNumber;
        }
        void setId(int ID) {
            if(ID < 0) __throw_invalid_argument("El id debe ser un numero no negativo\n");
            id = ID;
        }
        virtual void mostrarInformacion() const = 0;
        virtual ~Persona() = default;
    };

inline void to_json(nlohmann::json& j, const Persona& p) {
    j = nlohmann::json{
        {"id", p.getId()},
        {"nombre", p.getNombre()},
        {"apellido", p.getApellido()},
        {"telefono", p.getTelefono()}
    };
}

inline void from_json(const nlohmann::json& j, Persona& p) {
    p.setId(j.at("id").get<int>());
    p.setNombre(j.at("nombre").get<string>());
    p.setApellido(j.at("apellido").get<string>());
    p.setTelefono(j.at("telefono").get<string>());
}