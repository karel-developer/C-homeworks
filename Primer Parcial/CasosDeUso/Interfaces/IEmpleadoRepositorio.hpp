#pragma once
#include <vector>
#include <string>
#include "../../Dominio/Empleado.hpp"
using namespace std;

class IEmpleadoRepositorio {
    public:
        virtual void agregar(const Empleado& employee) = 0;
        virtual void modificar(const Empleado& employee) = 0;
        virtual void eliminar(int employeeID) = 0;
        virtual vector<Empleado> obtenerTodos() = 0;
        virtual Empleado* obtenerPorId(int employeeID) = 0;
        virtual double calcularSalarioPromedio() = 0;
        virtual Empleado obtenerEmpleadoConMayorSalario() = 0;
};