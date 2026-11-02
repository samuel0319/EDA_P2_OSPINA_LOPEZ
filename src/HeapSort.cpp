#include "HeapSort.hpp"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <utility>

namespace {
void siftDown(std::vector<std::string>& palabras, std::size_t heapSize, std::size_t raiz) {
    while (true) {
        std::size_t mayor = raiz;
        std::size_t izquierda = 2 * raiz + 1;
        std::size_t derecha = 2 * raiz + 2;

        if (izquierda < heapSize && palabras[izquierda] > palabras[mayor])
            mayor = izquierda;
        if (derecha < heapSize && palabras[derecha] > palabras[mayor])
            mayor = derecha;
        if (mayor == raiz)
            return;

        std::swap(palabras[raiz], palabras[mayor]);
        raiz = mayor;
    }
}
}

void heapSort(std::vector<std::string>& palabras) {
    if (palabras.size() < 2)
        return;

    // Construccion del max-heap en O(n).
    for (std::size_t i = palabras.size() / 2; i > 0; --i)
        siftDown(palabras, palabras.size(), i - 1);

    // Mueve el mayor elemento al final y restaura el heap.
    for (std::size_t fin = palabras.size(); fin > 1; --fin) {
        std::swap(palabras[0], palabras[fin - 1]);
        siftDown(palabras, fin - 1, 0);
    }
}

bool ejecutarHeapSort(const std::string& rutaEntrada,
                      const std::string& rutaSalida,
                      std::size_t mostrar) {
    std::ifstream entrada(rutaEntrada);
    if (!entrada.is_open()) {
        std::cerr << "Error: no se pudo abrir " << rutaEntrada << '\n';
        return false;
    }

    std::vector<std::string> palabras;
    std::string linea;
    while (std::getline(entrada, linea)) {
        if (!linea.empty() && linea.back() == '\r')
            linea.pop_back();
        if (!linea.empty())
            palabras.push_back(linea);
    }
    entrada.close();

    std::cout << "Palabras leidas para HeapSort: " << palabras.size() << '\n';
    const auto inicio = std::chrono::steady_clock::now();
    heapSort(palabras);
    const auto fin = std::chrono::steady_clock::now();
    const double ms = std::chrono::duration<double, std::milli>(fin - inicio).count();

    const bool ordenado = std::is_sorted(palabras.begin(), palabras.end());
    std::cout << "HeapSort termino en " << ms << " ms\n";
    std::cout << "Verificacion: " << (ordenado ? "ordenado correctamente" : "ERROR, no esta ordenado") << '\n';

    const std::size_t cantidad = std::min(mostrar, palabras.size());
    std::cout << "\nPrimeras " << cantidad << " palabras ordenadas con HeapSort:\n";
    for (std::size_t i = 0; i < cantidad; ++i)
        std::cout << i + 1 << ". " << palabras[i] << '\n';

    std::ofstream salida(rutaSalida);
    if (!salida.is_open()) {
        std::cerr << "Error: no se pudo crear " << rutaSalida << '\n';
        return false;
    }
    for (const auto& palabra : palabras)
        salida << palabra << '\n';

    std::cout << "Resultado HeapSort guardado en " << rutaSalida << '\n';
    return ordenado && static_cast<bool>(salida);
}
