#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fun(){
    int x=rand()%10, y=rand()%10;
    int* z=malloc(sizeof(int)); //recuerda reservar memoria
    printf("Esta hebra suma %d y %d\n", x, y);
    *z=x+y;
    pthread_exit((void*)z);   
}

void main(int argc, char** argv){
    if(argc!=2){
        printf("Error línea de comandos\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    int x=atoi(argv[1]), sum=0;
    int* aux=0; //x=número de hebras a implementar
    pthread_t hebra[x];
    for(int i=0; i<x; i++){
        pthread_create(&hebra[i], NULL, (void*)fun, NULL);
    }
    for(int i=0; i<x; i++){
        pthread_join(hebra[i], (void**)&aux);
        sum=sum+*aux;
    }

    printf("Todo esto en total %d\n", sum);

}
