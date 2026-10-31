#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <string>
#include <vector>

// Ordena alfabéticamente el vector de palabras usando QuickSort
void quickSort(std::vector<std::string> &palabras);

// Verifica que el vector esté ordenado de forma ascendente.
bool estaOrdenado(const std::vector<std::string> &palabras);

// lee dataset.txt, ordena con QuickSort, mide el tiempo y guarda el resultado.
bool ejecutarQuickSort(const std::string &rutaEntrada,
                       const std::string &rutaSalida,
                        int mostrar);
#endif