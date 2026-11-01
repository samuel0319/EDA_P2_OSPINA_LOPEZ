#include "ordenamiento.hpp"

#include <chrono>   // Para medir el tiempo de ejecución
#include <fstream>  // Para leer y escribir archivos
#include <iostream> // Para mostrar mensajes en consola
#include <utility>  // std::swap (solo intercambia valores, no ordena)

static int particionar(std::vector<std::string> &v, int bajo, int alto){
    //calculamos el punto medio
    int medio = bajo + (alto - bajo) / 2;
    // Ordenamos entre sí v[bajo], v[medio] y v[alto], v[medio] queda como la mediana de los tres
    if (v[medio] < v[bajo])
        std::swap(v[medio], v[bajo]);
    if (v[alto] < v[bajo])
        std::swap(v[alto], v[bajo]);
    if (v[alto] < v[medio])
        std::swap(v[alto], v[medio]);

    // Copiamos el pivote (la mediana) para compararlo mientras los elementos se mueven de posición
    std::string pivote = v[medio];

    int i = bajo - 1; // Cursor que avanza desde la izquierda
    int j = alto + 1; // Cursor que retrocede desde la derecha

    while (true){
        // Avanza i hasta encontrar un elemento mayor o igual al pivote
        do{
            i++;
        } 
        while (v[i] < pivote);
        // Retrocede j hasta encontrar un elemento menor o igual pivote
        do{
            j--;
        }
            while (pivote < v[j]);
            // Si los cursores se cruzaron, la partición terminó
            if (i >= j)
                return j;
            // Ambos elementos están del lado equivocado: los intercambiamos
            std::swap(v[i], v[j]);
    }
}
static void quickSortRec(std::vector<std::string> &v, int bajo, int alto){
    while (bajo < alto){
        int p = particionar(v, bajo, alto); // Índice de corte
        if (p - bajo < alto - p){
            quickSortRec(v, bajo, p); // Mitad izquierda (más pequeña)
            bajo = p + 1;             // Seguimos con la derecha
        }
        else{
            quickSortRec(v, p + 1, alto); // Mitad derecha (más pequeña)
            alto = p;                     // Seguimos con la izquierda
        }
    }
}
//ordena las palabras de manera alfabetica, si tiene 0 o 1 no hace nada (tiene menos de 2 letra)
void quickSort(std::vector<std::string> &palabras){
    if (palabras.size() < 2)
        return;
    quickSortRec(palabras, 0, static_cast<int>(palabras.size()) - 1);
}
//comprobar que quicksort funciona correctamente (devuelve true cuando estan en orden)
bool estaOrdenado(const std::vector<std::string> &palabras){
    for (std::size_t i = 1; i < palabras.size(); i++){
        if (palabras[i] < palabras[i - 1])
            return false;
    }
    return true;
}
bool ejecutarQuickSort(const std::string &rutaEntrada,
                       const std::string &rutaSalida, 
                       int mostrar){
    //Lectura del dataset
    std::ifstream entrada(rutaEntrada);
    if (!entrada.is_open()){
        std::cerr << "Error: no se pudo abrir " << rutaEntrada << '\n';
        return false;
    }
    std::vector<std::string> palabras;
    std::string linea;
    while (std::getline(entrada, linea)){
        // Quitamos el '\r' inerente de windows (afecta al rendimiento con lineas invisibles)
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (!linea.empty())
            palabras.push_back(linea);
    }
    entrada.close();
    std::cout << "Palabras leidas: " << palabras.size() << '\n';
    //midiendo el tiempo
    auto inicio = std::chrono::steady_clock::now();
    quickSort(palabras);
    auto fin = std::chrono::steady_clock::now();
    //la diferencia de tiempo = total de tiempo
    double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();
    std::cout << "QuickSort termino en " << ms << " ms\n";
    //Verificación del resultado (? como true y : es falso)
    std::cout << (estaOrdenado(palabras) ? "Verificacion: ordenado correctamente\n"
                                         : "Verificacion: ERROR, no esta ordenado\n");
    // Mostrar en consola solo las primeras "mostrar"(100) palabras ordenadas std::min evita salirnos del vector si hubiera menos palabras
    std::size_t cantidad = std::min<std::size_t>(mostrar, palabras.size());
    std::cout << "\nPrimeras " << cantidad << " palabras ordenadas:\n";
    for (std::size_t i = 0; i < cantidad; i++){
        std::cout << i + 1 << ". " << palabras[i] << '\n';
    }
    //Escritura del resultado completo en el archivo
    std::ofstream salida(rutaSalida);
    if (!salida.is_open()){
        std::cerr << "Error: no se pudo crear " << rutaSalida << '\n';
        return false;
    }
    for (const auto &p : palabras)
        salida << p << '\n';
    std::cout << "Resultado guardado en " << rutaSalida << '\n';
    return true;
}