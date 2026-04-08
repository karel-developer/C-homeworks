#pragma once
#include "../Infraestructura/ClienteRepositorio.hpp"
#include "../Dominio/Cliente.hpp"
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

class ClienteCasoDeUso {
private:
    ClienteRepositorio& repo;

    int generarNuevoId() {
        vector<Cliente> todos = repo.obtenerTodos();
        if (todos.empty()) return 1;
        int maxId = 0;
        for (const auto& c : todos) {
            if (c.getId() > maxId) maxId = c.getId();
        }
        return maxId + 1;
    }

public:
    ClienteCasoDeUso(ClienteRepositorio& repositorio) : repo(repositorio) {}

    int agregarCliente(const string& nombre, const string& apellido,
                        const string& telefono, const string& correo) {
        int nuevoId = generarNuevoId();
        Cliente nuevo(nombre, apellido, telefono, nuevoId, correo, vector<Venta>());
        repo.agregar(nuevo);
        return nuevoId;
    }

    void modificarCliente(int id, const string& nombre, const string& apellido,
                          const string& telefono, const string& correo) {
        Cliente* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Cliente no encontrado.");
        existente->setNombre(nombre);
        existente->setApellido(apellido);
        existente->setTelefono(telefono);
        existente->setCorreo(correo);
        repo.modificar(*existente);
        delete existente;
    }

    void eliminarCliente(int id) {
        Cliente* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Cliente no encontrado.");
        if (!existente->getHistorial().empty()) {
            throw runtime_error("No se puede eliminar un cliente con compras registradas.");
        }
        repo.eliminar(id);
        delete existente;
    }

    vector<Cliente> listarTodos() { return repo.obtenerTodos(); }

    Cliente* buscarPorId(int id) { return repo.obtenerPorId(id); }

    vector<Cliente> filtrarPorMontoGastado(double montoMinimo) {
        return repo.buscarPorMontoGastado(montoMinimo);
    }

    vector<Cliente> filtrarPorNumeroCompras(int minimoCompras) {
        return repo.buscarPorNumeroCompra(minimoCompras);
    }

    double totalGastadoPorCliente(int id) {
        Cliente* c = repo.obtenerPorId(id);
        if (!c) throw runtime_error("Cliente no encontrado.");
        return repo.calcularTotalGastadoPorCliente(id);
    }

    vector<Cliente> topCompradores(int n) {
        return repo.obtenerClientesConMasCompras(n);
    }
};