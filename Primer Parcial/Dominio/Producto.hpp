#pragma once
#include <iostream>
#include "../Modulos/json.hpp"
using namespace std;

class Producto {
    private:
        string nombre;
        string categoria;
        int id;
        int stock;
        double precio;
    public:
        Producto(string name, string category, int ID, int disponibility, double price) {
            setNombre(name);
            setCategoria(category);
            setId(ID);
            setStock(disponibility);
            setPrecio(price);
        }
        Producto() : nombre(""), categoria(""), id(0), stock(0), precio(0.1) { }

        string getNombre() const { return nombre; }
        string getCategoria() const { return categoria; }
        int getId() const { return id; }
        double getPrecio() const { return precio; }
        double getStock() const { return stock; }
        void setNombre(string name) { nombre = name; }
        void setCategoria(string category) { categoria = category; }
        void setId(int ID) {
            if(ID < 0) __throw_invalid_argument("El id debe ser un numero no negativo\n");
            id = ID;
        }
        void setPrecio(double price) {
            if(price <= 0) __throw_invalid_argument("El precio debe ser un valor positivo\n");
            precio = price;
        }
        void setStock(int disponibility) {
            if(disponibility < 0) __throw_invalid_argument("El stock debe ser 0 o mas\n");
            stock = disponibility;
        }
        void actualizarStock(int change) {
            if(stock + change < 0) __throw_invalid_argument("Ha superado el stock\n");
            stock += change;
        }
        void mostrarProducto() {
            cout << "ID: " << getId() << '\n';
            cout << "Nombre: " << getNombre() << '\n';
            cout << "Categoria: " << getCategoria() << '\n';
            cout << "Precio: " << getPrecio() << '\n';
            cout << "Stock: " << getStock() << '\n';
            cout << "------------------------\n";
        }
    };

    inline void to_json(nlohmann::json& j, const Producto& p) {
        j = nlohmann::json{
            {"id", p.getId()},
            {"categoria", p.getCategoria()},
            {"nombre", p.getNombre()},
            {"precio", p.getPrecio()},
            {"stock", p.getStock()}
        };
    }

    inline void from_json(const nlohmann::json& j, Producto& p) {
        p.setId(j.at("id").get<int>());
        p.setCategoria(j.at("categoria").get<string>());
        p.setNombre(j.at("nombre").get<string>());
        p.setPrecio(j.at("precio").get<double>());
        p.setStock(j.at("stock").get<int>());
    }
