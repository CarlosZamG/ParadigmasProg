#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Comando para compilar:

gcc -pthread variables_pthreads.c -o variables_pthreads

Salida:

El valor de number es: 50
El valor de number es: 100

*/

int number = 0;


void* work1(void *data){
    
    number = number + 50;
    printf("El valor de number es: %d\n", number);
    return NULL;
}

void* work2(void *data){
    
    sleep(2);
    number = number + 50;
    printf("El valor de number es: %d\n", number);
    return NULL;
}


int main(){
    

    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, work1, NULL) != 0) return EXIT_FAILURE;
    if (pthread_create(&t2, NULL, work2, NULL)) return EXIT_FAILURE;

    if (pthread_join(t1, NULL) != 0) return EXIT_FAILURE;
    if (pthread_join(t2, NULL)) return EXIT_FAILURE;

}