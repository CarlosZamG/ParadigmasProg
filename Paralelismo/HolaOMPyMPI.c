#include <mpi.h>
#include <stdio.h>
#include <omp.h>

/*
Programa que combina OpenMP + MPI
Crea diversos procesos en varios Host con MPI y cada proceso bifurca en hilos con OpenMP 
Necesita de un archivo hostfile (machines.LINUX) para saber en que máquinas se va a ejecutar

-Comando para compilar: 
mpicc  hola.c -fopenmp -o hola


- Comando para su ejecución: 
mpirun --mca btl vader,self --hostfile machines.LINUX -n 3 ./hola


- Salida:
Hilo: 0 Name: compute-0-1.local, rank 0 out of 3 processors
Hilo: 3 Name: compute-0-1.local, rank 0 out of 3 processors
Hilo: 1 Name: compute-0-1.local, rank 1 out of 3 processors
Hilo: 0 Name: compute-0-1.local, rank 1 out of 3 processors
Hilo: 3 Name: compute-0-1.local, rank 1 out of 3 processors
Hilo: 2 Name: compute-0-1.local, rank 1 out of 3 processors
Hilo: 0 Name: compute-0-1.local, rank 2 out of 3 processors
Hilo: 1 Name: compute-0-1.local, rank 2 out of 3 processors
Hilo: 3 Name: compute-0-1.local, rank 2 out of 3 processors
Hilo: 2 Name: compute-0-1.local, rank 0 out of 3 processors
Hilo: 2 Name: compute-0-1.local, rank 2 out of 3 processors
Hilo: 1 Name: compute-0-1.local, rank 0 out of 3 processors

*/


int main(int argc, char** argv){

    //Inicializa OpenMP de la forma normal
    MPI_Init(NULL, NULL);

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);


    //Guarda el nombre del Host(o procesador) en la variable processor_name
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int len_name;
    MPI_Get_processor_name(processor_name, &len_name);

    int nthread;


    //Crea una región paralela
    #pragma omp parallel private(nthread)
    {
        nthread = omp_get_thread_num();
        printf("Hilo: %d Name: %s, rank %d out of %d processors\n",
        nthread, processor_name, world_rank, world_size);

        /*
        nthread: número de hilo
        processor_name: nombre del Host
        world_rank: número del proceso
        world_size; número total de procesos
        */

    }
    MPI_Finalize();
}