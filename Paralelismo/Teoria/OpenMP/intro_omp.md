# Introducción a OpenMP

**OpenMP** (**Open M**ulti-**P**rocessing) es una interfaz de programación de aplicaciones (***API***) que permite convertir programas secuenciales en paralelo. Al usar OpenMP, el compilador es responsable de lidiar con los detalles *engorrosos* de la generación, inicialización y finalización de hilos. La desventaja es que se sacrifica el control del programador para darle comodidad.

OpenMP utiliza lo que conoce como *construcciones de trabajo compartido* para indicar al compilador que inicie hilos y haga que realicen una tarea específica. Las construcciones de trabajo compartido van desde la paralelización automática de bucles hasta la descripción explícita de tareas.

Hagamos nuestro primer *hola mundo* con OpenMP:

```c
#include <stdio.h>
#include <omp.h>

int main(){

    int n_threads = 5;

    #pragma omp parallel num_threads(n_threads)
    {
        printf("Hola mundo desde el hilo con ID: %d\n", omp_get_thread_num());
    }
}
```

Notemos los pasos esenciales que hacen que nuestro programa haga uso de **OpenMP**:

1. Estamos incluyendo el archivo de cabecera `#include <omp.h>`.
2. La directiva `#pragma omp parallel` que lanza múltiples hilos, cada uno ejecutando las instrucciones del bloque. Las directivas pragma suelen tener un número de claúsulas opcionales que modifican su comportamiento, dichas claúsulas pueden estar separadas por coma o por un espacio en blanco. En nuestro ejemplo, estamos usando la claúsula `num_threads()` para especificar el número de hilos que serán lanzados.
3. Podemos usar funciones de la biblioteca de OpenMPm, en este caso estamos usando la función `omp_get_thread_num()` para obtener el **ID** del hilo que está ejecutando la instrucción.

Los programas hechos con OpenMP siguen una estructura **Globalmente secuencial, localmente paralelo**, lo que significa que hay un flujo principal que se bifurca en múltiples hilos que después vuelven a ser unidos al hilo principal, y este proceso puede ser repetido varias veces. A este modelo de paralelismo se le conoce como paralelismo *fork-join*.

