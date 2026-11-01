#include "arbolALV.hpp"

#include <algorithm> 
#include <chrono> // Para medir el tiempo de ejecución
#include <fstream> // Para leer y escribir archivos
#include <iostream> // Para mostrar mensajes en consola
// Constructor del nodo: empieza como hoja (altura 1, sin hijos).
NodoAVL::NodoAVL(const std::string &p) : palabra(p), altura(1), izq(nullptr), der(nullptr) {}
ArbolAVL::ArbolAVL() : raiz(nullptr), cantidad(0) {}
ArbolAVL::~ArbolAVL() { liberar(raiz); }

// Libera toda la memoria del arbol
void ArbolAVL::liberar(NodoAVL *n){
    if (!n)
        return;
    liberar(n->izq);
    liberar(n->der);
    delete n;
}

// Devuelve la altura de un nodo
int ArbolAVL::alturaNodo(const NodoAVL *n) { return n ? n->altura : 0; }

// Recalcula la altura de un nodo a partir de la de sus hijos
void ArbolAVL::actualizarAltura(NodoAVL *n){
    n->altura = 1 + std::max(alturaNodo(n->izq), alturaNodo(n->der));
}

// Factor de balance = altura(izq) - altura(der). Un AVL exige que este en (-1, 1)
int ArbolAVL::factorBalance(const NodoAVL *n){
    return n ? alturaNodo(n->izq) - alturaNodo(n->der) : 0;
}

// Rotacion simple a la derecha (caso izquierda-izquierda).
NodoAVL *ArbolAVL::rotarDerecha(NodoAVL *y){
    NodoAVL *x = y->izq;
    y->izq = x->der;
    x->der = y;
    actualizarAltura(y);
    actualizarAltura(x);
    return x; // nueva raiz del subarbol
}

// Rotacion simple a la izquierda (caso derecha-derecha).
NodoAVL *ArbolAVL::rotarIzquierda(NodoAVL *x){
    NodoAVL *y = x->der;
    x->der = y->izq;
    y->izq = x;
    actualizarAltura(x);
    actualizarAltura(y);
    return y; // nueva raiz del subarbol
}

// Revisa el balance del nodo y aplica la rotacion que corresponda (simple o doble), Se decide con el balance del hijo, no con la clave, tambien funciona si hay palabras repetidas.
NodoAVL *ArbolAVL::balancear(NodoAVL *n){
    actualizarAltura(n);
    int fb = factorBalance(n);
    // desbalanceado a la izquierda
    if (fb > 1){
        if (factorBalance(n->izq) < 0) // caso izquierda-derecha
            n->izq = rotarIzquierda(n->izq);
                return rotarDerecha(n); // caso izquierda-izquierda
        }
    // desbalanceado a la derecha
    if (fb < -1){
        if (factorBalance(n->der) > 0) // caso derecha-izquierda
            n->der = rotarDerecha(n->der);
                return rotarIzquierda(n); // caso derecha-derecha
    }
    return n; // ya estaba balanceado
}
// Insercion recursiva: baja como en un BST y al volver rebalancea cada nodo. Las palabras repetidas se envian a la derecha para no perder ninguna.
NodoAVL *ArbolAVL::insertarRec(NodoAVL *n, const std::string &palabra){
    if (!n)
        return new NodoAVL(palabra);
    if (palabra < n->palabra)
        n->izq = insertarRec(n->izq, palabra);
    else
        n->der = insertarRec(n->der, palabra);
    return balancear(n);
}

void ArbolAVL::insertar(const std::string &palabra){
    raiz = insertarRec(raiz, palabra);
    ++cantidad;
}

// Recorrido inorden: izquierda -> nodo -> derecha. En un BST produce orden ascendente.
void ArbolAVL::inordenRec(const NodoAVL *n, std::vector<std::string> &resultado){
    if (!n)
        return;
    inordenRec(n->izq, resultado);
    resultado.push_back(n->palabra);
    inordenRec(n->der, resultado);
}

void ArbolAVL::inorden(std::vector<std::string> &resultado) const{
    resultado.reserve(resultado.size() + cantidad);
    inordenRec(raiz, resultado);
}

int ArbolAVL::altura() const { return alturaNodo(raiz); }

std::size_t ArbolAVL::tamaño() const { return cantidad; }

// Quitamos el '\r' inerente de windows (afecta al rendimiento con lineas invisibles)
bool cargarPalabras(const std::string &archivo, std::vector<std::string> &palabras){
    std::ifstream in(archivo);
    if (!in.is_open()){
        std::cerr << "No se pudo abrir: " << archivo << "\n";
            return false;
    }
    std::string linea;
    while (std::getline(in, linea)){
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
            if (!linea.empty())
                palabras.push_back(linea);
    }
    return true;
}

// Escribe una palabra por linea en el archivo de salida.
bool guardarPalabras(const std::string &archivo, const std::vector<std::string> &palabras){
    std::ofstream out(archivo);
    if (!out.is_open()){
        std::cerr << "No se pudo crear: " << archivo << "\n";
            return false;
    }
    for (const std::string &p : palabras)
        out << p << '\n';
            return true;
}

// Pasos del metodo: 
//1) insertar todas las palabras 
//2) inorden 
//3) devolver la lista.
std::vector<std::string> ordenarConAVL(const std::vector<std::string> &entrada){
    ArbolAVL arbol;
    for (const std::string &p : entrada)
        arbol.insertar(p);

    std::vector<std::string> ordenado;
    arbol.inorden(ordenado);
    return ordenado;
}

// Funcion principal del modulo: carga, ordena, mide tiempos y guarda el archivo.
bool ejecutarOrdenamientoAVL(const std::string &archivoEntrada,
                             const std::string &archivoSalida,
                             std::size_t mostrar){
    using reloj = std::chrono::steady_clock;

    std::vector<std::string> palabras;
    if (!cargarPalabras(archivoEntrada, palabras))
        return false;
    std::cout << "Palabras cargadas: " << palabras.size() << "\n";
    auto inicio = reloj::now();
    ArbolAVL arbol;
    for (const std::string &p : palabras)
        arbol.insertar(p); // 1) insercion
    auto tInsercion = reloj::now();

    std::vector<std::string> ordenado;
    arbol.inorden(ordenado); // 2) inorden -> 3) lista
    auto fin = reloj::now();

    using ms = std::chrono::duration<double, std::milli>;
    std::cout << "Altura del AVL: " << arbol.altura() << "\n";
    std::cout << "Tiempo de insercion: " << ms(tInsercion - inicio).count() << " ms\n";
    std::cout << "Tiempo de inorden:   " << ms(fin - tInsercion).count() << " ms\n";
    std::cout << "Tiempo total:        " << ms(fin - inicio).count() << " ms\n";

    // Verificacion rapida de que el resultado quedo ordenado.
    std::cout << "Ordenado correctamente: "
              << (std::is_sorted(ordenado.begin(), ordenado.end()) ? "si" : "no") << "\n";
    
    // Mostrar en consola solo las primeras "mostrar"(100) palabras ordenadas std::min evita salirnos del vector si hubiera menos palabras
    std::size_t cantidad = std::min(mostrar, ordenado.size());
    std::cout << "\nPrimeras " << cantidad << " palabras ordenadas:\n";
    for (std::size_t i = 0; i < cantidad; i++)
    {
        std::cout << i + 1 << ". " << ordenado[i] << '\n';
    }

    return guardarPalabras(archivoSalida, ordenado);
}
