## 📁 Presentacion/README.md

# Presentation Layer (`Presentacion/`)

This layer contains the console-based user interface. It interacts with the use cases to present menus, capture user input, and display results.

## Structure
Presentacion/
├── Menus/
│ ├── menuPrincipal.hpp
│ ├── menuProducto.hpp
│ ├── menuCliente.hpp
│ ├── menuEmpleado.hpp
│ ├── menuVenta.hpp
│ └── menuReportes.hpp

## Features

- **Interactive menus:** Clear navigation with submenus for each entity.
- **Input validation:** Robust functions to handle wrong input types (letters instead of numbers, empty strings, etc.).
- **Aligned tables:** Uses `std::setw` and `std::left` to display lists in readable columns.
- **User feedback:** Shows success/error messages, and displays generated IDs after creation.
- **Screen clearing:** Cross-platform `limpiarPantalla()` function.

## Input Helpers (from `Modulos/consoleClear.hpp`)

- `leerEntero()`, `leerDouble()`, `leerString()`, `leerCharacter()`.
- Prevents crashes from invalid input.

## Dependencies
- Depends on use case classes (injected).
- Does NOT directly access repositories or domain logic.
