#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "../../CasosDeUso/ClienteCasoDeUso.hpp"
#include "../../Dominio/Cliente.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void menuCliente(ClienteCasoDeUso& clienteUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========== GESTION DE CLIENTES ==========\n";
        cout << " 1. Agregar cliente\n";
        cout << " 2. Modificar cliente\n";
        cout << " 3. Eliminar cliente\n";
        cout << " 4. Listar todos los clientes\n";
        cout << " 5. Buscar cliente por ID\n";
        cout << " 6. Filtrar por monto gastado\n";
        cout << " 7. Filtrar por numero de compras\n";
        cout << " 8. Total gastado por cliente\n";
        cout << " 9. Top compradores\n";
        cout << "10. Volver al menu principal\n";
        cout << "=========================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();
        try {
            switch (opcion) {
                case 1: {
                    string nombre, apellido, telefono, correo;
                    cout << "Nombre: "; nombre = leerString();
                    cout << "Apellido: "; apellido = leerString();
                    cout << "Telefono: "; telefono = leerString();
                    cout << "Correo: "; correo = leerString();
                    int nuevoId = clienteUC.agregarCliente(nombre, apellido, telefono, correo);
                    cout << "\nCliente agregado exitosamente con ID: " << nuevoId << '\n';
                    break;
                }
                case 2: {
                    int id; string nombre, apellido, telefono, correo;
                    cout << "ID del cliente: "; id = leerEntero();
                    cout << "Nuevo nombre: "; nombre = leerString();
                    cout << "Nuevo apellido: "; apellido = leerString();
                    cout << "Nuevo telefono: "; telefono = leerString();
                    cout << "Nuevo correo: "; correo = leerString();
                    clienteUC.modificarCliente(id, nombre, apellido, telefono, correo);
                    cout << "\nCliente modificado exitosamente.\n";
                    break;
                }
                case 3: {
                    int id;
                    cout << "ID del cliente a eliminar: "; id = leerEntero();
                    clienteUC.eliminarCliente(id);
                    cout << "\nCliente eliminado exitosamente.\n";
                    break;
                }
                case 4: {
                    vector<Cliente> clientes = clienteUC.listarTodos();
                    if (clientes.empty()) {
                        cout << "\nNo hay clientes registrados.\n";
                    } else {
                        cout << "\nLista de clientes:\n";
                        for (const auto& c : clientes) {
                            c.mostrarInformacion();
                        }
                    }
                    break;
                }
                case 5: {
                    int id;
                    cout << "ID del cliente: "; id = leerEntero();
                    Cliente* c = clienteUC.buscarPorId(id);
                    if (c) {
                        c->mostrarInformacion();
                        delete c;
                    }
                    else cout << "\nCliente no encontrado.\n";
                    break;
                }
                case 6: {
                    double monto;
                    cout << "Monto minimo gastado: "; monto = leerDouble();
                    vector<Cliente> resultados = clienteUC.filtrarPorMontoGastado(monto);
                    if (resultados.empty()) cout << "\nNingun cliente supera ese monto.\n";
                    else for (auto& c : resultados) c.mostrarInformacion();
                    break;
                }
                case 7: {
                    int compras;
                    cout << "Numero minimo de compras: "; compras = leerEntero();
                    vector<Cliente> resultados = clienteUC.filtrarPorNumeroCompras(compras);
                    if (resultados.empty()) cout << "\nNingun cliente alcanza esas compras.\n";
                    else for (auto& c : resultados) c.mostrarInformacion();
                    break;
                }
                case 8: {
                    int id;
                    cout << "ID del cliente: "; id = leerEntero();
                    double total = clienteUC.totalGastadoPorCliente(id);
                    cout << "\nTotal gastado: $" << fixed << setprecision(2) << total << "\n";
                    break;
                }
                case 9: {
                    int n;
                    cout << "Cantidad de top compradores: "; n = leerEntero();
                    vector<Cliente> top = clienteUC.topCompradores(n);
                    if (top.empty()) cout << "\nNo hay clientes.\n";
                    else for (auto& c : top) c.mostrarInformacion();
                    break;
                }
                case 10:
                    break;
                default:
                    cout << "\nOpcion invalida.\n";
            }
        } catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
        }
        if (opcion != 10) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 10);
}