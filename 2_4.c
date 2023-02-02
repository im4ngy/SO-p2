#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int global=0;

void* fun(){
    for(int i=0; i<10000; i++){
        global++;
    }
    int* x=malloc(sizeof(int));
    *x=global;
    pthread_exit((void*)x);
}

void main(){

    pthread_t hebras[2];
    int sum=0;
    int* aux;
    for(int i=0; i<2; i++){
        pthread_create(&hebras[i], NULL, (void*)fun, NULL);
    }
    for(int i=0; i<2; i++){
        pthread_join(hebras[i], (void**)&aux);
        sum=sum+(*aux);
    }
    printf("El valor es %d y del otro modo no es el mismo: %d\n", global, sum);
}