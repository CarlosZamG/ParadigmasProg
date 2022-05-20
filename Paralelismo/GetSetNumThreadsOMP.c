#include <stdio.h>
#include <omp.h>

/*
Programa en OpenMP para entender el funcionamiento de 
omp_set_num_threads(N) y omp_get_num_threads()

- Comando para compilar:
gcc GetSetNumThreadsOMP.c -o GetSetNumThreadsOMP -fopenmp

-Comando para ejecutar:
./GetSetNumThreadsOMP

-Salida:
Número actual de hilos: 1

Número actual de hilos: 1

Número actual de hilos: 4 | Yo soy el hilo 2
Soy el hilo 0 de 4
Soy el hilo 1 de 4
Soy el hilo 3 de 4
Soy el hilo 2 de 4

Número actual de hilos: 1

Número actual de hilos: 8 | Yo soy el hilo 4
Soy el hilo 0 de 8
Soy el hilo 7 de 8
Soy el hilo 4 de 8
Soy el hilo 1 de 8
Soy el hilo 5 de 8
Soy el hilo 2 de 8
Soy el hilo 3 de 8
Soy el hilo 6 de 8


*/


int main(){
    
    int numActual = omp_get_num_threads();
    printf("\nNúmero actual de hilos: %d\n", numActual);

    omp_set_num_threads(4);
    // omp_set_num_threads(int N) permite indicar el número de threads que se crearán, en este ejemplo son 4.

    numActual = omp_get_num_threads();
    printf("\nNúmero actual de hilos: %d \n", numActual);

    //Como estamos afuera de la región paralela el número de hilos es 1

    #pragma omp parallel shared(numActual)
    {
        int tid;
        tid = omp_get_thread_num();
        /*
        NOTA: la variable tid muere con la región paralela, fuera de ella no existe,
        por eso podemos volver a declararla en la sigiente región
        */

        #pragma omp single
        { 
            //El bloque se ejecuta por un único thread. No tiene por qué ser el maestro.
            
            numActual = omp_get_num_threads(); // En este caso, nos dice que hay 4 hilos en la región paralela
            printf("\nNúmero actual de hilos: %d | Yo soy el hilo %d \n", numActual,tid);
        }

        
        printf("Soy el hilo %d de %d\n", tid, numActual);
    }
    


    omp_set_num_threads(8);
    //Indicamos que vamos a crear 8 hilos
    
    
    numActual = omp_get_num_threads();
    printf("\nNúmero actual de hilos: %d \n", numActual);
    //Como estamos afuera de la región paralela el número de hilos es 1

    #pragma omp parallel shared(numActual)
    {
        int tid;
        tid = omp_get_thread_num();

        #pragma omp single
        { 
            //El bloque se ejecuta por un único thread. No tiene por qué ser el maestro.
            
            numActual = omp_get_num_threads(); // En este caso, nos dice que hay 8 hilos en la región paralela
            printf("\nNúmero actual de hilos: %d | Yo soy el hilo %d \n", numActual,tid);
        }

        
        printf("Soy el hilo %d de %d\n", tid, numActual);
    }



}
