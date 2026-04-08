# ERP System for Soluciones S.A. (C++ Console Application)

A mini-ERP system for a small technology products and services company. Built in C++11 following Clean Architecture principles. The system manages products, clients, employees, sales, and generates reports with persistent storage via JSON files.

## Features

- **Product Management:** CRUD, stock control, category/price filters, critical stock alerts, most expensive/cheapest products.
- **Client Management:** CRUD (cannot delete if has purchases), purchase history, filters by amount spent or number of purchases, top buyers.
- **Employee Management:** CRUD, salary statistics (average, highest, count by position).
- **Sales Management:** Register sales (automatic stock update), delete by ID, filter by client or date range.
- **Reports & Statistics:** Total sold per category, best-selling product, biggest spender client, inventory total cost, average price per category, average sales per client.
- **Volume Discounts:** 5% for 3+ items, 10% for 5+, 20% for 10+.
- **Persistence:** All data stored in JSON files (under `data/` folder).
- **Console UI:** Interactive menus with aligned tables and robust input validation.

## Architecture (Clean)

- **Domain:** Core business entities (Product, Person, Employee, Client, Sale).
- **Use Cases:** Application-specific business rules (repositories interfaces + implementations).
- **Infrastructure:** Concrete repositories (JSON file storage).
- **Presentation:** Console menus handling user interaction.

## Project Structure
primer_parcial/
├── Dominio/Entities
├── CasosDeUso/ Use Cases + Interfaces
├── Infraestructura/ Repositories (JSON)
├── Presentacion/ Menus (UI)
├── Modulos/ Utilities (json.hpp, consoleClear.hpp)
├── data/ JSON data files
└── main.cpp

## How to Build & Run

- Compile with any C++11 compatible compiler (g++, clang++, MSVC).
- Include `nlohmann/json.hpp` (provided in `Modulos/`).
- Ensure `data/` folder exists (or it will be created automatically when saving data).

## License
Academic project – use freely for learning purposes.
