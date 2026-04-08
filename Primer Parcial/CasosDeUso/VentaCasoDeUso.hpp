#pragma once
#include "../Infraestructura/VentaRepositorio.hpp"
#include "../Infraestructura/ProductoRepositorio.hpp"
#include "../Infraestructura/ClienteRepositorio.hpp"
#include "../Dominio/Venta.hpp"
#include "../Dominio/Producto.hpp"
#include "../Dominio/Cliente.hpp"
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <algorithm>
using namespace std;

class VentaCasoDeUso {
private:
    VentaRepositorio& ventaRepo;
    ProductoRepositorio& productoRepo;
    ClienteRepositorio& clienteRepo;

    int generarNuevoId() {
        vector<Venta> todas = ventaRepo.obtenerTodos();
        if (todas.empty()) return 1;
        int maxId = 0;
        for (const auto& v : todas) {
            if (v.getId() > maxId) maxId = v.getId();
        }
        return maxId + 1;
    }

public:
    VentaCasoDeUso(VentaRepositorio& vRepo, ProductoRepositorio& pRepo, ClienteRepositorio& cRepo)
        : ventaRepo(vRepo), productoRepo(pRepo), clienteRepo(cRepo) {}
        
   void registrarVenta(int clienteId, const vector<int>& idsProductos, const string& fecha) {
        Cliente* cliente = clienteRepo.obtenerPorId(clienteId);
        if (!cliente) throw runtime_error("Cliente no encontrado.");

        vector<Producto*> productosPtr;
        for (int prodId : idsProductos) {
            Producto* prod = productoRepo.obtenerPorId(prodId);
            if (!prod) {
                for (Producto* p : productosPtr) delete p;
                delete cliente;
                throw runtime_error("Producto no existe.");
            }
            if (prod->getStock() < 1) {
                for (Producto* p : productosPtr) delete p;
                delete cliente;
                throw runtime_error("Stock insuficiente.");
            }
            productosPtr.push_back(prod);
        }

        vector<Producto> productosVendidos;
        for (Producto* prod : productosPtr) {
            prod->actualizarStock(-1);
            productoRepo.modificar(*prod);
            productosVendidos.push_back(*prod);
            delete prod;
        }

        int cantidad = productosVendidos.size();
        double descuento = 0.0;
        if (cantidad >= 10) descuento = 0.20;
        else if (cantidad >= 5) descuento = 0.10;
        else if (cantidad >= 3) descuento = 0.05;
        
        double subtotal = 0.0;
        for (const auto& p : productosVendidos) {
            subtotal += p.getPrecio();
        }
        double totalConDescuento = subtotal * (1.0 - descuento);
        if (descuento > 0) {
            cout << "\n Descuento por volumen del " << (descuento * 100) << "% aplicado.\n";
            cout << "   Subtotal: $" << subtotal << "\n";
            cout << "   Total con descuento: $" << totalConDescuento << "\n";
        }
        int nuevoId = generarNuevoId();
        if (descuento > 0) {
            double factor = (1.0 - descuento);
            for (auto& p : productosVendidos) {
                p.setPrecio(p.getPrecio() * factor);
            }
        }
        
        Venta nuevaVenta(nuevoId, clienteId, productosVendidos, fecha);
        ventaRepo.registrar(nuevaVenta);

        cliente->agregarCompra(nuevaVenta);
        clienteRepo.modificar(*cliente);
        delete cliente;
    }

    void eliminarVenta(int ventaId) {
        Venta* venta = ventaRepo.obtenerPorId(ventaId);
        if (!venta) throw runtime_error("Venta no encontrada.");

        Cliente * cliente = clienteRepo.obtenerPorId(venta->getCompradorId());
        if(!cliente) {
            delete venta;
            throw runtime_error("Cliente asociado a la venta no encontrado");
        }

        vector<Venta> historialActualizado;
        for(const auto& v : cliente->getHistorial()) {
            if(v.getId() != ventaId) {
                historialActualizado.push_back(v);
            }
        }

        cliente->setHistorial(historialActualizado);
        clienteRepo.modificar(*cliente);

        for (const Producto& p : venta->getProductos()) {
            Producto* prod = productoRepo.obtenerPorId(p.getId());
            if (prod) {
                prod->actualizarStock(1);
                productoRepo.modificar(*prod);
                delete prod;
            }
        }

        ventaRepo.eliminar(ventaId);

        delete venta;
        delete cliente;
    }

    vector<Venta> listarTodas() { return ventaRepo.obtenerTodos(); }

    Venta* buscarPorId(int id) { return ventaRepo.obtenerPorId(id); }

    vector<Venta> ventasPorCliente(int clienteId) {
        return ventaRepo.buscarPorClienteId(clienteId);
    }

    vector<Venta> ventasPorRangoFechas(const string& desde, const string& hasta) {
        return ventaRepo.buscarPorRangoFechas(desde, hasta);
    }

    double totalVendidoPorCategoria(const string& categoria) {
        double total = 0.0;
        vector<Venta> ventas = ventaRepo.obtenerTodos();
        for (const Venta& v : ventas) {
            for (const Producto& p : v.getProductos()) {
                if (p.getCategoria() == categoria) total += p.getPrecio();
            }
        }
        return total;
    }

    pair<int, int> productoMasVendido() {
        map<int, int> contador;
        for (const Venta& v : ventaRepo.obtenerTodos()) {
            for (const Producto& p : v.getProductos()) {
                contador[p.getId()]++;
            }
        }
        int mejorId = -1, maxCant = 0;
        for (auto& par : contador) {
            if (par.second > maxCant) {
                maxCant = par.second;
                mejorId = par.first;
            }
        }
        return {mejorId, maxCant};
    }

    int clienteQueMasGasta() {
        map<int, double> gastoPorCliente;
        for (const Venta& v : ventaRepo.obtenerTodos()) {
            gastoPorCliente[v.getCompradorId()] += v.getTotal();
        }
        int mejorCliente = -1;
        double maxGasto = 0.0;
        for (auto& par : gastoPorCliente) {
            if (par.second > maxGasto) {
                maxGasto = par.second;
                mejorCliente = par.first;
            }
        }
        return mejorCliente;
    }

    double promedioVentasPorCliente() {
        int totalClientes = clienteRepo.obtenerTodos().size();
        if (totalClientes == 0) return 0.0;
        int totalVentas = ventaRepo.obtenerTodos().size();
        return static_cast<double>(totalVentas) / totalClientes;
    }
};