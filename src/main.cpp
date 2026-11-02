#include "ordenamiento.hpp"
#include "arbolALV.hpp"
#include "HeapSort.hpp"

int main()
{
    ejecutarQuickSort("data/dataset.txt", "data/dataset_quicksort.txt", 100);
    ejecutarHeapSort("data/dataset.txt", "data/sorted_heapsort.txt", 100);
    ejecutarOrdenamientoAVL("data/dataset.txt", "data/ordenado_avl.txt", 100);
    return 0;
}
