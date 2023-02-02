/*Implemente un programa que cree un número N de hebras. Cada hebra creará 2 números
aleatorios flotantes (consulte Moodle para la generación de aleatorios) y guardará su suma en una
variable para ello, que será devuelta a la hebra principal o llamadora (la que invocó
pthread_create()).
La hebra principal ira recogiendo los valores devueltos por las N hebras y los ira sumando en
una variable no global cuyo resultado mostrará al final por pantalla. Para ver que los resultados
finales son los que usted espera, muestre los 2 números que va creando cada hebra y su suma, de
forma que pueda comparar esas sumas parciales con la suma final que realizará el main() o hebra
principal. Utilice macros definidas y comprobación de errores en sus programas (errno y
comprobación de valores devueltos en cada llamada, con sus posibles alternativas).*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* fun(){
    double x=drand48()*(10-1)+10, y=drand48()*(10-1)*10;
    float* z=malloc(sizeof(float)); //recuerda reservar memoria
    printf("Esta hebra suma %f y %f\n", x, y);
    *z=x+y;
    pthread_exit((void*)z);   
}

void main(int argc, char** argv){
    if(argc!=2){
        printf("Error línea de comandos\n");
        exit(EXIT_FAILURE);
    }
    srand48(time(NULL));
    int x=atoi(argv[1]);
    float sum=0;
    int* aux=0; //x=número de hebras a implementar
    pthread_t hebra[x];
    for(int i=0; i<x; i++){
        pthread_create(&hebra[i], NULL, (void*)fun, NULL);
    }
    for(int i=0; i<x; i++){
        pthread_join(hebra[i], (void**)&aux);
        sum=sum+*aux;
    }

    printf("Todo esto en total %f\n", sum);

}