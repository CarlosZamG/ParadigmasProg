#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
Programa que calcula los términos de la sucesión de Fibonacci de manera recursiva en paralelo con OpenMP

- Comando de compilación:
gcc FiboParalelo.c -o FiboParalelo -fopenmp

- Comando de ejecución:
./FiboParalelo N

Donde 'N' representa el último término que se va a calcular

- Salida:
Profundidad: 3 Hilo: 0 a_n = 1 n = 1

Profundidad: 3 Hilo: 2 a_n = 1 n = 2

Profundidad: 2 Hilo: 0 a_n = 2 n = 3  a_(n-1) = 1 a_(n-2) = 1

Profundidad: 4 Hilo: 0 a_n = 1 n = 2

Profundidad: 4 Hilo: 2 a_n = 1 n = 1

Profundidad: 3 Hilo: 2 a_n = 2 n = 3  a_(n-1) = 1 a_(n-2) = 1

Profundidad: 3 Hilo: 3 a_n = 1 n = 2

Profundidad: 2 Hilo: 3 a_n = 3 n = 4  a_(n-1) = 2 a_(n-2) = 1

Profundidad: 1 Hilo: 1 a_n = 5 n = 5  a_(n-1) = 3 a_(n-2) = 2


Concepto de Task

La asignación de tareas facilita la paralelización de aplicaciones
donde las unidades de trabajo se generan dinámicamente, como
en estructuras recursivas o bucles while

La directiva task define el código asociado con la tarea y su entorno de datos.

Cuando un subproceso encuentra una construcción de tarea, puede optar por ejecutar
la tarea inmediatamente o posponer su ejecución hasta un momento posterior. Si se
aplaza la ejecución de la tarea, la tarea se coloca en un grupo conceptual de tareas
asociado con la región paralela actual. Los subprocesos en el equipo actual tomarán
tareas del grupo y las ejecutarán hasta que el grupo esté vacío. Un subproceso que
ejecuta una tarea puede ser diferente del subproceso que lo encontró originalmente.

*/


int fibonacci(int,int);


int fibonacci(int n, int prof)
{
    

    if(n<3){
    
        printf("\n Profundidad: %d Hilo: %d a_n = %d n = %d\n",prof,omp_get_thread_num(),1,n);
        return 1;
    }

    int n_1, n_2;

    #pragma omp task shared(n_1) firstprivate(n,prof)
    n_1 = fibonacci(n-1,prof+1);

    #pragma omp task shared(n_2) firstprivate(n,prof)
    n_2 = fibonacci(n-2,prof+1);
    

    /*
    La directiva taskwait especifica una espera en la finalización de las tareas
    secundarias generadas desde el comienzo de la tarea actual (implícita o explícita)
    */
    #pragma omp taskwait
    int a_n =n_1 + n_2;
    
    printf("\n Profundidad: %d Hilo: %d a_n = %d n = %d  a_(n-1) = %d a_(n-2) = %d\n",prof,omp_get_thread_num(),a_n,n,n_1,n_2);
    return a_n;

}

int main(int argc, char *argv[]){

    int n = 3;
    if(argc>1){
        n = atoi(argv[1]);
    }
    /*
    omp_set_dynamic(int);
    Indica que el tiempo de ejecución puede ajustar
    la cantidad de subprocesos disponibles en las próximas
     regiones paralelas.
    */
    omp_set_dynamic(0);
    omp_set_num_threads(4);

    #pragma omp parallel shared(n)
    {   
        #pragma omp single
        {
            fibonacci(n,1);
        }
        

    }
    

}