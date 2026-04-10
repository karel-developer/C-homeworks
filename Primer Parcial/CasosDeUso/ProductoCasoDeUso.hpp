#pragma once
#include "./Interfaces/IProductoRepositorio.hpp"
#include "../Dominio/Producto.hpp"
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>
using namespace std;

class ProductoCasoDeUso {
private:
    IProductoRepositorio& repo;

    int generarNuevoId() {
        vector<Producto> todos = repo.obtenerTodos();
        if (todos.empty()) return 1;
        int maxId = 0;
        for (const auto& p : todos) {
            if (p.getId() > maxId) maxId = p.getId();
        }
        return maxId + 1;
    }

public:
    ProductoCasoDeUso(IProductoRepositorio& repositorio) : repo(repositorio) {}

    int agregarProducto(const string& nombre, const string& categoria,
                         double precio, int stock) {
        int nuevoId = generarNuevoId();
        Producto nuevo(nombre, categoria, nuevoId, stock, precio);
        repo.agregar(nuevo);
        return nuevoId;
    }

    void modificarProducto(int id, const string& nombre, const string& categoria,
                           double precio, int stock) {
        Producto* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Producto no encontrado.");
        existente->setNombre(nombre);
        existente->setCategoria(categoria);
        existente->setPrecio(precio);
        existente->setStock(stock);
        repo.modificar(*existente);
        delete existente;
    }

    void eliminarProducto(int id) {
        Producto* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Producto no encontrado.");
        repo.eliminar(id);
        delete existente;
    }

    vector<Producto> listarTodos() { return repo.obtenerTodos(); }

    Producto* buscarPorId(int id) { return repo.obtenerPorId(id); }

    vector<Producto> buscarPorNombre(const string& parcial) {
        return repo.buscarPorNombre(parcial);
    }

    vector<Producto> buscarPorCategoria(const string& cat) {
        return repo.buscarPorCategoria(cat);
    }

    vector<Producto> buscarPorRangoPrecios(double min, double max) {
        return repo.buscarPorRangoPrecios(min, max);
    }

    vector<Producto> stockCritico(int umbral) {
        return repo.buscarPorStockCritico(umbral);
    }

    Producto productoMasCaro() { return repo.obtenerProductoMasCaro(); }

    Producto productoMasBarato() { return repo.obtenerProductoMasBarato(); }

    double costoTotalInventario() {
        double total = 0.0;
        vector<Producto> productos = repo.obtenerTodos();
        for (const auto& p : productos) {
            total += p.getPrecio() * p.getStock();
        }
        return total;
    }

    map<string, double> precioPromedioPorCategoria() {
        map<string, pair<double, int>> acum;
        vector<Producto> productos = repo.obtenerTodos();
        for (const auto& p : productos) {
            acum[p.getCategoria()].first += p.getPrecio();
            acum[p.getCategoria()].second++;
        }
        map<string, double> promedios;
        for (auto& it : acum) {
            promedios[it.first] = it.second.first / it.second.second;
        }
        return promedios;
    }
};