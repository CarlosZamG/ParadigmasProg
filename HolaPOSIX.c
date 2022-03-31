#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/*
Hola mundo en paralelo con Hilos en POSIX

-Comando de Compilación:
gcc HolaPOSIX.c -lpthread -o HolaPOSIX

-Comando de Ejecución:
./HolaPOSIX

-Salida:
Hola!!! Soy el hilo 0
Hola!!! Soy el hilo 3
Hola!!! Soy el hilo 1
Hola!!! Soy el hilo 5
Hola!!! Soy el hilo 2
Hola!!! Soy el hilo 4
Hola!!! Soy el hilo 6
Hola!!! Soy el hilo 7
Hola!!! Soy el hilo 8
Hola!!! Soy el hilo 9

*/


// Número de Hilos
#define MAX_HILO 10

//Función que va a ejecutar cada hilo recibe un puntero void * y que devuelve void *
void* hola(void* id)
{   
    int a = *((int *) id);
    printf("Hola!!! Soy el hilo %d \n",a);

}
int main()
{
    
    pthread_t hilos[MAX_HILO];      //Arreglo con los hilos
    int* ids = (int*) malloc(MAX_HILO*sizeof(int));     //Arreglo para que cada hilo tenga su ID


    /*
    La función que nos permite crear un un nuevo hilo de ejcución es pthread_create() que admite cuatro parámetros:

    - pthread_t * es un puntero a un identificador de thread. La función nos devolverá este valor relleno,
    de forma que luego podamos referenciar al hilo para "hacerle cosas",
    
    - pthread_attr_t * son los atributos de creación del hilo. Hay varios atributos posibles.
    Se puede pasar NULL, con lo que el hilo se creará con sus atributos por defecto y para nuestro ejemplo es suficiente.

    - void *(*)(void *)  Aunque asuste, no es más que el tipo de una función que admite un puntero void * y que devuelve void *.
    Eso quiere decir que a este parámetro le podemos pasar el nombre de una función que cumpla lo que acabamos de decir.
    Esta función es la que se ejecutará como un hilo aparte. 
    
    - void * es el parámetro que se le pasará a la función anterior cuando se ejecute en el hilo aparte.
    De esta manera nuestro programa principal puede pasar un único parámetro (que puede ser cualquier cosa, como una estructura compleja)
    a la función que se ejecutará en el hilo. La función del hilo sólo tendrá que hacer el "cast" adecuado.
    
    */

    for (int i = 0; i < MAX_HILO; i++){
        ids[i] = i;
        pthread_create(&hilos[i], NULL, hola,(void*) &ids[i]);

    }
    /*
    pthread_join() espera a que finalice el hilo

    pthread_join toma sólo dos argumentos: EL hilo esperado y puntero a void* donde se puede almacenar el estado de salida del hilo especificado.
    Si no queremos recuperar el código de salida del hilo esperado, debemos pasar el valor NULL.
    */
    for (int i = 0; i < MAX_HILO; i++)
        pthread_join(hilos[i], NULL);
    return 0;
}