#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
Comando para compilar:

gcc -pthread multiple_restaurants.c -o multiple

Salida:

Varios cocineros trabajando en Tlalnepantla


Varios cocineros trabajando en Toluca

El chef está cocinando en el restaurante con id: 7269
El chef está cocinando en el restaurante con id: 7269
El chef está cocinando en el restaurante con id: 7270
El chef está cocinando en el restaurante con id: 7270
Orden lista en el restaurante con id: 7269
Orden lista en el restaurante con id: 7270
Orden lista en el restaurante con id: 7269
Orden lista en el restaurante con id: 7270

*/

char *location;

void* work(void *data){
    
    printf("El chef está cocinando en el restaurante con id: %d\n", getpid());
    sleep(2);
    printf("Orden lista en el restaurante con id: %d\n", getpid());
    return NULL;
}

int main(){

    int id = fork();
    if (id){
        // Estamos en el proceso original
        location = "Tlalnepantla";
    }else{
        // Estamos en el nuevo proceso
        location = "Toluca";
    }

    // Restaurante con hilos en paralelo (múltiples cocineros)
    printf("\nVarios cocineros trabajando en %s\n\n", location);
    pthread_t chef1, chef2;

    if (pthread_create(&chef1, NULL, work, NULL) != 0) return EXIT_FAILURE;
    if (pthread_create(&chef2, NULL, work, NULL)) return EXIT_FAILURE;

    if (pthread_join(chef1, NULL) != 0) return EXIT_FAILURE;
    if (pthread_join(chef2, NULL)) return EXIT_FAILURE;

    return EXIT_SUCCESS;

}