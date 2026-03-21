#include <bits/stdc++.h>
using namespace std;

template<class T>
string paridad(T dato) {
    return (dato & 1 ? "IMPAR" : "PAR");
}

vector<int> ordenar(int a, int b, int c) {
    int x = max(a, b);
    x = max(x, c);
    int z = min(a, b);
    z = min(z, c);
    int y = a + b + c;
    y = y - x - z;
    vector<int> result;
    result.push_back(z);
    result.push_back(y);
    result.push_back(x);

    return result;
}

int contador(vector<int> a, int b) {
    int conteo = 0;
    for(int i = 0; i < a.size(); i++) {
        if(a[i] == b) conteo++;
    }
    return conteo;
}

int sum(const vector<int>& vec) {
    int suma = 0;

    for(int i = 0; i < vec.size(); i++) {
        suma += vec[i];
    }

    return suma;
}

vector<int> invertir(const vector<int>& vec) {
    vector<int> result(vec.size());
    int j = 0;
    for(int i = vec.size() - 1; i >= 0; i--) {
        result[j] = vec[i];
        j++;
    }
    return result;
}

vector<int> func(const vector<int>& vec) {
    vector<bool> dis(1e6, false);
    vector<int> result;
    for(int i = 0; i < vec.size(); i++) {
        if(!dis[i]) {
            for(int j = i; j < vec.size(); j++) {
                if(vec[j] == vec[i]) {
                    dis[j] = true;
                }
            }
            result.push_back(vec[i]);
        }
    }
    return result;
}

vector<int> filtrar(const vector<int> vec, int num) {
    vector<int> filter;
    for(int x : vec) 
        if(x > num) filter.push_back(x);

    return filter;
    
}

vector<int> suma_prefijo(const vector<int>& vec) {
    int total = sum(vec);
    vector<int> result(vec.size());
    int reverse_sum = 0;
    result[vec.size() - 1] = total;
    for(int i = vec.size() - 2; i >= 0; i--) {
        reverse_sum += vec[i + 1];
        result[i] = total - reverse_sum;
    }
    return result;
}

int suma_maxima(const vector<int>& vec) {
    int current = vec[0];
    int max_sum = vec[0];
    for(int i = 1; i < vec.size(); ++i) {
        current = max(vec[i], current + vec[i]);
        max_sum = max(max_sum, current);
    }
    return max_sum;
}

vector<int> construction_of_vector(const vector<int>& vec) {
    vector<int> r(vec.size());
    int acumulado_izquierda = 1;
    for(int i = 0; i < vec.size(); ++i) {
        r[i] = acumulado_izquierda;
        acumulado_izquierda *= vec[i];
    }
    int acumulado_derecha = 1;
    for(int i = vec.size() - 1; i >= 0; --i) {
        r[i] *= acumulado_derecha;
        acumulado_derecha *= vec[i];
    }
    return r;
}

int main() {

    int num;
    cin >> num;
    cout << paridad(num) << endl;

    vector<int> l = ordenar(2,3,4);
    cout << l[0] << endl;
    cout << l[1] << endl;
    cout << l[2] << endl;

    const vector<int> aux = {1, 2, 3};

    cout << contador(aux, 1) << endl;

    cout << sum(aux) << endl;

    vector<int> aux2 = invertir(aux);

    cout << aux2[0] << endl;

    vector<int> x = {1, 2, 3, 1, 2, 1, 3, 2, 1, -2, 2, 1, 1, 2, 3};
    vector<int> aux3 = func(x);
    for(int a : aux3) cout << a << endl;

    cout << "Filtrado" << endl;
    vector<int> filter = filtrar(x, 1);
    for(int a : filter) cout << a << endl;

    cout << "Acumulado" << endl;
    vector<int> accumulate_sum = suma_prefijo(x);
    for(int a : accumulate_sum) cout << a << endl;

    cout << "Suma maxima" << endl;

    cout << suma_maxima(x) << endl;

    vector<int> r = construction_of_vector(x);
    for(int a : r) cout << a << endl;


    return 0;
}