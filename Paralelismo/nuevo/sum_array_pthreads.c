#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>


/*
El siguiente programa realiza la suma de los elementos de un arreglo de números
utilizando hilos POSIX

Comando para compilar:

gcc -pthread sum_array_pthreads.c -o sum_array_pthreads

Salida:
El resultado de la suma es:153

*/

#define NUM_THREADS 4
#define ARRAY_SIZE 17

int numbers[ARRAY_SIZE] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
int sum_thread[NUM_THREADS];

void* add(void* arg){

    // Realizamos la división para ver cuántos números del arreglo le tocan a cada hilo 
    int div = ceil((float)ARRAY_SIZE/(float)NUM_THREADS);
    
    // Obtenemos un identificador para cada hilo
    int id = *((int*) arg);
    
    // Realizamos la repartición de los números correspondientes
    for(int j = id*div; j < (id+1)*div; j++)
    {
        // Cada hilo suma su parte correspondiente
        if(j < ARRAY_SIZE){
            sum_thread[id] += numbers[j];
        }
    }
    return NULL;
}

int main(){
    

    for(int i = 0; i < NUM_THREADS; i++) sum_thread[i] = 0; 
    
    pthread_t threads[NUM_THREADS];

    // Creamos un arreglo para que cada hilo tenga su identificador
    int* ids = (int*) malloc(NUM_THREADS*sizeof(int));

    int i;
    for(i = 0; i < NUM_THREADS; i++){
        ids[i] = i;
        if (pthread_create(threads + i,  NULL, add, &ids[i]) != 0) return EXIT_FAILURE;
    }
        

    for (i = 0; i < NUM_THREADS; i++)
        if (pthread_join(threads[i], NULL) != 0) return EXIT_FAILURE;

    
    int total_sum = 0;

    // Sumamos las cantidades obtenidas por cada hilo
    for (i = 0; i < NUM_THREADS; i++){
        total_sum += sum_thread[i];
    }
        

    printf("El resultado de la suma es:%d\n",total_sum);

    // Liberamos el arreglo de idenficadores
    free(ids);
}