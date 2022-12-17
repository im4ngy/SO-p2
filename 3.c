#include<pthread.h>
#include <stdio.h>
#include<stdlib.h>

/*Implemente un programa que cree un vector de 10 elementos relleno con numeros aleatorios entre 1 y 9. No cree el vector de manera global, declarelo en el main().
Reparta ese vector entre 2 hebras p 5 hebras a partes iguales, según se indique por lunea de argmuentos un 2 o un 5, de forma que cada hebra sume la parte del vector 
que le corresponda y se lo devuelva al hilo principal el cual mostrará la suma de los resultados devuelto por las hebras creadas*/

struct dato
{
    int num_;
    int cont;
    int *dir_vector;
};

//noc

void* funcion_hebra(void* num_void){
    struct dato* num= (struct dato*)num_void;
    int a;
    if(num->cont==0){
        for(a=0; a<(num->num_); a++){
            srand(time(NULL));
        // sleep(1);
            (num->vec[a])=rand();
        }
    }
    if(num->cont==1){
        for(a=5; a<10; a++){
            srand(time(NULL));
        // sleep(1);
            (num->vec[a])=rand();
        }
    }    
    pthread_exit()
}


int main(int argc, char** argv){
    if(argc!=2){
        printf("Error línea de comandos");
        exit(EXIT_FAILURE);
    }
    struct dato datos;
    int i;
    datos.num_=atoi(argv[1]);
    if(datos.num_==2){
        pthread_t hebra[2];
        for(i=0; i<2;i++){
            datos.num_=5;
            if(pthread_create(&hebra[i], NULL, (void*)funcion_hebra, (void*)&datos)){
                printf("Error creación");
                exit(EXIT_FAILURE);
            }
            datos.cont++;
        }
        for(i=0; i<2;i++){
            if(pthread_join(hebra[i], NULL)){
                printf("Error join");
                exit(EXIT_FAILURE);
            }
        }        
    }
    //else if(num==5){

   // }
    else{
        printf("Error linea de comandos");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<10;i++){
        printf("El entero de la posición %i es %i\n", i, datos.vec[i]);
    }
    return 0;
}