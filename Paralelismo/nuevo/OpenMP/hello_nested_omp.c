#include <stdio.h>
#include <omp.h>

/*
Programa que realiza un hola mundo con OpenMP

Comando para compilar:

gcc hello_nested_omp.c -o hello_nested_omp -fopenmp

Salida:
Hola mundo con paralelismo anidado desde el hilo 0.0
Hola mundo con paralelismo anidado desde el hilo 1.0
Hola mundo con paralelismo anidado desde el hilo 0.1
Hola mundo con paralelismo anidado desde el hilo 4.1
Hola mundo con paralelismo anidado desde el hilo 1.1
Hola mundo con paralelismo anidado desde el hilo 2.1
Hola mundo con paralelismo anidado desde el hilo 2.0
Hola mundo con paralelismo anidado desde el hilo 3.1
Hola mundo con paralelismo anidado desde el hilo 3.0
Hola mundo con paralelismo anidado desde el hilo 4.0|   

*/

int main(){

    omp_set_nested(1);


    int n_threads = 5;
    int n_inner = 2;

    #pragma omp parallel num_threads(n_threads)
    {
        int id = omp_get_thread_num();

        #pragma omp parallel num_threads(n_inner) firstprivate(id)
        {
            printf("Hola mundo con paralelismo anidado desde el hilo %d.%d\n",id, omp_get_thread_num());
        }
        
    }
}