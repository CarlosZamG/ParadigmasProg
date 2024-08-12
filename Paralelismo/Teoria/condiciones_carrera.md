# Condiciones de carrera

La definición formal de una **condición de carrera** (o *race condition* en inglés) es cuando sucede un comportamiento anormal del programa causado porque el resultado depende de una secuencia de eventos que se ejecutan en orden arbitrario y van a trabajar sobre un mismo recurso compartido. Esto puede provocar que el resultado de ejecutar el programa varias veces los mismos  datos de entrada sea diferente. Este es un problema común al trabajar con hilos que hacen modifificaciones sobre una misma variable compartida, en este caso los hilos *compiten* por llegar primero al recurso compartido, y el resultado del programa depende de cuál hilo llegó primero. 

Veamos un ejemplo en código con **pThreads**:


```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 10000


int number = 0;


void* add(void *data){
    
    number = number + 1;
    return NULL;
}

int main(){
    

    pthread_t threads[N];

    int i;
    for(i = 0; i<N; i++)
        if (pthread_create(threads + i,  NULL, add, NULL) != 0) return EXIT_FAILURE;

    for (i = 0; i<N; i++)
        if (pthread_join(threads[i], NULL) != 0) return EXIT_FAILURE;

    printf("%d\n",number);

}
```

Veamos que pasa si ejecutamos el programa anterior múltiples veces con el comando:

```sh
for run in {1..20}; do ./race_conditions; done
```
Tenemos la siguiente salida:

```sh
10000
10000
10000
9999
10000
10000
10000
9999
9999
10000
10000
9998
10000
10000
10000
9996
9999
10000
9999
10000
```

