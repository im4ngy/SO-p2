/*Implemente un programa que cree dos hebras y cada una incremente 10000 veces en un bucle
una variable global (recuerde que la variable global, al estar en el mismo espacio de memoria para
las dos hebras, es compartida, y que su uso es “peligroso”). Imprima al final del programa principal
el valor de la variable (en cada ejecución posiblemente obtenga un valor diferente a 20000 –
problema de concurrencia –). Intente razonar el resultado, el cual le servirá como concepto
introductorio de la siguiente práctica de la asignatura.*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
int n=0;
void* funcion_hebra(void* n_){
    int* n= (int*) n_;
    int i;
    for(i=0;i<1000;i++){
     (*n)++;
    }
};

int main(){
    pthread_t hebra[2];
    int i;
    for(i=0; i<2; i++){
        if (pthread_create(&hebra[i], NULL, (void*)funcion_hebra, (void*) &n)){
            printf("Error creación");
            exit(EXIT_FAILURE);
        }
    }
    for(i=0; i<2; i++){
        if(pthread_join(hebra[i], NULL)){
            printf("Error join");
            exit(EXIT_FAILURE);
        }
    }
    printf("El entero total es %i\n", n);
    return 0;
}