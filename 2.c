#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

struct param{
    char*fich;
    int cont;
};

void* funcion_hebra_contar_lineas(void* fun_){
    struct param *fun=(struct param*)fun_;
    char* nf=fun->fich;
    FILE* fich=fopen(nf, "r");
    if(fich==NULL){
        printf("Fichero vacío");
        pthread_exit(NULL);
    }
    int cont=0, num;
    while(fscanf(fich, "%i", &num)==1){
        (fun->cont)++;
    }
    fclose(fich);
    pthread_exit(NULL);
}

int main(int argc, char** argv){
    if(argc<=1){
        printf("Error linea de argumentos");
        exit(EXIT_FAILURE);
    }
    int i, cont=0, n=(argc-1);
    pthread_t hebra[n];
    struct param fun;
    fun.cont=0;
    for (i=1;i<argc; i++){
        fun.fich=argv[i];
        if(pthread_create(&hebra[i-1], NULL, (void*) funcion_hebra_contar_lineas, (void*)&fun)){
            printf("Error creación");
            exit(EXIT_FAILURE);
        }
    }
    for (i=1;i<argc; i++){
        if(pthread_join(hebra[i-1], NULL)){
            printf("Error join");
            exit(EXIT_FAILURE);
        }
    }
    printf("%i", fun.cont);
    return 0;
}