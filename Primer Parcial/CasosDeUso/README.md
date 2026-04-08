## 📁 CasosDeUso/README.md

# Use Cases Layer (`CasosDeUso/`)

This layer contains the application-specific business rules. It orchestrates the flow of data between the presentation layer and the repositories.

## Structure
CasosDeUso/
├── Interfaces/ Repository interfaces (abstractions)
│ ├── IClienteRepositorio.hpp
│ ├── IEmpleadoRepositorio.hpp
│ ├── IProductoRepositorio.hpp
│ └── IVentaRepositorio.hpp
├── ClienteCasoDeUso.hpp
├── EmpleadoCasoDeUso.hpp
├── ProductoCasoDeUso.hpp
└── VentaCasoDeUso.hpp

## Responsibilities

- **Interfaces:** Define what the repositories must do (dependency inversion).
- **Use Case classes:** Implement the actual operations (CRUD, statistics, filters, sales logic).
- **ID generation:** Automatically assigns new IDs by scanning existing data.
- **Business rules enforcement:**
  - Cannot delete a client with purchase history.
  - Cannot sell a product with insufficient stock.
  - Volume discounts (3+ items = 5%, 5+ = 10%, 10+ = 20%).
- **Memory management:** Properly deletes pointers returned by repositories.

## Dependencies

- Uses repository interfaces (injected via constructor).
- Depends on domain entities (includes them).
- No direct file I/O or JSON handling – that belongs to infrastructure.
