# Cómo compilar y ejecutar

Se necesita tener instalado `g++` (por ejemplo, mediante MinGW-w64) y ejecutarlo desde la carpeta raíz del proyecto. El archivo de entrada esperado es `data\dataset.txt`.

En PowerShell, compila el programa con:

```powershell
g++ -std=c++17 -Iinclude src\main.cpp src\ordenamiento.cpp src\arbolALV.cpp src\HeapSort.cpp -o programa.exe
```

Luego ejecútalo desde esa misma carpeta:

```powershell
.\programa.exe
```

El programa ejecuta QuickSort, HeapSort y el ordenamiento AVL. Los resultados completos se guardan en `data\dataset_quicksort.txt`, `data\sorted_heapsort.txt` y `data\ordenado_avl.txt`, respectivamente. También muestra en la consola el tiempo de ejecución y las primeras 100 palabras ordenadas.