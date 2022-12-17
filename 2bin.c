#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

struct param{
    char*fich;
    int cont;
};

void* funcion_hebra_contar_lineas(void* fun_){
    struct param *fun=(struct param*)fun_;
    char s[128];
    char* nf=fun->fich;
    FILE* fich=fopen(nf, "r");
    if(fich==NULL){
        printf("Fichero vacío");
        pthread_exit(NULL);
    }
    int cont=0;
    while(fgets(s, 128, fich)){
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
    int i,suma=0, cont=0, n=(argc-1);
    pthread_t hebra[n];
    struct param fun[n];
    fun[n].cont=0;
    for (i=0;i<argc-1; i++){
        fun[i].fich=argv[i+1];
        if(pthread_create(&hebra[i], NULL, (void*) funcion_hebra_contar_lineas, (void*)&fun[i])){
            printf("Error creación");
            exit(EXIT_FAILURE);
        }
    }
    
    for (i=0;i<argc-1; i++){
        if(pthread_join(hebra[i], NULL)){
            printf("Error join");
            exit(EXIT_FAILURE);
        }
        suma=suma+fun[i].cont;
    }
    printf("%i\n", suma);
    return 0;
}