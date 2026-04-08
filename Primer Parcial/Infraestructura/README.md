## 📁 Infraestructura/README.md

# Infrastructure Layer (`Infraestructura/`)

This layer provides concrete implementations of the repository interfaces defined in the use cases. It handles JSON file storage and retrieval.

## Files

| File | Description |
|------|-------------|
| `ClienteRepositorio.hpp` | JSON file storage for clients. |
| `EmpleadoRepositorio.hpp` | JSON file storage for employees. |
| `ProductoRepositorio.hpp` | JSON file storage for products. |
| `VentaRepositorio.hpp` | JSON file storage for sales. |

## Features

- **File operations:** `readJson()` and `writeJson()` methods.
- **Automatic ID tracking:** Maintains `nextID` to generate new IDs correctly.
- **CRUD implementations:** `agregar`, `modificar`, `eliminar`, `obtenerTodos`, `obtenerPorId`.
- **Custom queries:** Filter by amount, number of purchases, date range, etc.
- **Memory:** `obtenerPorId` returns a pointer to a heap-allocated object (caller must `delete`).

## Dependencies
- Uses domain entities and nlohmann/json.
- Implements interfaces from CasosDeUso/Interfaces/.

Note
Repositories do NOT contain business logic (e.g., discount calculation). That belongs to use cases.
