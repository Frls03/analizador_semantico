#include <iostream>
#include <stack>
#include <cstring>
#include <cstdlib>

using namespace std;


class Nodo {
public:
    char valor;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo(char v) {
        valor = v;
        izquierdo = derecho = NULL;
    }
};


Nodo* construirArbol(string expresion) {
    stack<Nodo*> pila;
    Nodo* nodo;
    for (int i = 0; i < expresion.length(); i++) {
        if (expresion[i] >= '0' && expresion[i] <= '9') {
            nodo = new Nodo(expresion[i]);
            pila.push(nodo);
        }
        else {
            nodo = new Nodo(expresion[i]);
            nodo->derecho = pila.top();
            pila.pop();
            nodo->izquierdo = pila.top();
            pila.pop();
            pila.push(nodo);
        }
    }
    nodo = pila.top();
    pila.pop();
    return nodo;
}


string analizarArbol(Nodo* nodo) {
    if (nodo->valor >= '0' && nodo->valor <= '9') {
        return string(1, nodo->valor);
    }
    string izq = analizarArbol(nodo->izquierdo);
    string der = analizarArbol(nodo->derecho);
    string resultado = izq + der + string(1, nodo->valor);
    return resultado;
}


void imprimirResultados(Nodo* nodo) {
    if (nodo == NULL) {
        return;
    }
   
    if (nodo->valor >= '0' && nodo->valor <= '9') {
        cout << "term.t = " << "'" << nodo->valor << "'";
    }
    else {
        cout << "expr.t" << ' ' << " = expr.t" << " " << " || ";
        cout << "term.t" << " " << " || '" << nodo->valor << "' || ";
    }
    cout << endl;
     imprimirResultados(nodo->izquierdo);
    imprimirResultados(nodo->derecho);
}

int main() {
    string expresion;
    cout << "Ingrese una expresion en notacion postfija: ";
    cin >> expresion;
    Nodo* raiz = construirArbol(expresion);
    string resultado = analizarArbol(raiz);
    cout << "Las reglas semanticas de la siguiente notacion  " << resultado << " son: " << endl;
    imprimirResultados(raiz);
    delete raiz;
    return 0;
}
