#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "../../CasosDeUso/EmpleadoCasoDeUso.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void menuEmpleado(EmpleadoCasoDeUso& empleadoUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========== GESTION DE EMPLEADOS ==========\n";
        cout << " 1. Agregar empleado\n";
        cout << " 2. Modificar empleado\n";
        cout << " 3. Eliminar empleado\n";
        cout << " 4. Listar todos los empleados\n";
        cout << " 5. Buscar empleado por ID\n";
        cout << " 6. Salario promedio\n";
        cout << " 7. Empleado con mayor salario\n";
        cout << " 8. Conteo por cargo\n";
        cout << " 9. Volver al menu principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();
        try {
            switch (opcion) {
                case 1: {
                    string nombre, apellido, telefono, cargo;
                    double salario;
                    cout << "Nombre: "; nombre = leerString();
                    cout << "Apellido: "; apellido = leerString();
                    cout << "Telefono: "; telefono = leerString();
                    cout << "Cargo: "; cargo = leerString();
                    cout << "Salario: "; salario = leerDouble();
                    int nuevoId = empleadoUC.agregarEmpleado(nombre, apellido, telefono, cargo, salario);
                    cout << "\nEmpleado agregado exitosamente con ID: " << nuevoId << '\n';
                    break;
                }
                case 2: {
                    int id; string nombre, apellido, telefono, cargo;
                    double salario;
                    cout << "ID del empleado: "; id = leerEntero();
                    cout << "Nuevo nombre: "; nombre = leerString();
                    cout << "Nuevo apellido: "; apellido = leerString();
                    cout << "Nuevo telefono: "; telefono = leerString();
                    cout << "Nuevo cargo: "; cargo = leerString();
                    cout << "Nuevo salario: "; salario = leerDouble();
                    empleadoUC.modificarEmpleado(id, nombre, apellido, telefono, cargo, salario);
                    cout << "\nEmpleado modificado exitosamente.\n";
                    break;
                }
                case 3: {
                    int id;
                    cout << "ID del empleado a eliminar: "; id = leerEntero();
                    empleadoUC.eliminarEmpleado(id);
                    cout << "\nEmpleado eliminado exitosamente.\n";
                    break;
                }
                case 4: {
                    vector<Empleado> empleados = empleadoUC.listarTodos();
                    if (empleados.empty()) cout << "\nNo hay empleados registrados.\n";
                    else for (auto& e : empleados) e.mostrarInformacion();
                    break;
                }
                case 5: {
                    int id;
                    cout << "ID del empleado: "; id = leerEntero();
                    Empleado* e = empleadoUC.buscarPorId(id);
                    if (e) {
                        e->mostrarInformacion();
                        delete e;
                    }
                    else cout << "\nEmpleado no encontrado.\n";
                    break;
                }
                case 6: {
                    double promedio = empleadoUC.salarioPromedio();
                    cout << "\nSalario promedio: $" << fixed << setprecision(2) << promedio << "\n";
                    break;
                }
                case 7: {
                    Empleado mejor = empleadoUC.empleadoConMayorSalario();
                    mejor.mostrarInformacion();
                    break;
                }
                case 8: {
                    map<string, int> conteo = empleadoUC.conteoPorCargo();
                    cout << "\nConteo por cargo:\n";
                    for (auto& par : conteo) {
                        cout << par.first << ": " << par.second << "\n";
                    }
                    break;
                }
                case 9:
                    break;
                default:
                    cout << "\nOpcion invalida.\n";
            }
        } catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
        }
        if (opcion != 9) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 9);
}