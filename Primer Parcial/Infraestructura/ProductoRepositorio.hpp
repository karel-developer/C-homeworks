#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "../CasosDeUso/Interfaces/IProductoRepositorio.hpp"
#include "../Dominio/Producto.hpp"
#include "../Modulos/json.hpp"
using namespace std;
using json = nlohmann::json;

class ProductoRepositorio : public IProductoRepositorio {
private:
    string filename;
    int nextID = 1;
    json readJson() {
        ifstream file(filename);
        if (!file.is_open() || file.peek() == EOF) {
            return json::array();
        }
        json j;
        file >> j;
        return j;
    }
    void writeJson(const json& j) {
        ofstream file(filename);
        file << j.dump(4);
    }
    void updateNextID(const json& j) {
        for (const auto& elem : j) {
            if (elem.contains("id") && elem["id"].is_number()) {
                int id = elem["id"].get<int>();
                if (id >= nextID) nextID = id + 1;
            }
        }
    }

public:
    ProductoRepositorio(string path) : filename(path) {
        json data = readJson();
        updateNextID(data);
    }
    void agregar(const Producto& producto) override {
        json data = readJson();
        json productoJson = producto;
        data.push_back(productoJson);
        writeJson(data);
    }

    void modificar(const Producto& producto) override {
        json data = readJson();
        bool found = false;
        for (auto& elem : data) {
            if (elem["id"] == producto.getId()) {
                elem = producto;
                found = true;
                break;
            }
        }
        if (found) {
            writeJson(data);
        }
    }

    void eliminar(int productoId) override {
        json data = readJson();
        data.erase(remove_if(data.begin(), data.end(),
            [productoId](const json& elem) {
                return elem["id"] == productoId;
            }), data.end());
        writeJson(data);
    }

    vector<Producto> obtenerTodos() override {
        json data = readJson();
        return data.get<vector<Producto>>();
    }

    Producto* obtenerPorId(int productoId) override {
        json data = readJson();
        for (const auto& elem : data) {
            if (elem["id"] == productoId) {
                return new Producto(elem.get<Producto>());
            }
        }
        return nullptr;
    }

    vector<Producto> buscarPorNombre(const string& nombreParcial) override {
        json data = readJson();
        vector<Producto> resultados;
        for (const auto& elem : data) {
            if (elem["nombre"].get<string>().find(nombreParcial) != string::npos) {
                resultados.push_back(elem.get<Producto>());
            }
        }
        return resultados;
    }

    vector<Producto> buscarPorCategoria(const string& categoria) override {
        json data = readJson();
        vector<Producto> resultados;
        for (const auto& elem : data) {
            if (elem["categoria"].get<string>() == categoria) {
                resultados.push_back(elem.get<Producto>());
            }
        }
        return resultados;
    }

    vector<Producto> buscarPorRangoPrecios(double minPrecio, double maxPrecio) override {
        json data = readJson();
        vector<Producto> resultados;
        for (const auto& elem : data) {
            if (elem["precio"].get<double>() >= minPrecio && elem["precio"].get<double>() <= maxPrecio) {
                resultados.push_back(elem.get<Producto>());
            }
        }
        return resultados;
    }

    vector<Producto> buscarPorStockCritico(int umbral) override {
        json data = readJson();
        vector<Producto> resultados;
        for (const auto& elem : data) {
            if (elem["stock"].get<int>() < umbral) {
                resultados.push_back(elem.get<Producto>());
            }
        }
        return resultados;
    }

    Producto obtenerProductoMasCaro() override {
        json data = readJson();
        Producto masCaro = {};
        bool first = true;
        for (const auto& elem : data) {
            Producto p = elem.get<Producto>();
            if (first || p.getPrecio() > masCaro.getPrecio()) {
                masCaro = p;
                first = false;
            }
        }
        if (first) throw runtime_error("No hay productos para calcular el mas caro.");
        return masCaro;
    }

    Producto obtenerProductoMasBarato() override {
        json data = readJson();
        Producto masBarato = {};
        bool first = true;
        for (const auto& elem : data) {
            Producto p = elem.get<Producto>();
            if (first || p.getPrecio() < masBarato.getPrecio()) {
                masBarato = p;
                first = false;
            }
        }
        if (first) throw runtime_error("No hay productos para calcular el mas barato.");
        return masBarato;
    }
};
