#include <stdio.h>
#include <omp.h>

/*
Comando para compilar:

gcc synchro_examples.c -o synchro_examples -fopenmp

Ejecución múltiples veces:

for run in {1..5}; do ./synchro_examples; done

Salida:

x: 3 | y: 3
x: 2 | y: 2
x: 3 | y: 3
x: 6 | y: 4
x: 3 | y: 3

*/

int main(){
    
    int x = 0;
    int y = 0;
    /*
    printf("\nCon condición de carrera\n");

    #pragma omp parallel num_threads(4)
    {
        x += y++;
    }

    printf("x: %d | y: %d\n", x, y);
    
    
    x = 0;
    y = 0;

    printf("\nCon critical\n");

    #pragma omp parallel num_threads(4)
    {
        #pragma omp critical
        {
            x += y++;
        }
        
    }

    printf("x: %d | y: %d\n", x, y);
    */
    x = 0;
    y = 0;

    printf("\nCon atomic\n");

    #pragma omp parallel num_threads(4)
    {
        #pragma omp atomic
            x += y++;
        
    }

    printf("x: %d | y: %d\n", x, y);
}