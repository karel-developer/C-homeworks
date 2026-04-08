#include "Presentacion/Menus/menuPrincipal.hpp"
#include "Infraestructura/ClienteRepositorio.hpp"
#include "Infraestructura/EmpleadoRepositorio.hpp"
#include "Infraestructura/ProductoRepositorio.hpp"
#include "Infraestructura/VentaRepositorio.hpp"
#include "CasosDeUso/ClienteCasoDeUso.hpp"
#include "CasosDeUso/EmpleadoCasoDeUso.hpp"
#include "CasosDeUso/ProductoCasoDeUso.hpp"
#include "CasosDeUso/VentaCasoDeUso.hpp"
#include <iostream>
using namespace std;

int main() {
    try {
        string clientesFile = "data/clientes.json";
        string empleadosFile = "data/empleados.json";
        string productosFile = "data/productos.json";
        string ventasFile = "data/ventas.json";

        ClienteRepositorio clienteRepo(clientesFile);
        EmpleadoRepositorio empleadoRepo(empleadosFile);
        ProductoRepositorio productoRepo(productosFile);
        VentaRepositorio ventaRepo(ventasFile);

        ClienteCasoDeUso clienteUC(clienteRepo);
        EmpleadoCasoDeUso empleadoUC(empleadoRepo);
        ProductoCasoDeUso productoUC(productoRepo);
        VentaCasoDeUso ventaUC(ventaRepo, productoRepo, clienteRepo);

        mostrarMenuPrincipal(clienteUC, empleadoUC, productoUC, ventaUC);

    } catch (const exception& e) {
        cerr << "Error fatal: " << e.what() << endl;
        return 1;
    }

    return 0;
}