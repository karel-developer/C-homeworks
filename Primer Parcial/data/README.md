## 📁 data/README.md

# Data Folder (`data/`)

This folder stores all persistent data in JSON format. The repository classes automatically read from and write to these files.

## Files

| File | Content |
|------|---------|
| `clientes.json` | List of clients (including purchase history). |
| `empleados.json` | List of employees. |
| `productos.json` | List of products (stock, price, etc.). |
| `ventas.json` | List of sales. |

## Auto‑generation

If any file is missing when the program starts, it will be created as an empty JSON array (`[]`) upon first write operation.

## Example (productos.json)

```json
[
    {
        "id": 1,
        "nombre": "Mouse",
        "categoria": "Perifericos",
        "precio": 25.99,
        "stock": 12
    }
]
```
## Important
Do not manually edit these files while the program is running, as it may cause data loss.

Make backups if you want to preserve data.

The program uses these files as its only persistent storage – no external database is required.
