#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../../CasosDeUso/VentaCasoDeUso.hpp"
#include "../../CasosDeUso/ClienteCasoDeUso.hpp"
#include "../../CasosDeUso/ProductoCasoDeUso.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void menuVenta(VentaCasoDeUso& ventaUC, ClienteCasoDeUso& clienteUC, ProductoCasoDeUso& productoUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========== GESTION DE VENTAS ==========\n";
        cout << " 1. Registrar venta\n";
        cout << " 2. Eliminar venta\n";
        cout << " 3. Listar todas las ventas\n";
        cout << " 4. Buscar venta por ID\n";
        cout << " 5. Ventas por cliente\n";
        cout << " 6. Ventas por rango de fechas\n";
        cout << " 7. Volver al menu principal\n";
        cout << "=======================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();
        try {
            switch (opcion) {
                case 1: {
                    int clienteId;
                    cout << "ID del cliente: "; clienteId = leerEntero();
                    if (!clienteUC.buscarPorId(clienteId)) {
                        cout << "\nCliente no existe.\n";
                        break;
                    }
                    vector<int> idsProductos;
                    char continuar;
                    do {
                        int prodId;
                        cout << "ID del producto: "; prodId = leerEntero();
                        if (productoUC.buscarPorId(prodId)) {
                            idsProductos.push_back(prodId);
                        } else {
                            cout << "Producto no existe.\n";
                        }
                        cout << "Agregar otro producto? (s/n): "; continuar = leerCharacter();
                    } while (continuar == 's' || continuar == 'S');
                    if (idsProductos.empty()) {
                        cout << "\nNo se agregaron productos, venta cancelada.\n";
                        break;
                    }
                    string fecha;
                    cout << "Fecha (YYYY-MM-DD): "; fecha = leerString();
                    ventaUC.registrarVenta(clienteId, idsProductos, fecha);
                    cout << "\nVenta registrada exitosamente.\n";
                    break;
                }
                case 2: {
                    int id;
                    cout << "ID de la venta a eliminar: "; id = leerEntero();
                    ventaUC.eliminarVenta(id);
                    cout << "\nVenta eliminada (stock revertido).\n";
                    break;
                }
                case 3: {
                    vector<Venta> ventas = ventaUC.listarTodas();
                    if (ventas.empty()) cout << "\nNo hay ventas registradas.\n";
                    else for (auto& v : ventas) v.mostrarResumen();
                    break;
                }
                case 4: {
                    int id;
                    cout << "ID de la venta: "; id = leerEntero();
                    Venta* v = ventaUC.buscarPorId(id);
                    if (v) {
                        v->mostrarResumen();
                        delete v;
                    }
                    else cout << "\nVenta no encontrada.\n";
                    break;
                }
                case 5: {
                    int clienteId;
                    cout << "ID del cliente: "; clienteId = leerEntero();
                    vector<Venta> ventas = ventaUC.ventasPorCliente(clienteId);
                    if (ventas.empty()) cout << "\nEse cliente no tiene ventas.\n";
                    else for (auto& v : ventas) v.mostrarResumen();
                    break;
                }
                case 6: {
                    string desde, hasta;
                    cout << "Fecha desde (YYYY-MM-DD): "; desde = leerString();
                    cout << "Fecha hasta (YYYY-MM-DD): "; hasta = leerString();
                    vector<Venta> ventas = ventaUC.ventasPorRangoFechas(desde, hasta);
                    if (ventas.empty()) cout << "\nNo hay ventas en ese rango.\n";
                    else for (auto& v : ventas) v.mostrarResumen();
                    break;
                }
                case 7:
                    break;
                default:
                    cout << "\nOpcion invalida.\n";
            }
        } catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
        }
        if (opcion != 7) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 7);
}