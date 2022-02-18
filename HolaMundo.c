#include <stdio.h>
#include <omp.h>
#include <unistd.h>

int main(){

    int tid;

    #pragma omp parallel private(tid) num_threads(2)
    {

        tid = omp_get_thread_num();
        if(tid==0) sleep(tid+1);
        printf("Hola Mundo Paralelo tid: %d \n",tid);

    }
    


}