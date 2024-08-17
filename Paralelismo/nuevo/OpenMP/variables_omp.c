#include <stdio.h>
#include <omp.h>

/*
Comando para compilar:

gcc variables_omp.c -o variables_omp -fopenmp

Salida 1:
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 10)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 15)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 30)
(x, y, a) = (5, 5, 30)

Salida 2:
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 0)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 5)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 25)
(x, y, a) = (5, 5, 25)

*/

int main(){

    int x = 1;
    int y = 1;
    
    int a = 0;

    x = 5;
    y = 5;

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
    
    #pragma omp parallel private(x) firstprivate(y) num_threads(4)
    {
        int id = omp_get_thread_num();
        int n1 = id*x;
        int n2 = id*y;
        //Por reglas de OpenMP, las variables id, n1 y n2 son privadas
        
        x = x+1;
        y = y+1;
        a = a + n2;
        printf("Hilo con ID: %3d | n1: %3d | n2: %3d | (x, y, a) = (%d, %d, %d)\n", id, n1, n2, x, y, a);
    }

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
}