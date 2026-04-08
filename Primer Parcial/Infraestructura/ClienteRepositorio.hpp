#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "../CasosDeUso/Interfaces/IClienteRepositorio.hpp"
#include "../Dominio/Cliente.hpp"
#include "../Modulos/json.hpp"
using namespace std;

using json = nlohmann::json;

class ClienteRepositorio : public IClienteRepositorio {
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

    json findClienteJsonById(int clienteId) {
        json data = readJson();
        for (const auto& elem : data) {
            if (elem["id"] == clienteId) {
                return elem;
            }
        }
        return json();
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
    ClienteRepositorio(string path) : filename(path) {}

    bool tieneCompras(int clienteId) {
        Cliente* c = obtenerPorId(clienteId);
        if (!c) return false;
        bool resultado = !c->getHistorial().empty();
        delete c;
        return resultado;
    }

    void agregar(const Cliente& cliente) override {
        json data = readJson();
        json clienteJson = cliente;
        data.push_back(clienteJson);
        writeJson(data);
    }

    void modificar(const Cliente& cliente) override {
        json data = readJson();
        bool found = false;
        for (auto& elem : data) {
            if (elem["id"] == cliente.getId()) {
                elem = cliente;
                found = true;
                break;
            }
        }
        if (found) {
            writeJson(data);
        }
    }

    void eliminar(int clienteId) override {
        json data = readJson();
        data.erase(remove_if(data.begin(), data.end(),
            [clienteId](const json& elem) {
                return elem["id"] == clienteId;
            }), data.end());
        writeJson(data);
    }

    vector<Cliente> obtenerTodos() override {
        json data = readJson();
        return data.get<vector<Cliente>>();
    }

    Cliente* obtenerPorId(int clienteId) override {
        json data = readJson();
        for (const auto& elem : data) {
            if (elem["id"] == clienteId) {
                return new Cliente(elem.get<Cliente>());
            }
        }
        return nullptr;
    }

    vector<Cliente> buscarPorMontoGastado(double monto) override {
        json data = readJson();
        vector<Cliente> resultados;
        for (const auto& elem : data) {
            Cliente c = elem.get<Cliente>();
            if (calcularTotalGastadoPorCliente(c.getId()) > monto) {
                resultados.push_back(c);
            }
        }
        return resultados;
    }

    vector<Cliente> buscarPorNumeroCompra(int numCompras) override {
        json data = readJson();
        vector<Cliente> resultados;
        for (const auto& elem : data) {
            Cliente c = elem.get<Cliente>();
            if (c.getHistorial().size() > numCompras) {
                resultados.push_back(c);
            }
        }
        return resultados;
    }

    double calcularTotalGastadoPorCliente(int clienteId) override {
        Cliente* clienteOpt = obtenerPorId(clienteId);
        if (!clienteOpt) {
            throw runtime_error("Cliente con ID " + to_string(clienteId) + " no encontrado.");
        }
        
        double totalGastado = 0.0;
        for (const auto& venta : clienteOpt->getHistorial()) {
            totalGastado += venta.getTotal();
        }
        delete clienteOpt;
        return totalGastado;
    }

    vector<Cliente> obtenerClientesConMasCompras(int n) override {
        auto todosClientes = obtenerTodos();
        sort(todosClientes.begin(), todosClientes.end(), [](const Cliente& a, const Cliente& b) {
            return a.getHistorial().size() > b.getHistorial().size();
        });
        
        vector<Cliente> topN;
        for (int i = 0; i < n && i < todosClientes.size(); ++i) {
            topN.push_back(todosClientes[i]);
        }
        return topN;
    }
};