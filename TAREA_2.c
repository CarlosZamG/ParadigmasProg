#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*
Programa que comunica dos procesos con MPI

- Comando para compilar:
mpicc TAREA_2.c -o Tarea2

- Comando para Ejecución: 
mpirun -n 2 ./Tarea2

- Salida:
Proceso 0 recibió el dato -1 del proceso 1
Proceso 1 recibió el dato -1 del proceso 0


*/


int main(int argc, char** argv){

    MPI_Init(NULL,NULL);
    /*
    Se construyen todas las variables globales e internas de MPI.
    Se forma un comunicador en torno a todos los procesos que se generaron
    y se asignan rangos (funcionan como identificadores) únicos a cada proceso
    
    Toma dos argumentos que no son necesarios
    */


    int world_rank;
    int world_size;

    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    /*
    MPI_Comm_rank(MPI_Comm comunicador,int* rango)  devuelve el rango de un proceso en un comunicador.
     A cada proceso dentro de un comunicador se le asigna un rango incremental a partir de cero.
     Los rangos de los procesos se utilizan principalmente con fines de identificación al enviar y recibir mensajes.
    */
    
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    /*
    MPI_Comm_size(MPI_Comm comunicador, int* tamaño) devuelve el tamaño de un comunicador.

    MPI_COMM_WORLD (construido para nosotros por MPI) encierra todos los procesos en el trabajo,
    por lo que esta llamada debería devolver la cantidad de procesos que se solicitaron para el trabajo
    */


    /*
    Mensaje de Error
    Si la cantidad de procesos solicitados es diferente de 2, ejecuta esta parte 
    */
    if(world_size != 2){

        fprintf(stderr, "Solo pueden ser 2 procesos\n");
        MPI_Abort(MPI_COMM_WORLD,EXIT_FAILURE);

        /*
        int MPI_Abort(MPI_Comm comm, int errorcode)

        Termina el entorno de ejecución de MPI
        Parámetros:
            comm: comunicador, canal
            errorcode: código de error  


        Posible salida:
        Solo pueden ser 2 procesos
        application called MPI_Abort(MPI_COMM_WORLD, 1) - process 1   
        */        
    }

    int dato;
    //Es lo que se va a enviar

    if(world_rank == 0){
        
        dato = -1;
        MPI_Send(
            /*Dato: */      &dato,
            /*Contador:*/   1,
            /*Tipo: */      MPI_INT,
            /*Destino: */   world_rank + 1,
            /*Etiqueta: */  0,
            /*Comunicador: */ MPI_COMM_WORLD 
        );

        MPI_Recv(
            /*Dato: */      &dato,
            /*Contador:*/   1,
            /*Tipo: */      MPI_INT,
            /*Origen: */   world_rank + 1,
            /*Etiqueta: */  0,
            /*Comunicador: */ MPI_COMM_WORLD,
            /*Status: */    MPI_STATUS_IGNORE 
        );
        printf("Proceso %d recibió el dato %d del proceso %d \n", world_rank, dato, world_rank + 1);
    }
    else if(world_rank == 1){

        MPI_Recv(
            /*Dato: */      &dato,
            /*Contador:*/   1,
            /*Tipo: */      MPI_INT,
            /*Origen: */   world_rank - 1,
            /*Etiqueta: */  0,
            /*Comunicador: */ MPI_COMM_WORLD,
            /*Status: */    MPI_STATUS_IGNORE 
        );
        printf("Proceso %d recibió el dato %d del proceso %d \n", world_rank, dato, world_rank - 1);

        MPI_Send(
            /*Dato: */      &dato,
            /*Contador:*/   1,
            /*Tipo: */      MPI_INT,
            /*Destino: */   world_rank - 1,
            /*Etiqueta: */  0,
            /*Comunicador: */ MPI_COMM_WORLD 
        );

    }

    MPI_Finalize();
    //MPI_Finalize() se utiliza para limpiar el entorno MPI. No se pueden realizar más llamadas MPI después de esta.

}
