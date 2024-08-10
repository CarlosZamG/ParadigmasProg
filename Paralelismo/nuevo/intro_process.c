#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
Comando para compilar:

gcc intro_process.c -o intro_process

Salida:

Hola desde el proceso padre (el proceso original) con id: 8770
Hola desde el proceso hijo (el proceso nuevo) con id: 8771

*/

int main(){
    
    int id = fork();
    if (id == -1){
        printf("Ocurrió un error\n");
    }else if (id == 0){
        printf("Hola desde el proceso hijo (el proceso nuevo) con id: %d\n", getpid());
    }else{
        printf("Hola desde el proceso padre (el proceso original) con id: %d\n", getpid());
    }
}