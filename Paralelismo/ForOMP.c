#include <stdio.h>
#include <omp.h>

/*
Programa para entender los bucles for en OpenMP

-Comando para compilar:
gcc ForOMP.c -o ForOMP -fopenmp

-Comando para ejecutar:
./ForOMP

-Salida:
Soy el hilo: 3 , contador: 75
Soy el hilo: 3 , contador: 76
Soy el hilo: 3 , contador: 77
Soy el hilo: 3 , contador: 78
Soy el hilo: 3 , contador: 79
Soy el hilo: 3 , contador: 80

...

Soy el hilo: 0 , contador: 5
Soy el hilo: 0 , contador: 6
Soy el hilo: 0 , contador: 7
Soy el hilo: 0 , contador: 8
Soy el hilo: 0 , contador: 9

...

Soy el hilo: 1 , contador: 34
Soy el hilo: 1 , contador: 35

...

Soy el hilo: 2 , contador: 64
Soy el hilo: 2 , contador: 65
Soy el hilo: 2 , contador: 66
Soy el hilo: 2 , contador: 67
Soy el hilo: 2 , contador: 68
Soy el hilo: 2 , contador: 69
....

Soy el hilo: 1 , contador: 44
Soy el hilo: 1 , contador: 45
Soy el hilo: 1 , contador: 46
Soy el hilo: 1 , contador: 47
Soy el hilo: 1 , contador: 48
Soy el hilo: 1 , contador: 49
Soy el hilo: 2 , contador: 73
Soy el hilo: 2 , contador: 74
Acabó el for

*/


int main(){

    omp_set_num_threads(4);

    #pragma omp parallel 
    {
        #pragma omp for
        for(int i = 0; i<100;  i++)
        {
            printf("\nSoy el hilo: %d , contador: %d", omp_get_thread_num(),i);        

        } 
        /*
        Se crea cierto nu ́mero de threads que ejecutan un subconjunto de las iteraciones
        del bucle FOR. Todos los threads esperan al final del parallel for (fuerza una
        sincronización).
        */

        #pragma omp single
        printf("\nAcabó el for\n");
    }

    /*
    #pragma omp parallel for 
    Es una directiva para abreviar
        
        #pragma omp parallel
            #pragma omp for

    */
    #pragma omp parallel for schedule(dynamic,10)
    for(int i = 0; i<100;  i++)
    {
            printf("\nSoy el hilo: %d , contador: %d", omp_get_thread_num(),i);        

    }
    printf("\nAcabó el for\n");
    
    /*
    Una cláusula schedule indica la forma como se dividen las iteraciones del for entre los threads:
        
        • schedule(static,tamaño) las iteraciones se dividen según el tamaño, y la asignación
        se hace estáticamente a los threads. Si no se indica el tamaño se divide por igual
        entre los threads.
        
        • schedule(dynamic,tamaño) las iteraciones se dividen según el tamaño y se asignan
        a los threads dinámicamente cuando van acabando su trabajo.
        
        • schedule(guided,tamaño) las iteraciones se asignan dinámicamente a los threads
        pero con tamaños decrecientes,
    
    */

}
