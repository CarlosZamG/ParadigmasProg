#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 10000

/*
Comando para compilar:

gcc -pthread race_conditions.c -o race_conditions

Ejecución múltiples veces:

for run in {1..20}; do ./race_conditions; done

Salida:
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


*/

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