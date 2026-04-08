#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstdlib>

inline void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

#endif