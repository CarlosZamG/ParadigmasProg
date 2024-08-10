#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Comando para compilar:

gcc -pthread restaurant.c -o restaurant

Salida:

Un cocinero

El chef está cocinando
Orden lista
El chef está cocinando
Orden lista

Varios cocineros

El chef está cocinando
El chef está cocinando
Orden lista
Orden lista

*/

void* work(void *data){
    
    printf("El chef está cocinando\n");
    sleep(2);
    printf("Orden lista\n");
    return NULL;
}

int main(){
    
    //Restaurante en secuencial (un solo cocinero)
    printf("\nUn cocinero\n\n");
    work(NULL);
    work(NULL);

    // Restaurante con hilos en paralelo (múltiples cocineros)
    printf("\nVarios cocineros\n\n");
    pthread_t chef1, chef2;

    if (pthread_create(&chef1, NULL, work, NULL) != 0) return EXIT_FAILURE;
    if (pthread_create(&chef2, NULL, work, NULL)) return EXIT_FAILURE;

    if (pthread_join(chef1, NULL) != 0) return EXIT_FAILURE;
    if (pthread_join(chef2, NULL)) return EXIT_FAILURE;

}