#include <stdio.h>
#include <stdlib.h>

int fibonacci(int,int);


int fibonacci(int n, int prof)
{
    

    if(n<3){
        
        printf("\n Profundidad: %d",prof);
        printf(" a_n = %d n = %d\n",1,n);
        return 1;
    }

    int n_1, n_2;

    n_1 = fibonacci(n-1,prof+1);
    n_2 = fibonacci(n-2,prof+1);
    
    int a_n =n_1 + n_2;
    
    printf("\n Profundidad: %d",prof);
    printf(" a_n = %d n = %d  a_(n-1) = %d a_(n-2) = %d\n",a_n,n,n_1,n_2);
    return a_n;

}

int main(int argc, char *argv[]){

    int n = 3;
    if(argc>1){
        n = atoi(argv[1]);
    }
    fibonacci(n,1);

}