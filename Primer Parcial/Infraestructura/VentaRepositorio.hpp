#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../CasosDeUso/Interfaces/IVentaRepositorio.hpp"
#include "../Dominio/Venta.hpp"
#include "../Modulos/json.hpp"
using namespace std;
using json = nlohmann::json;

class VentaRepositorio : public IVentaRepositorio {
    private:
        string fileName;
        int nextID = 1;
        json readJson() {
            ifstream file(fileName);
            if(!file.is_open() || file.peek() == EOF) {
                return json::array();
            }
            json j;
            file >> j;
            return j;
        }

        void writeJson(const json& j) {
            ofstream file(fileName);
            file << j.dump(4);
        }

        void updateNextID(const json& j) {
            for (const auto& element : j) {
                if (element["id"].is_number()) {
                    int id = element["id"].get<int>();
                    if (id >= nextID) nextID = id + 1;
                }
            }
        }
    public:
        VentaRepositorio(string path) : fileName(path) {
            json data = readJson();
            updateNextID(data);
        }

        void registrar(const Venta& sale) override {
            json data = readJson();
            json ventaJson = sale;
            data.push_back(ventaJson);
            writeJson(data);
        }

        void eliminar(int saleID) override {
            json data = readJson();
            data.erase(remove_if(data.begin(), data.end(),
            [saleID] (const json& element) {
                return element["id"] == saleID;
            }), data.end());
            writeJson(data);
        }
        vector<Venta> obtenerTodos() override {
            json data = readJson();
            return data.get<vector<Venta>>();
        }
        Venta* obtenerPorId(int saleID) override {
            json data = readJson();
            for(const auto& element : data) {
                if(element["id"] == saleID) {
                    return new Venta(element.get<Venta>());
                }
            }
            return nullptr;
        }
        vector<Venta> buscarPorClienteId(int clientID) override {
            json data = readJson();
            vector<Venta> results;
            for(const auto& element : data) {
                if(element["compradorId"] == clientID) {
                    results.push_back(element.get<Venta>());
                }
            }
            return results;
        }
        vector<Venta> buscarPorRangoFechas(const string& fechaInicio, const string& fechaFin) override {
            json data = readJson();
            vector<Venta> resultados;
            for (const auto& elem : data) {
                Venta v = elem.get<Venta>();
                string fechaVenta = v.getFecha();
                if (fechaVenta >= fechaInicio && fechaVenta <= fechaFin) {
                    resultados.push_back(v);
                }
            }
            return resultados;
        }
};