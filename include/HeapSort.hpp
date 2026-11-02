#ifndef HEAPSORT_HPP
#define HEAPSORT_HPP

#include <string>
#include <vector>

// Ordena alfabeticamente las palabras usando HeapSort y un monticulo binario.
void heapSort(std::vector<std::string>& palabras);

// Lee el dataset, ejecuta HeapSort, mide el tiempo y guarda el resultado.
bool ejecutarHeapSort(const std::string& rutaEntrada,
                      const std::string& rutaSalida,
                      std::size_t mostrar);

#endif
