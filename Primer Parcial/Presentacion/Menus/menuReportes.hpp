#pragma once
#include <iostream>
#include <iomanip>
#include "../../CasosDeUso/VentaCasoDeUso.hpp"
#include "../../CasosDeUso/ClienteCasoDeUso.hpp"
#include "../../CasosDeUso/ProductoCasoDeUso.hpp"
#include "../../CasosDeUso/EmpleadoCasoDeUso.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void menuReportes(VentaCasoDeUso& ventaUC,
                  ClienteCasoDeUso& clienteUC,
                  ProductoCasoDeUso& productoUC,
                  EmpleadoCasoDeUso& empleadoUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========== REPORTES Y ESTADISTICAS ==========\n";
        cout << " 1. Total vendido por categoria\n";
        cout << " 2. Producto mas vendido\n";
        cout << " 3. Cliente que mas gasta\n";
        cout << " 4. Promedio de ventas por cliente\n";
        cout << " 5. Costo total de inventario\n";
        cout << " 6. Promedio de precios por categoria\n";
        cout << " 7. Salario promedio de empleados\n";
        cout << " 8. Empleado con mayor salario\n";
        cout << " 9. Conteo de empleados por cargo\n";
        cout << "10. Volver al menu principal\n";
        cout << "==============================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();
        try {
            switch (opcion) {
                case 1: {
                    string categoria;
                    cout << "Categoria: "; categoria = leerString();
                    double total = ventaUC.totalVendidoPorCategoria(categoria);
                    cout << "\nTotal vendido en '" << categoria << "': $"
                              << fixed << setprecision(2) << total << "\n";
                    break;
                }
                case 2: {
                    auto par = ventaUC.productoMasVendido();
                    if (par.first == -1) {
                        cout << "\nNo hay ventas registradas.\n";
                    } else {
                        Producto* p = productoUC.buscarPorId(par.first);
                        if (p) {
                            cout << "\nProducto mas vendido: " << p->getNombre()
                                      << " (ID: " << p->getId() << ")\n";
                            cout << "Cantidad vendida: " << par.second << "\n";
                        }
                    }
                    break;
                }
                case 3: {
                    int idCliente = ventaUC.clienteQueMasGasta();
                    if (idCliente == -1) {
                        cout << "\nNo hay ventas registradas.\n";
                    } else {
                        Cliente* c = clienteUC.buscarPorId(idCliente);
                        if (c) {
                            cout << "\nCliente que mas gasta: " << c->getNombre() << " " << c->getApellido()
                                      << " (ID: " << c->getId() << ")\n";
                        }
                    }
                    break;
                }
                case 4: {
                    double promedio = ventaUC.promedioVentasPorCliente();
                    cout << "\nPromedio de ventas por cliente: "
                              << fixed << setprecision(2) << promedio << "\n";
                    break;
                }
                case 5: {
                    double costo = productoUC.costoTotalInventario();
                    cout << "\nCosto total del inventario: $"
                              << fixed << setprecision(2) << costo << "\n";
                    break;
                }
                case 6: {
                    auto promedios = productoUC.precioPromedioPorCategoria();
                    cout << "\nPrecio promedio por categoria:\n";
                    for (auto& par : promedios) {
                        cout << "  " << par.first << ": $"
                                  << fixed << setprecision(2) << par.second << "\n";
                    }
                    break;
                }
                case 7: {
                    double promedio = empleadoUC.salarioPromedio();
                    cout << "\nSalario promedio de empleados: $"
                              << fixed << setprecision(2) << promedio << "\n";
                    break;
                }
                case 8: {
                    Empleado mejor = empleadoUC.empleadoConMayorSalario();
                    cout << "\nEmpleado con mayor salario:\n";
                    mejor.mostrarInformacion();
                    break;
                }
                case 9: {
                    auto conteo = empleadoUC.conteoPorCargo();
                    cout << "\nConteo de empleados por cargo:\n";
                    for (auto& par : conteo) {
                        cout << "  " << par.first << ": " << par.second << "\n";
                    }
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