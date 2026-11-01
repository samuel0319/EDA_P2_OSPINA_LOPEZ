#include "ordenamiento.hpp"
#include "arbolALV.hpp"

int main()
{
    ejecutarQuickSort("dataset.txt", "dataset_quicksort.txt", 100);
    ejecutarOrdenamientoAVL("dataset.txt", "ordenado_avl.txt",100);
    return 0;
}