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

- **Tareas en segundo plano**: Las aplicaciones interactivas pueden utilizar hilos para realizar tareas en segundo plano, es decir, tareas que no requieren la interacción del usuario y, al mismo tiempo, seguir respondiendo a sus peticiones.

- **Procesamiento asíncrono**: Enviar una solicitud a un servidor a través de una red implica una latencia considerable. Al generar un subproceso para gestionar la transacción con el servidor de forma asíncrona (es decir, sin esperar la respuesta), una aplicación puede seguir realizando un trabajo útil, lo que mejora el rendimiento y la utilización de los recursos.

- **Videojuegos**: Una característica típica de los juegos es la necesidad de realizar concurrentemente una gran colección de tareas periódicas. Estas tareas incluyen el redibujado de la pantalla, la reproducción del sonido, la detección de la entrada del usuario y la creación de estrategias. Estas tareas no tienen por qué ejecutarse con la misma frecuencia que el resto, y ponerlas dentro del mismo bucle y asegurarse de que pueden ejecutarse a la velocidad de la recarga de la pantalla es un requisito extremo que sólo puede satisfacerse con una mayor complejidad del programa. Asignar las distintas tareas a diferentes hilos permite obtener un código mucho mejor estructurado que, además, es más fácil de mantener.

Veamos un ejemplo de cómo usar hilos en Linux con **pThreads**, una librería para manejar hilos:

El siguiente código puede ser encontrado en `/Paralelismo/nuevo/restaurant.c`, en este podemos pensar un hilo como un chef de un restaurante cuya tarea es cocinar platillos. Cada hilo es un chef que cocina independientemente de lo que estén realizando los otros chefs.

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
```

Con la siguiente salida:

```sh

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
```
Notemos que lo primero que tenemos que hacer es incluir el archivo de cabecera `pthread.h`.

Después de eso, cuando creamos un hilo con **pThreads**, este ejecuta una función, que en este caso es la función `work()`. Luego declaramos una variable del tipo `pthread_t` que usaremos con la función `pthread_create()`. Esta función tiene la siguiente estructura:

```c
int pthread_create(pthread_t *newthread, pthread_attr_t *attr, void *(*function)(void *), void *arg)
```

Devuelve un entero y recibe cuatro argumentos:

1. Un apuntador a una variable de tipo `pthread_t`.
2. La siguiente variable son atributos para configurar cosas que podemos hacer con los hilos.
3. La función que el hilo va a ejecutar.
4. Los argumentos que se le deben pasar a la función.

Por último, usualmente queremos esperar a que los hilos terminen de ejecutar su tarea. Para eso utilizaremos la función `pthread_join()` que tiene la siguiente estructura:

```c
int pthread_join(pthread_t thread, void **return)
```
Devuelve un entero y recibe dos argumentos:

1. Una variable de tipo `pthread_t`.
2. Un puntero para obtener lo que retorna la función que el hilo ejecutó.

## Diferencias entre hilos y procesos.

La primera diferencia es que podemos tener múltiples hilos dentro de un proceso, pero un hilo no puede pertenecer a múltiples procesos. Otra diferencia importante es que cuando trabajamos con procesos, al momento de bifurcar con la función `fork()`, duplicamos todas las variables del proceso *padre* en el proceso *hijo*, por lo que podemos manejar las varibles de forma independiente entre procesos. Mientras que al trabajar con hilos tenemos las variables en un espacio de memoria compartido, por lo que todos los hilos pueden acceder a todas las variables. Veamos ejemplos de esto:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

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
```

La función `wait()` bloquea la ejecución del proceso *padre* hasta que el proceso *hijo* termine. Considerando esto **¿cuál será el valor de `number` al momento de imprimirlo en el proceso *padre*?** Aunque podríamos pensar que tendrá un valor de `100` ya que se realizan dos incrementos de `50`, la realidad es que como estamos **bifurcando procesos**, cada uno tiene su respectiva copia, por lo que la salida es la siguiente:

```sh
Hola desde el proceso hijo (el proceso nuevo), el valor de number es: 50
Hola desde el proceso padre (el proceso original), el valor de number es: 50
```

Ahora veamos un ejemplo similar pero con hilos:

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
```

Salida:
```sh
El valor de number es: 50
El valor de number es: 100
```

Lo que sucede es que la variable `number` es compartida por los dos hilos, así que el incremento que estamos haciendo en `work1()` también es considerado por el otro hilo, cosa que se refleja al imprimir en `work2()`. 

Podemos ampliar nuestro ejemplo en `restaurant.c` para también trabajar con procesos. Si un hilo es un cocinero, ¿Qué es un proceso en esta analogía? Pues un proceso lo podemos ver como un restaurante, es decir, al momento de trabajar con múltiples procesos, podemos pensarlos como múltiples restaurantes, cada uno con sus propios cocineros (hilos):

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

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
```

Salida:
```sh

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

```

Todos estos códigos se encuentran en la carpeta `Paralelismo/nuevo`