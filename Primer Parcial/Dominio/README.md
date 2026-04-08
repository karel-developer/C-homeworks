## 📁 Dominio/README.md

# Domain Layer (`Dominio/`)

This folder contains the core business entities of the ERP system. These classes represent the real-world concepts and are independent of any external framework or storage mechanism.

## Classes

| File | Description |
|------|-------------|
| `Persona.hpp` | Abstract base class for persons (id, name, surname, phone). |
| `Empleado.hpp` | Employee – inherits `Persona`, adds position and salary. |
| `Cliente.hpp` | Client – inherits `Persona`, adds email and purchase history. |
| `Producto.hpp` | Product (id, name, category, price, stock). |
| `Venta.hpp` | Sale (id, buyer ID, date, list of products, total amount). |

## Design Principles

- No external dependencies (except standard library and `nlohmann/json` for serialization).
- Getters are `const`, setters include validation.
- Each class provides `to_json` / `from_json` functions for JSON persistence.
- Inheritance: `Persona` → `Empleado` / `Cliente`.

## Serialization

All classes implement manual serialization using `nlohmann/json` to allow saving/loading from JSON files without macros.

## Note

Entities do NOT know about repositories or use cases. They are plain data containers with business logic only related to themselves (e.g., stock update, total calculation).
