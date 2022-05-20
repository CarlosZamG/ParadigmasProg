#include <stdio.h>
#include <omp.h>

/*

- Coamndo para compilar:
gcc VariablesOMP.c -fopenmp -o VariablesOMP

-Comando para ejecutar:
./VariablesOMP

- Salida:

carlos@DESKTOP-TLLMVTS:~/ESFM/ParadigmasProg$ ./VariablesOMP

 Región paralela
Variable privada: 0    Variable compartida: 148
Variable privada: 1    Variable compartida: 149                     <= Aquí vemos que se pierde la Coherencia
Variable privada: 100    Variable compartida: 149

 Región paralela
Variable privada: 100    Variable compartida: 119
Variable privada: 101    Variable compartida: 120
Variable privada: 100    Variable compartida: 120
carlos@DESKTOP-TLLMVTS:~/ESFM/ParadigmasProg$ ./VariablesOMP

 Región paralela
Variable privada: 0    Variable compartida: 149
Variable privada: 1    Variable compartida: 150                     <= Aquí vemos que se pierde la Coherencia
Variable privada: 100    Variable compartida: 150

 Región paralela
Variable privada: 100    Variable compartida: 119
Variable privada: 101    Variable compartida: 120
Variable privada: 100    Variable compartida: 120
carlos@DESKTOP-TLLMVTS:~/ESFM/ParadigmasProg$


*/


int main(){

    int var_privada = 100;
    int var_compartida = 100;
    
    /*
    • shared: los datos en la región paralela son compartidos y accesibles por to-
    dos los threads simultáneamente.

    • private: los datos en la región paralela son privados para cada thread y cada
    uno tiene una copia de ellos sobre una variable temporal.
    
    • default: permite al programador definir cómo serán los datos dentro de la
    región paralela (shared, private, o none).
    */

    #pragma omp parallel default(none) private(var_privada) shared(var_compartida) num_threads(50)
    {
        #pragma omp master
        {
            printf("\n Región paralela \nVariable privada: %d    Variable compartida: %d",var_privada,var_compartida);

        }


        /*
        #pragma omp master
        
        Identifica un constructor que especifica un bloque de sentencias que será ejecutado
        por el master thread del grupo. Los otros threads en el grupo no ejecutan el bloque
        asociado.
        
        */

        var_privada++;
        var_compartida++;

        #pragma omp barrier
        /*
        #pragma omp barrier
        
        Sincroniza todos los threads de un grupo. Cuando un thread llega a la barrera,
        espera a que todos los demás threads en el grupo alcancen este punto. Después de
        que todos los threads encontraron la barrera, cada thread comienza a ejecutar las
        sentencias que se ubican después de la directiva de barrera.
        
        */


        #pragma omp single
        {
            printf("\nVariable privada: %d    Variable compartida: %d",var_privada,var_compartida);
        }

    }

    printf("\nVariable privada: %d    Variable compartida: %d\n",var_privada,var_compartida);

    var_privada = 100;
    var_compartida = 100;


    /*
    
    • firstprivate: Especifica que cada subproceso debe tener su propia instancia de una variable
     y que la variable debe inicializarse con el valor de la variable,
    ya que existe antes que la construcción paralela.
    */
    #pragma omp parallel default(none) firstprivate(var_privada) shared(var_compartida) num_threads(20)
    {
        #pragma omp master
        {
            printf("\n Región paralela \nVariable privada: %d    Variable compartida: %d",var_privada,var_compartida);

        }


        var_privada++;
        
        #pragma omp atomic
        var_compartida++;

        /*
        #pragma omp critical
        Esta directiva restringe la ejecución del bloque asociado a un único thread en un
        momento dado. Un thread espera al inicio de la sección crítica hasta que ningún
        otro thread se encuentre ejecutando código de la misma.
        
        #pragma omp atomic
            (expression)

        atomic: similar a critical, Las expresiones que se permiten
        incluyen a operadores binarios en asignaciones simples,
        como a++ o p[i] -= 5.

        */


        #pragma omp barrier

        #pragma omp single
        {
            printf("\nVariable privada: %d    Variable compartida: %d",var_privada,var_compartida);
        }

    }
    printf("\nVariable privada: %d    Variable compartida: %d\n",var_privada,var_compartida);


}
