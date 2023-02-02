/*Implemente un programa que cuente las líneas de los ficheros de texto que se le pasen como
parámetros y al final muestre el número de líneas totales (contando las de todos los ficheros juntos).
Ejemplo de llamada: ./a.out fichero1 fichero2 fichero3
Debe crear un hilo por cada fichero indicado por linea de argumentos, de forma que todos los
ficheros se procesen de manera paralela, uno por cada hilo.*/

//recuerda se lee con fgets y en 1 linea hay 128 caracteres

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fun_hebra(void* fun_){
    printf("Hola\n");
    char *fun=(char*)fun_;
    printf("%s", fun);
    char s[128];
    int* resul=malloc(sizeof(int));
    char* nf=fun;
    FILE* fich=fopen(nf, "r");
    if(fich==NULL){
        printf("Fichero vacío");
        pthread_exit(NULL);
    }
    int cont=0;
    printf("Hola\n");
    while(fgets(s, 128, fich)){
        
    }
    printf("Hola\n");
    fclose(fich);
    pthread_exit((void*)resul);
}

void main(int argc, char** argv){
    if(argc<2){
        printf("Error linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
    int* aux;
    int total=0;
    pthread_t hebras[argc-1];
    for(int i=0; i<argc; i++){
        if(pthread_create(&hebras[i], NULL, (void*)fun_hebra, (void*)&argv[i+1])){
            fprintf(stderr, "error\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i<argc; i++){
        pthread_join(hebras[i], (void**)aux);
        printf("El archivo %d tiene %d lineas\n", i+1, *aux);
        total=total+*aux;
    }

    printf("En total hay %d lineas\n", total);
}