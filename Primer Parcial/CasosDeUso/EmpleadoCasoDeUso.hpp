#pragma once
#include "./Interfaces/IEmpleadoRepositorio.hpp"
#include "../Dominio/Empleado.hpp"
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

class EmpleadoCasoDeUso {
private:
    IEmpleadoRepositorio& repo;

    int generarNuevoId() {
        vector<Empleado> todos = repo.obtenerTodos();
        if (todos.empty()) return 1;
        int maxId = 0;
        for (const auto& e : todos) {
            if (e.getId() > maxId) maxId = e.getId();
        }
        return maxId + 1;
    }

public:
    EmpleadoCasoDeUso(IEmpleadoRepositorio& repositorio) : repo(repositorio) {}

    int agregarEmpleado(const string& nombre, const string& apellido,
                         const string& telefono, const string& cargo, double salario) {
        int nuevoId = generarNuevoId();
        Empleado nuevo(nombre, apellido, telefono, nuevoId, cargo, salario);
        repo.agregar(nuevo);
        return nuevoId;
    }

    void modificarEmpleado(int id, const string& nombre, const string& apellido,
                           const string& telefono, const string& cargo, double salario) {
        Empleado* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Empleado no encontrado.");
        existente->setNombre(nombre);
        existente->setApellido(apellido);
        existente->setTelefono(telefono);
        existente->setCargo(cargo);
        existente->setSalario(salario);
        repo.modificar(*existente);
        delete existente;
    }

    void eliminarEmpleado(int id) {
        Empleado* existente = repo.obtenerPorId(id);
        if (!existente) throw runtime_error("Empleado no encontrado.");
        repo.eliminar(id);
        delete existente;
    }

    vector<Empleado> listarTodos() { return repo.obtenerTodos(); }

    Empleado* buscarPorId(int id) { return repo.obtenerPorId(id); }

    double salarioPromedio() { return repo.calcularSalarioPromedio(); }

    Empleado empleadoConMayorSalario() { return repo.obtenerEmpleadoConMayorSalario(); }

    map<string, int> conteoPorCargo() {
        map<string, int> conteo;
        vector<Empleado> empleados = repo.obtenerTodos();
        for (const auto& emp : empleados) {
            conteo[emp.getCargo()]++;
        }
        return conteo;
    }
};