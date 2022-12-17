#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


void* funcion_hebra(void* sum){
    float *sum_=(float*)sum;
    float num1, num2;
    srand(time(NULL));
   // sleep(1);
    num1=rand();
   // sleep(1);
    num2=rand();

    printf("Numeros aleatorios %f y %f\n", num1, num2);
    *sum_=*sum_+num1+num2;
    printf("Suma parcial %f\n", *sum_);
    pthread_exit(NULL);
}



int main(int argc, char** argv){
    if(argc!=2){
        printf("Error línea de argumentos");
        exit(EXIT_FAILURE);
    }
    int i, a=atoi(argv[1]);
    pthread_t hebra[a];
    float sum=0;
    for(i=0; i<a;i++){
        sleep(1);
        int a;
        if(a=pthread_create(&hebra[i], NULL, (void*) funcion_hebra, (void*)&sum)){
            printf("Error creacion hebra");
            exit(EXIT_FAILURE);
        }
        printf("Soy a %i", a);
    }
    for(i=0; i<a;i++){
        if(pthread_join(hebra[i], NULL)){
            printf("Error espera de hebra");
            exit(EXIT_FAILURE);
        }
    }
    printf("La suma total es %f\n", sum);

    return 0;
}

