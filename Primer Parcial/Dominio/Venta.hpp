#pragma once
#include <iostream>
#include <vector>
#include "./Producto.hpp"
#include "../Modulos/json.hpp"
using namespace std;

class Venta {
    private:
        int id;
        int compradorId;
        double total;
        string fecha;
        vector<Producto> productos;
    public:
        Venta(int ID, int sealerId , vector<Producto> products, string saleDate) {
            setId(ID);
            setCompradorId(sealerId);
            setProductos(products);
            setFecha(saleDate);
            total = calcularTotal();
        }
        Venta() : id(0), compradorId(0), total(0.0), fecha("") {}
        int getId() const { return id; }
        int getCompradorId() const { return compradorId; }
        double getTotal() const { return total; }
        string getFecha() const { return fecha; }
        const vector<Producto>& getProductos() const { return productos; }
        void setId(int ID) {
            if(ID < 0) __throw_invalid_argument("El id debe ser un numero no negativo\n");
            id = ID;
        }
        void setCompradorId(int ID) {
            if(ID < 0) __throw_invalid_argument("El id del comprador debe ser un numero no negativo\n");
            compradorId = ID;
        }
        void setFecha(const string& f) {
            if(f.length() < 10 || f.length() > 10) __throw_invalid_argument("La fecha debe contener 10 caracteres\n");
            for(int i = 0; i < 10; i++) {
                if(f[i] - '0' > 9 || f[i] - '0' < 0 && i != 4 && i != 7) {
                    __throw_invalid_argument("La fecha debe estar en formato YYYY-MM-DD\n");
                } else if(f[i] != '-' && (i == 4 || i == 7)) {
                    __throw_invalid_argument("La fecha debe estar en formato YYYY-MM-DD\n");
                }
            }
            fecha = f;
        }
        void setProductos(const vector<Producto>& products) {
            if(products.size() == 0) __throw_invalid_argument("El listado de productos de la compra no puede estar vacio\n");
            productos = products;
        }
        void mostrarResumen() {
            cout << "------------------------\n";
            cout << "Fecha: " << fecha << '\n';
            cout << "Importe: " << getTotal() << '\n';
            cout << "Identificador: " << getId() << '\n';
            for(Producto product : productos) product.mostrarProducto();
        }
        double calcularTotal() {
            double suma = 0.0;
            for(Producto product : productos) {
                suma += product.getPrecio();
            }
            return suma;
        }
    };

    inline void to_json(nlohmann::json& j, const Venta& v) {
        j = nlohmann::json{
            {"id", v.getId()},
            {"compradorId", v.getCompradorId()},
            {"fecha", v.getFecha()},
            {"productos", v.getProductos()},
            {"total", v.getTotal()},
        };
    }

    inline void from_json(const nlohmann::json& j, Venta& v) {
        v.setId(j.at("id").get<int>());
        v.setCompradorId(j.at("compradorId").get<int>());
        v.setFecha(j.at("fecha").get<string>());
        v.setProductos(j.at("productos").get<vector<Producto>>());
    }
