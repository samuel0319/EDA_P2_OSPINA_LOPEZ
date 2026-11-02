// Estudiante: Simon Ospina Ruiz
// Materia: Estructura de Datos y Algoritmos
// Profesor: Carlos Alberto Álvarez Henao
// HeapSort con un montículo binario (max-heap)

#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <vector>
#include <string>
#include <utility>

// Max-heap en arreglo: hijos en 2i+1 y 2i+2, padre en (i-1)/2
class BinaryHeap {
public:
    // Construye el heap en O(n) (método de Floyd)
    explicit BinaryHeap(std::vector<std::string>& data) : heap(data), size((int)data.size()) {
        for (int i = size / 2 - 1; i >= 0; i--) siftDown(i);
    }

    bool empty() const { return size == 0; }

    // Manda el máximo al final del arreglo y reduce el heap
    void extractMaxToEnd() {
        std::swap(heap[0], heap[size - 1]);
        size--;
        siftDown(0);
    }

private:
    std::vector<std::string>& heap;  // referencia: se ordena en el mismo arreglo
    int size;                        // elementos que siguen en el heap

    // Hunde el elemento i hasta cumplir la propiedad de max-heap
    void siftDown(int i) {
        while (true) {
            int largest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < size && heap[left] > heap[largest]) largest = left;
            if (right < size && heap[right] > heap[largest]) largest = right;
            if (largest == i) break;
            std::swap(heap[i], heap[largest]);
            i = largest;
        }
    }
};

// Construye el heap y saca el máximo n veces: O(n log n), in-place
class HeapSort {
public:
    static void sort(std::vector<std::string>& arr) {
        BinaryHeap heap(arr);
        while (!heap.empty()) heap.extractMaxToEnd();
    }
};

#endif
