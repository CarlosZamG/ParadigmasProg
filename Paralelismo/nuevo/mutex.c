#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 10000

/*
Comando para compilar:

gcc -pthread mutex.c -o mutex

Ejecución múltiples veces:

for run in {1..20}; do ./mutex; done

Salida:
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000
10000

*/

int number = 0;
pthread_mutex_t lock;

void* add(void *data){

    pthread_mutex_lock(&lock);
    number = number + 1;
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main(){
    

    pthread_t threads[N];
    pthread_mutex_init(&lock, NULL);

    int i;
    for(i = 0; i<N; i++)
        if (pthread_create(threads + i,  NULL, add, NULL) != 0) return EXIT_FAILURE;

    for (i = 0; i<N; i++)
        if (pthread_join(threads[i], NULL) != 0) return EXIT_FAILURE;

    pthread_mutex_destroy(&lock);

    printf("%d\n",number);

}