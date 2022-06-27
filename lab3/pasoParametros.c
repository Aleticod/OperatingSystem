// Nombre       : pasoParametros.c
// Objetivo     : Crea hilos que imprimen caracteres aleatorios
// Autor        : Edwin Carrasco
// FCreacion    : 06/12/2007

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Parametros para funcion de impresion

struct parametros  {
    char caracter; // El caracter a imprimir
    int cuenta; // El numero de veces a imprimir
};

// Imprime un caracter, segun se especifique en Argumentos
// Que es un apuntador a la estructura de parametros

void *imprimir (void *argumentos) {
    // Hace un cast sobre el apuntador al tipo adecuado
    struct parametros *p = (struct parametros *)argumentos;
    int i;

    for(i = 0; i < p->cuenta; i++) {
        printf("%c",p->caracter);
    }
    printf("\n");

    // Salir del hilo
    pthread_exit(0);
}

int main() {
    // Variables
    struct parametros argHilos;
    int nroHilos;
    int cnt;
    srandom(time(0));

    // Indicar proposito de programa
    printf("ESTE PROGRAMA CREA N HILOS QUE IMPRIMEN CARACTERES ALEATORIOS\n");

    // Leer datos
    printf("Ingrese N: ");
    scanf("%i", &nroHilos);

    // Procesar
    pthread_t arregloHilos[nroHilos];

    for(cnt = 0; cnt < nroHilos; cnt ++) {
        argHilos.caracter = (char)(random()%(26) + 65);
        argHilos.cuenta = (int)((random()%100) + 1);
        printf("El hilo %d imprimira %c %d veces \n", cnt, argHilos.caracter, argHilos.cuenta);
        pthread_create(&(arregloHilos[cnt]), NULL, &imprimir, &argHilos);
        pthread_join(arregloHilos[cnt], NULL);
    }

    // Salir
    return 0;
}
