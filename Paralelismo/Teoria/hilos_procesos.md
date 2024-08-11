# Hilos vs Procesos

## Procesos

Un **proceso** es un programa en ejecución, es decir, la entidad del sistema operativo que encapsula el código, los datos, recursos y el estado de ejecución requerido por el sistema operativo para manejar el programa.

Veamos ejemplos en código de cómo usar procesos en **Linux**:

El siguiente código se encuentra en `/Paralelismo/nuevo/intro_process.c`
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
```

Y nos produce la siguiente salida:
```sh
Hola desde el proceso padre (el proceso original) con id: 8770
Hola desde el proceso hijo (el proceso nuevo) con id: 8771
``` 

Al momento de llamar a la función `fork()`, se crea una copia exacta de la memoria del proceso, incluyendo el código y los datos tal y como estaban al momento de la llamada. Comúnmente suele decir que el proceso original es el proceso *padre* mientras que la copia es el proceso *hijo*. A este proceso se le conoce en español como *bifurcar*.

La función `fork()` devuelve un entero según sea el caso:
- `-1` en caso de que haya ocurrido un error.
- `0` para el nuevo proceso.
- El identificador del proceso hijo para el proceso original.

Esto último nos permite diferenciar entre los procesos y ejecutar diferentes instrucciones para cada uno.

**NOTA**: Cada proceso tiene un único identificador que podemos obtener con la función `getpid()`.

## Hilos

El ***Scheduler*** es el proceso que se encarga de asignar los recursos del sistema para desempeñar las tareas.

Un **hilo** es la unidad más pequeña de instrucciones que puede ser manejada por el *Scheduler*. Un proceso puede tener uno o múltiples hilos que pueden compartir algunos recursos, sin embargo un hilo sólo puede estar ligado a un único proceso. Todo proceso tiene **al menos** un hilo.

Los hilos alivian la carga de trabajo asociada al proceso de *bifurcación* copiando sólo lo estrictamente necesario: La pila de tiempo de ejecución. Esta pila contiene los registros de activación para las funciones que están siendo llamadas. Una pila compartida podría provocar que al regresar de la llamada de una función, el control podría volver a un punto distinto del que la llamó.

### ¿Cuándo es conveniente usar hilos?

