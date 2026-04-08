#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../CasosDeUso/Interfaces/IEmpleadoRepositorio.hpp"
#include "../Dominio/Empleado.hpp"
#include "../Modulos/json.hpp"
using namespace std;

using json = nlohmann::json;

class EmpleadoRepositorio : public IEmpleadoRepositorio {
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
        for (const auto& elem : j) {
            if (elem.contains("id") && elem["id"].is_number()) {
                int id = elem["id"].get<int>();
                if (id >= nextID) nextID = id + 1;
            }
        }
    }
    public:
        EmpleadoRepositorio(string path) : fileName(path) {
            json data = readJson();
            updateNextID(data);
        }

        void agregar(const Empleado& employee) override {
            json data = readJson();
            json empleadoJson = employee;
            data.push_back(empleadoJson);
            writeJson(data);
        }

        void modificar(const Empleado& employee) override {
            json data = readJson();
            bool found = false;
            for (auto& elem : data) {
                if (elem["id"] == employee.getId()) {
                    elem = employee;
                    found = true;
                    break;
                }
            }
            if (found) {
                writeJson(data);
            }
        }

        void eliminar(int employeeId) override {
            json data = readJson();
            data.erase(remove_if(data.begin(), data.end(),
                [employeeId](const json& elem) {
                    return elem["id"] == employeeId;
                }), data.end());
            writeJson(data);
        }

        vector<Empleado> obtenerTodos() override {
            json data = readJson();
            return data.get<vector<Empleado>>();
        }

        Empleado* obtenerPorId(int employeeID) override {
            json data = readJson();
            for (const auto& elem : data) {
                if (elem["id"] == employeeID) {
                    return new Empleado(elem.get<Empleado>());
                }
            }
            return nullptr;
        }

        double calcularSalarioPromedio() override {
            json data = readJson();
            int suma = 0;
            for(const auto& element : data) {
                suma += element["salario"].get<double>();
            }
            return (double) suma / data.size();
        }
        Empleado obtenerEmpleadoConMayorSalario() override {
            json data = readJson();
            if (data.empty()) throw runtime_error("No hay empleados.");
            Empleado mayor;
            double maxSalario = -1.0;
            for (const auto& elem : data) {
                Empleado e = elem.get<Empleado>();
                if (e.getSalario() > maxSalario) {
                    maxSalario = e.getSalario();
                    mayor = e;
                }
            }
            return mayor;
        }

};