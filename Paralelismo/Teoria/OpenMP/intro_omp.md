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

OpenMP hace una distinción entre *regiones* y *construcciones*: Una **construcción paralela** es la combinación de una directiva **pragma** de OpenMP con el bloque de instrucciones que le siguen, mientras que una **región paralela** es la sucesión dinámica de instrucciones producida durante la ejecución de una construcción paralela.

## Variables en OpenMP

Cuando una región paralela está en ejecución, todos los hilos ejecutan una copia del bloque de instrucciones, pero **¿Cómo se manejan las variables?** OpenMP tiene dos tipos elementales de memoria: *privada* y *compartida*.

1. **Variables privadas**: Cada hilo tiene su propia copia de la variable a la que sólo dicho hilo puede acceder, es decir, ningún otro hilo puede interferir, por lo que no hay riesgo de sufrir una **condición de carrera**, ya que un hilo nunca podrá cambiar el valor de la copia de una variable privada perteneciente a otro hilo.

2. **Variables compartidas**: Solo existe una instancia de la variable y puede ser leída o modificada por todos los hilos. Debemos tener cuidado al usar estas variables para evitar caer en una *condición de carrera*.

Veamos un ejemplo en código de los distintos tipos de variables en las construcciones de OpenMP.

```c
#include <stdio.h>
#include <omp.h>

int main(){

    int x = 1;
    int y = 1;
    
    int a = 0;

    x = 5;
    y = 5;

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
    
    #pragma omp parallel private(x) firstprivate(y) num_threads(4)
    {
        int id = omp_get_thread_num();
        int n1 = id*x;
        int n2 = id*y;
        //Por reglas de OpenMP, las variables id, n1 y n2 son privadas
        
        x = x+1;
        y = y+1;
        a = a + n2;
        printf("Hilo con ID: %3d | n1: %3d | n2: %3d | (x, y, a) = (%d, %d, %d)\n", id, n1, n2, x, y, a);
    }

    printf("(x, y, a) = (%d, %d, %d)\n", x, y, a);
}
```

Notemos que las variables `x`,`y` y `a` están declaradas afuera de la construcción paralela, pero al momento de escribir la construcción paralela, utilizamos las claúsulas `private()` para la variable `x` y `firstprivate()` para la variable `y`. Así estamos indicando que ambas variables son privadas, por lo que cada hilo tendrá su propia copia de dichas variables. La diferencia entre `private` y `firstprivate` es que el valor de las varibles privadas indicadas con `private` está indefinido dentro de la región paralela, mientras que con `firstprivate` nos aseguramos que se toma el valor de la variable afuera de la construcción para inicializar cada copia de los hilos en la región paralela.

Por defecto, todas las variables declaradas afuera de la construcción paralela son compartidas, así que la variable `a` es compartida. ya que no estamos utilizando una claúsula para ella.

Veamos lo que sucede al ejecutar un par de veces el programa:

```sh
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 10)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 15)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 30)
(x, y, a) = (5, 5, 30)
```

```sh
(x, y, a) = (5, 5, 0)
Hilo con ID:   0 | n1:   0 | n2:   0 | (x, y, a) = (1, 6, 0)
Hilo con ID:   2 | n1:   0 | n2:  10 | (x, y, a) = (1, 6, 10)
Hilo con ID:   1 | n1:   0 | n2:   5 | (x, y, a) = (1, 6, 5)
Hilo con ID:   3 | n1:   0 | n2:  15 | (x, y, a) = (1, 6, 25)
(x, y, a) = (5, 5, 25)
```

Podemos notar que cuando cada hilo ejecuta las líneas:
```c
x = x+1;
y = y+1;
```
Esto afecta a las copias que cada hilo tiene de las variables privadas `x` y `y`, así que dichas copias tienen el valor de `1` y `6` respectivamente en todos los hilos. 

Algo curioso que podemos observar en ambas ejecuciones es que al momento de salir de la región paralela, ambas variables `x` y `y` vuelven a tener el valor de `5`. Esto se debe a que en OpenMP las variables privadas tienen un tiempo de vida restringido, es decir, sólo existen dentro de la región paralela y están indefinidas al entrar y salir de la construcción. En caso de que haya una variable privada y una fuera de la construcción paralela que compartan el mismo nombre, dichas variables serán tratadas como si fueran diferentes a pesar de compartir nombre. Esto último es lo que sucede con las variables `x` y `y`.

Podemos ver que la variable `a` es compartida, ya que va guardando la suma acumulada de los valores de la varible `n2` de cada hilo, o al menos eso es lo que intenta, sin embargo sucede una condición de carrera.

## Directivas de sincronización

Para utilizar variables compartidas en un programa paralelo de forma correcta, necesitamos una forma de coordinar los cambios que se hacen a dichas variables. OpenMP provee directivas de sincronización que sirven para dos propósitos:**exclusión mutua** y **sincronización de eventos**.

- `critical`:
- `atomic`:
- `barrier`:
- `single`:
- `master`: