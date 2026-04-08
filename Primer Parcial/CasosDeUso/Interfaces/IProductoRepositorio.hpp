#pragma once
#include <vector>
#include <string>
#include "../../Dominio/Producto.hpp"
using namespace std;

class IProductoRepositorio {
    public:
        virtual void agregar(const Producto& product) = 0;
        virtual void modificar(const Producto& product) = 0;
        virtual void eliminar(int productID) = 0;
        virtual vector<Producto> obtenerTodos() = 0;
        virtual Producto* obtenerPorId(int productID) = 0;
        virtual vector<Producto> buscarPorNombre(const string& name) = 0;
        virtual vector<Producto> buscarPorCategoria(const string& category) = 0;
        virtual vector<Producto> buscarPorRangoPrecios(double min, double max) = 0;
        virtual vector<Producto> buscarPorStockCritico(int limit) = 0;
        virtual Producto obtenerProductoMasCaro() = 0;
        virtual Producto obtenerProductoMasBarato() = 0;
};