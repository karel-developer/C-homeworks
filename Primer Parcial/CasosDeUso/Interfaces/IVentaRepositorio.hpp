#pragma once
#include <vector>
#include <string>
#include "../../Dominio/Venta.hpp"
using namespace std;

class IVentaRepositorio {
    public:
        virtual void registrar(const Venta& sale) = 0;
        virtual void eliminar(int saleID) = 0;
        virtual vector<Venta> obtenerTodos() = 0;
        virtual Venta* obtenerPorId(int saleID) = 0;
        virtual vector<Venta> buscarPorClienteId(int clientID) = 0;
        virtual vector<Venta> buscarPorRangoFechas(const string& fechaInicio, const string& fechaFin) = 0;
};