#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "menuCliente.hpp"
#include "menuEmpleado.hpp"
#include "menuProducto.hpp"
#include "menuVenta.hpp"
#include "menuReportes.hpp"
#include "../../CasosDeUso/ClienteCasoDeUso.hpp"
#include "../../CasosDeUso/EmpleadoCasoDeUso.hpp"
#include "../../CasosDeUso/ProductoCasoDeUso.hpp"
#include "../../CasosDeUso/VentaCasoDeUso.hpp"
#include "../../Modulos/consoleClear.hpp"
#include "../../Modulos/dataLecture.hpp"
using namespace std;

void mostrarMenuPrincipal(ClienteCasoDeUso& clienteUC,
                          EmpleadoCasoDeUso& empleadoUC,
                          ProductoCasoDeUso& productoUC,
                          VentaCasoDeUso& ventaUC) {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========================================\n";
        cout << "       SISTEMA ERP - SOLUCIONES S.A.    \n";
        cout << "========================================\n";
        cout << " 1. Gestion de Productos\n";
        cout << " 2. Gestion de Clientes\n";
        cout << " 3. Gestion de Empleados\n";
        cout << " 4. Gestion de Ventas\n";
        cout << " 5. Reportes y Estadisticas\n";
        cout << " 6. Salir\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        opcion = leerEntero();
        switch (opcion) {
            case 1:
                menuProducto(productoUC);
                break;
            case 2:
                menuCliente(clienteUC);
                break;
            case 3:
                menuEmpleado(empleadoUC);
                break;
            case 4:
                menuVenta(ventaUC, clienteUC, productoUC);
                break;
            case 5:
                menuReportes(ventaUC, clienteUC, productoUC, empleadoUC);
                break;
            case 6:
                cout << "\nSaliendo del sistema...\n";
                break;
            default:
                cout << "\nOpcion invalida. Presione Enter para continuar...\n";
                cin.ignore();
                cin.get();
        }
    } while (opcion != 6);
}