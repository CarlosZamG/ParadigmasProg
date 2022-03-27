#include <stdio.h>
#include <omp.h>

/*
Programa para entender los bucles for en OpenMP

-Comando para compilar:
gcc GaussOMP.c -o GaussOMP -fopenmp

-Comando para ejecutar:
./GaussOMP

-Salida:
Ingresa un número natural:1000
Sumatoria: 500500 == 500500
*/
int main(){

    int n, sum=0;

    printf("Ingresa un número natural:");
    scanf("%d", &n);

    /*
    Lo que hace la cláusula reduction es tomar el valor de una variable aportada por cada hilo y aplicar la operación
    indicada sobre esos datos para obtener un resultado
    */
    #pragma omp parallel for reduction(+ : sum)
    for(int i=0; i<= n; i++){
        sum = sum+i;
    }

    printf("Sumatoria: %d == %d\n",sum, (n*(n+1)/2));

}