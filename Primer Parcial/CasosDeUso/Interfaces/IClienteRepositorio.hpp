#pragma once
#include <vector>
#include <string>
#include "../../Dominio/Cliente.hpp"
using namespace std;

class IClienteRepositorio {
    public:
        virtual void agregar(const Cliente& client) = 0;
        virtual void modificar(const Cliente& client) = 0;
        virtual void eliminar(int clientID) = 0;
        virtual vector<Cliente> obtenerTodos() = 0;
        virtual Cliente* obtenerPorId(int clientID) = 0;
        virtual vector<Cliente> buscarPorMontoGastado(double check) = 0;
        virtual vector<Cliente> buscarPorNumeroCompra(int sales) = 0;
        virtual double calcularTotalGastadoPorCliente(int clientID) = 0;
        virtual vector<Cliente> obtenerClientesConMasCompras(int n) = 0;
};