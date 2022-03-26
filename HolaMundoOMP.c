#include <stdio.h>
#include <omp.h>
#include <unistd.h>

/*
Programa que hace un Hola Mundo en Paralelo con OpenMP 

- Comando de compilación:
gcc HolaMundoOMP.c -o HolaMundoOMP -fopenmp

- Comando de ejecución:
./HolaMundoOMP

- Salida:
Hola Mundo Paralelo tid: 5
Hola Mundo Paralelo tid: 2
Hola Mundo Paralelo tid: 3
Hola Mundo Paralelo tid: 4
Hola Mundo Paralelo tid: 1
Hola Mundo Paralelo tid: 6
Hola Mundo Paralelo tid: 7
Hola Mundo Paralelo tid: 0

*/

int main(){

    int tid;

    /*
    Ya que OpenMP es un modelo de memoria compartida, muchas variables en
    el código son visibles a todos los threads por defecto. Pero a veces es necesario
    tener variables privadas y pasar valores entre bloques secuenciales del código
    y bloques paralelos, por lo cual, es necesario definir atributos a los datos:

    • shared: los datos en la región paralela son compartidos y accesibles por to-
    dos los threads simultáneamente.

    • private: los datos en la región paralela son privados para cada thread y cada
    uno tiene una copia de ellos sobre una variable temporal.
    
    • default: permite al programador definir cómo serán los datos dentro de la
    región paralela (shared, private, o none).
    
    */


    #pragma omp parallel private(tid) num_threads(8)
    {
        /*
        Se crea cierto número de threads que ejecutan el mismo código.
        En este caso se crean 8 hilos con num_threads(8).
        Cada thread espera al final.
        */


        tid = omp_get_thread_num();
        //Devuelve el identificador del hilo
        
        if(tid==0) sleep(tid+1);
        //Si este es el hilo 0, se espera un segundo con sleep() de unistd.h ; tid+1 = 0+1 = 1 

        printf("Hola Mundo Paralelo tid: %d \n",tid);

    }
    


}