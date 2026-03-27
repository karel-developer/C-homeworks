#include <bits/stdc++.h>
using namespace std;

class Cadena {
private:
    char* ptr;
    size_t len;

public:
    Cadena(const char* s = "") {
        len = strlen(s);
        ptr = new char[len + 1];
        strcpy(ptr, s);
    }

    Cadena(const Cadena& otra) {
        len = otra.len;
        ptr = new char[len + 1];
        strcpy(ptr, otra.ptr);
    }

    ~Cadena() {
        delete[] ptr;
    }

    Cadena& operator=(const Cadena& otra) {
        if (this != &otra) {
            delete[] ptr;
            len = otra.len;
            ptr = new char[len + 1];
            strcpy(ptr, otra.ptr);
        }
        return *this;
    }

    Cadena operator+(const Cadena& otra) const {
        Cadena res;
        res.len = len + otra.len;
        delete[] res.ptr;
        res.ptr = new char[res.len + 1];
        strcpy(res.ptr, ptr);
        strcat(res.ptr, otra.ptr);
        return res;
    }

    bool operator==(const Cadena& otra) const {
        return strcmp(ptr, otra.ptr) == 0;
    }

    char& operator[](size_t index) {
        if (index >= len) throw out_of_range("Índice fuera de rango");
        return ptr[index];
    }

    const char& operator[](size_t index) const {
        if (index >= len) throw out_of_range("Índice fuera de rango");
        return ptr[index];
    }

    size_t longitud() const {
        return len;
    }

    void mayusculas() {
        for (size_t i = 0; i < len; ++i)
            ptr[i] = toupper(ptr[i]);
    }

    Cadena subcadena(size_t pos, size_t n) const {
        if (pos > len) throw out_of_range("Posición inicial inválida");
        size_t count = (n > len - pos) ? len - pos : n;
        char* temp = new char[count + 1];
        strncpy(temp, ptr + pos, count);
        temp[count] = '\0';
        Cadena res(temp);
        delete[] temp;
        return res;
    }

    friend ostream& operator<<(ostream& os, const Cadena& c) {
        os << c.ptr;
        return os;
    }
};

int main() {
    
    Cadena s1("Hola");
    Cadena s2(" Mundo");
    Cadena s3 = s1 + s2;
    cout << "Concatenación: " << s3 << endl;
    s3.mayusculas();
    cout << "Mayúsculas: " << s3 << endl;
    Cadena sub = s3.subcadena(0, 4);
    cout << "Subcadena (0,4): " << sub << endl;
    cout << "Longitud: " << s3.longitud() << endl;
    cout << "s3[5]: " << s3[5] << endl;
    Cadena s4("HOLA MUNDO");
    cout << "¿s3 == s4? " << boolalpha << (s3 == s4) << endl;

    return 0;
}