/*Implemente un programa que cree un vector de 10 elementos relleno con números aleatorios
entre 1 y 9. No cree el vector de manera global, declárelo en el main(). Reparta ese vector entre 2
hebras o 5 hebras a partes iguales, según se indique por linea de argumentos un 2 o un 5, de forma
que cada hebra sume la parte del vector que le corresponda y se lo devuelva al hilo principal, el cual
mostrará la suma de los resultados devuelto por las hebras creadas.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct param{
    int id;
    int vec_global[10];
};

void* fun2(void* aux_){
    struct param *aux=(struct param*) aux_;
    int* val=malloc(sizeof(int));
    int x=0;
    if(aux->id==0){
        for(int i=0; i<5; i++){
            x=x+aux->vec_global[i];
        }
    }
    else{
        for(int i=6; i<11; i++){
            x=x+aux->vec_global[i];
        }
    }
    *val=x;
    pthread_exit((void*)val);
}
void* fun5(){

}

void main(int argc, char** argv){
    if(argc!=2){
        printf("Error linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
    //vec aleatorio
    srand(time(NULL));
    int vec[10], suma;
    int* resultado;
    for (int i=0; i<10; i++){
        vec[i]=rand()%9;
    }
    printf("El vector contiene: ");
    for (int i=0; i<10; i++){
        printf("%d ", vec[i]);
    }
    pthread_t hebra[5];
    struct param aux[5];
    if(atoi(argv[1])==2){
        for(int i=0; i<2; i++){
            aux[i].id=i;
            for(int j=0; j<10; j++){
                aux[i].vec_global[j]=vec[j];
            }
            if(!pthread_create(&hebra[i], NULL, (void*)fun2, (void*)&aux[i])){
            fprintf(stderr, "error\n");
            exit(EXIT_FAILURE);
        }
        }
        for(int i=0; i<2;i++){
            pthread_join(hebra[i], (void**)&resultado);
            printf("\nEl resultado de la hebra %d es %d\n", i, *resultado);
        }
    }
    else if(atoi(argv[1])==5){
        for(int i=0; i<5; i++){
            pthread_create(&hebra[i], NULL, (void*)fun5, NULL);
        }
        for(int i=0; i<5;i++){
            pthread_join(hebra[i], NULL);
        }
    }
    else{
        printf("Error linea de argumentos\n");
        exit(EXIT_FAILURE);
    }
}