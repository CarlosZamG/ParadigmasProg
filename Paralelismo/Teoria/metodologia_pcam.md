# Metodología PCAM

En los programas paralelos, el posible orden en que se ejecutan las instrucciones no es único. Sin un diseño cuidadoso y adecuado, pueden presentarse errores, como una mala actualización de los datos o una mala sincronización de las comunicaciones.

Por estas razones el diseño se convierte en una parte fundamnetal al momento de resolver un problema usando programación paralela. Nuestros principales objetivos al momento de diseñar son:

1. Exactitud.

2. Mejorar el rendimiento.

Sin embargo, transformar un programa secuencial en uno paralelo no necesariamente es el mejor camino, muchas veces ejecutar un programa en paralelo requiere de un algoritmo completamente diferente.

En 1995, Ian Foster popularizó el proceso **PCAM** (**P**articionamiento, **C**omunicación, **A**glomeración, **M**apeo) para el diseño de programas en paralelo. El proceso tiene los siguientes 4 pasos:

1. **Particionamiento**: El primer paso involucra dividir la computación en tantas piezas como sea posible. Este paso saca a al luz el paralelismo del problema (si es que existe). El particionamiento puede ser *orientado a funciones*, es decir, separar los diferentes pasos que se deben ejecutar (también llamado *descomposición funcional*) u *orientado a datos*, es decir, separar los datos según como serán procesados (también llamado *dominio* o *descomposición de datos*)
2. **Comunicación**: Idealmente nos gustaría que las tareas resultantes del **particionamiento** fueran totalmente independientes, sin embargo, usualmente esas tareas tienen interdependencias: Una necesita que la otra termine para poder empezar. Estas dependencias se deben a que necesitan pasarse datos, es decir, *comunicarse entre sí*. En este paso se determina el volumen de los datos que se deben comunicar. La combinación de los primeros dos pasos nos permite obtener el *grafo de dependencias de las tareas*, con nodos que representan las tareas y las aristas representan el volumen de comunicación.
3. **Aglomeración**: La comunicación obstaculiza el paralelismo. Una forma de reducirla es agrupar las tareas, cada grupo de tareas será asignado a un solo nodo, lo que reduce la comunicación entre esas tareas.
4. **Mapeo**: Para ejecutar la aplicación, los grupo de tareas del 3er paso debe ser asignados (*mapeados*) a un nodo. Los objetivos que buscamos conseguir en esta etapa son:

    - Balancear la carga de trabajo entre los nodos.
    - Reducir la comunicación: Los grupos que necesiten un costo intercambio de datos entre ellos deben ser mapeados al mismo nodo.

La forma en la que deben realizarse cada uno de los 4 pasos depende de la aplicación. De hecho, el paso **4** del mapeo es un problema NP-completo, es decir que su forma general no puede resolverse de manera óptima para grafos no triviales.