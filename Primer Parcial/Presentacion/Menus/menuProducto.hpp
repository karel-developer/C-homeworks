#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>
#include "../../CasosDeUso/ProductoCasoDeUso.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void menuProducto(ProductoCasoDeUso& productoUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========== GESTION DE PRODUCTOS ==========\n";
        cout << " 1. Agregar producto\n";
        cout << " 2. Modificar producto\n";
        cout << " 3. Eliminar producto\n";
        cout << " 4. Listar todos los productos\n";
        cout << " 5. Buscar por nombre parcial\n";
        cout << " 6. Buscar por categoria\n";
        cout << " 7. Buscar por rango de precios\n";
        cout << " 8. Productos con stock critico\n";
        cout << " 9. Producto mas caro\n";
        cout << "10. Producto mas barato\n";
        cout << "11. Costo total del inventario\n";
        cout << "12. Precio promedio por categoria\n";
        cout << "13. Volver al menu principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();

        try {
            switch (opcion) {
                case 1: {
                    string nombre, categoria;
                    double precio;
                    int stock;
                    cout << "Nombre: "; nombre = leerString();
                    cout << "Categoria: "; categoria = leerString();
                    cout << "Precio: "; precio = leerDouble();
                    cout << "Stock: "; stock = leerEntero();
                    int nuevoId = productoUC.agregarProducto(nombre, categoria, precio, stock);
                    cout << "\nProducto agregado exitosamente con ID: " << nuevoId << '\n';
                    break;
                }
                case 2: {
                    int id, stock;
                    string nombre, categoria;
                    double precio;
                    cout << "ID del producto: "; id = leerEntero();
                    cout << "Nuevo nombre: "; nombre = leerString();
                    cout << "Nueva categoria: "; categoria = leerString();
                    cout << "Nuevo precio: "; precio = leerDouble();
                    cout << "Nuevo stock: "; stock = leerEntero();
                    productoUC.modificarProducto(id, nombre, categoria, precio, stock);
                    cout << "\nProducto modificado exitosamente.\n";
                    break;
                }
                case 3: {
                    int id;
                    cout << "ID del producto a eliminar: "; id = leerEntero();
                    productoUC.eliminarProducto(id);
                    cout << "\nProducto eliminado exitosamente.\n";
                    break;
                }
                case 4: {
                    vector<Producto> productos = productoUC.listarTodos();
                    if (productos.empty()) cout << "\nNo hay productos registrados.\n";
                    else for (auto& p : productos) p.mostrarProducto();
                    break;
                }
                case 5: {
                    string nombre;
                    cout << "Nombre parcial: "; nombre = leerString();
                    vector<Producto> resultados = productoUC.buscarPorNombre(nombre);
                    if (resultados.empty()) cout << "\nNo se encontraron productos.\n";
                    else for (auto& p : resultados) p.mostrarProducto();
                    break;
                }
                case 6: {
                    string cat;
                    cout << "Categoria: "; cat = leerString();
                    vector<Producto> resultados = productoUC.buscarPorCategoria(cat);
                    if (resultados.empty()) cout << "\nNo hay productos en esa categoria.\n";
                    else for (auto& p : resultados) p.mostrarProducto();
                    break;
                }
                case 7: {
                    double min, max;
                    cout << "Precio minimo: "; min = leerDouble();
                    cout << "Precio maximo: "; max = leerDouble();
                    vector<Producto> resultados = productoUC.buscarPorRangoPrecios(min, max);
                    if (resultados.empty()) cout << "\nNo hay productos en ese rango.\n";
                    else for (auto& p : resultados) p.mostrarProducto();
                    break;
                }
                case 8: {
                    int umbral;
                    cout << "Umbral de stock critico: "; umbral = leerEntero();
                    vector<Producto> criticos = productoUC.stockCritico(umbral);
                    if (criticos.empty()) cout << "\nNo hay productos con stock critico.\n";
                    else for (auto& p : criticos) p.mostrarProducto();
                    break;
                }
                case 9: {
                    Producto p = productoUC.productoMasCaro();
                    p.mostrarProducto();
                    break;
                }
                case 10: {
                    Producto p = productoUC.productoMasBarato();
                    p.mostrarProducto();
                    break;
                }
                case 11: {
                    double total = productoUC.costoTotalInventario();
                    cout << "\nCosto total del inventario: $" << fixed << setprecision(2) << total << "\n";
                    break;
                }
                case 12: {
                    map<string, double> promedios = productoUC.precioPromedioPorCategoria();
                    cout << "\nPrecio promedio por categoria:\n";
                    for (auto& par : promedios) {
                        cout << par.first << ": $" << fixed << setprecision(2) << par.second << "\n";
                    }
                    break;
                }
                case 13:
                    break;
                default:
                    cout << "\nOpcion invalida.\n";
            }
        } catch (const exception& e) {
            cout << "\nError: " << e.what() << "\n";
        }
        if (opcion != 13) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    } while (opcion != 13);
}