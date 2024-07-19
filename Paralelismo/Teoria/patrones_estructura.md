# Patrones de estructura del programa

Podemos distinguir los patrones de estructura de un programa en paralelo en 2 grandes categorías:

1. **Globalmente paralelo, localmente secuencial**: La aplicación puede realizar varias tareas en simultáneo, con cada una de esas tareas ejecutándose de forma secuencial. Algunos patrones de esta categoría son:

    - *Un único programa, múltiples datos.*
    - *Múltiples programas, múltiples datos.*

2. **Globalmente secuencial, localmente paralelo**: La aplicación se ejecuta como un programa secuencial, con partes individuales que se ejecutan en paralelo cuando se necesita. Algunos patrones que caen en esta categoría son:
    
    - *Fork/Join.*
    - Paralelización de bucles.

![](./images/patrones_estructura.drawio.svg)

### Un único programa, múltiples datos.

En este patrón, todos los nodos ejecutan el mismo programa, sin embargo puede ser que apliquen las mismas operaciones a diferentes datos o sigan diferentes flujos de ejecución dentro del programa. La estructura típica de un programa que sigue este patrón incluye los siguientes pasos:

1. **Inicialización del programa**: Involucra desplegar el programa en la plataforma paralela e inicializar el sitema responsable de la comunicación y sincronización entre los hilos o procesos.

2. **Obtener un identificador único**: Al trabajar con procesos o hilos, los identificadores suelen numerarse empezando desde cero. En ciertos casos, el identificador puede ser un vector y no solo un escalar.

3. **Ejecutar el programa**: Se sigue el flujo de ejecución correspondiente al identificador.

4. **Finalizar el programa**: Cerrar los hilos y procesos y combinar los resultados parciales para obtener el resultado final.


### Múltiples programas, múltiples datos.

Este enfoque es lo suficientemente flexible para cubrir la mayoría de escenarios. Es muy útil cuando:

1. La plataforma de ejecución es hetorogénea, por lo que se necesita desplegar diferentes programas basados en la arquitectura de cada nodo.

2. La aplicación requiere tanta memeoria que el espacio obliga a reducir la lógica del programa cargado a cada nodo

El patrón de *múltiples programas, múltiples datos* cubre estos casos permitiendo diferentes ejecutables, que serán unidos en una aplicación. Cada nodo es libre de ejecutar su propio programa y procesar sus propios datos, sin embargo la secuencia de pasos de la sección previa aún deben ser seguidos.

Un ejemplo especial de este patrón es CUDA, donde el programa se compila en un solo archivo, pero en realidad contiene dos binarios: Uno para la CPU y otro para la GPU.

### *Fork/Join*.

El patrón *Fork/Join* (puede ser traducido al español como *Bifurcar/Unir*) es utilizado cuando el algoritmo paralelo requiere la creación (bifurcación) dinámica de tareas en tiempo de ejecución. Estas tareas hijas (hilos o procesos)  deben terminar (unirse) antes de que el proceso padre pueda reanudar su ejecución.

Las tareas generadas pueden ejecutarse generando nuevos hilos o procesos, o utilizando un grupo de hilos existente (un *pool*) para gestionarlas. Este último enfoque minimiza la sobrecarga asociada a la creación de hilos y permite gestionar de forma óptima los recursos de procesamiento de una máquina.

### Paralelización de bucles.

La migración del software hacia arquitecturas multinúcleo es una tarea monumental. Así que patrón de paraleliación de bucles aborda este problema permitiendo al desarrollador portar el código secuencial existente paralelizando los bucles.

Este patrón es especialmente importante para la plataforma OpenMP, donde los bucles se paralelizan semiautomáticamente con la ayuda del programador: este último debe proporcionar pistas en forma de directivas para ayudar en esta tarea.

El paralelismo de bucles es un patrón con una utilidad limitada en el sentido de que no promueve el diseño de una nueva solución paralela a un problema, sino que se centra en la evolución de una solución secuencial a una paralela.

Esta es también una de las razones por las que los beneficios de rendimiento suelen ser pequeños, pero al menos el esfuerzo de desarrollo implicado es igualmente mínimo.