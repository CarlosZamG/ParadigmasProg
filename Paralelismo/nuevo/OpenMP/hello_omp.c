#include <stdio.h>
#include <omp.h>

/*
Programa que realiza un hola mundo con OpenMP

Comando para compilar:

gcc hello_omp.c -o hello_omp -fopenmp

Salida:
Hola mundo desde el hilo con ID: 4
Hola mundo desde el hilo con ID: 0
Hola mundo desde el hilo con ID: 3
Hola mundo desde el hilo con ID: 2
Hola mundo desde el hilo con ID: 1

*/

int main(){

    int n_threads = 5;

    #pragma omp parallel num_threads(n_threads)
    {
        printf("Hola mundo desde el hilo con ID: %d\n", omp_get_thread_num());
    }
}