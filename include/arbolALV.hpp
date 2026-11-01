#ifndef ARBOL_ALV_HPP
#define ARBOL_ALV_HPP

#include <string> //manejo de texto
#include <vector> // arreglo dinamico
#include <cstddef> //tamaños o indices

// Nodo del arbol AVL: guarda una palabra, su altura y los punteros a sus hijos.
struct NodoAVL
{
    std::string palabra;
    int altura;
    NodoAVL *izq;
    NodoAVL *der;
    explicit NodoAVL(const std::string &p);
};

// Arbol AVL (arbol binario de busqueda auto-balanceado).
class ArbolAVL{
public:
    ArbolAVL();
    ~ArbolAVL();

    // Inserta una palabra en el arbol y lo rebalancea si es necesario.
    void insertar(const std::string &palabra);

    // Recorrido inorden: agrega las palabras ya ordenadas al vector recibido.
    void inorden(std::vector<std::string> &resultado) const;

    // Altura total del arbol (0 si esta vacio).
    int altura() const;

    // Cantidad de palabras almacenadas.
    std::size_t tamaño() const;

private:
    NodoAVL *raiz;
    std::size_t cantidad;

    static int alturaNodo(const NodoAVL *n);
    static void actualizarAltura(NodoAVL *n);
    static int factorBalance(const NodoAVL *n);
    static NodoAVL *rotarDerecha(NodoAVL *y);
    static NodoAVL *rotarIzquierda(NodoAVL *x);
    static NodoAVL *balancear(NodoAVL *n);
    static NodoAVL *insertarRec(NodoAVL *n, const std::string &palabra);
    static void inordenRec(const NodoAVL *n, std::vector<std::string> &resultado);
    static void liberar(NodoAVL *n);

    // Evita copias accidentales (el arbol maneja memoria dinamica).
    ArbolAVL(const ArbolAVL &) = delete;
    ArbolAVL &operator=(const ArbolAVL &) = delete;
};

// Lee un archivo .txt (una palabra por linea) y llena el vector.
bool cargarPalabras(const std::string &archivo, std::vector<std::string> &palabras);

// Escribe el vector en un archivo .txt (una palabra por linea).
bool guardarPalabras(const std::string &archivo, const std::vector<std::string> &palabras);

// Inserta todas las palabras en un AVL y devuelve el resultado del inorden.
std::vector<std::string> ordenarConAVL(const std::vector<std::string> &entrada);

// Devuelve un vector con las primeras 'cantidad' palabras del vector recibido.
std::vector<std::string> obtenerPrimerasPalabras(const std::vector<std::string> &palabras, std::size_t cantidad = 100);

// Lee, ordena y guarda las palabras usando un arbol AVL.
bool ejecutarOrdenamientoAVL(const std::string &archivoEntrada = "dataset.txt",
                             const std::string &archivoSalida = "ordenado_avl.txt",
                             std::size_t mostrar=0);
#endif