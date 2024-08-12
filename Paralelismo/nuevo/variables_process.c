#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

/*
Comando para compilar:

gcc variables_process.c -o variables_process

Salida:
Hola desde el proceso hijo (el proceso nuevo), el valor de number es: 50
Hola desde el proceso padre (el proceso original), el valor de number es: 50

*/

int main(){
    
    int number = 0;

    int id = fork();
    
    if (id == -1){
        printf("Ocurrió un error\n");
    }else if (id == 0){
        number = number + 50;
        printf("Hola desde el proceso hijo (el proceso nuevo), el valor de number es: %d\n", number);
    }else{
        wait(0);
        sleep(2);
        number = number + 50;
        printf("Hola desde el proceso padre (el proceso original), el valor de number es: %d\n", number);
    }
}