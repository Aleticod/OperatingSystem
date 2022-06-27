// Nombre       : hallarPrimo.c
// Objetivo     : Muestra el N-esimo numero primo calculado por un hilo
// Autor        : Edwin Carrasco
// FCracion     : 06/12/2007

#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h> // intptr_t

// Este modulo devuelve el N-esimo numero primo

void *calcula_primo(void *arg) {
    int N = *((int *)arg);
    int divisor = 2;
    int cnt = 0;
    bool esPrimo = false;
    int nroEvaluado = 1;
    int candidato = 0;

    printf("\t Hilo comenzando calculo del N-esimo numero primo ... \n");

    while ( cnt < N ) {
        esPrimo =  true;
        divisor = 2;
        while( (esPrimo == true) && (divisor <= sqrt(nroEvaluado))) {
            if (( nroEvaluado % divisor == 0))
                esPrimo = false;
            else
                divisor ++;
        }

        if ( esPrimo == true) {
            cnt ++;
            candidato = nroEvaluado;
        }

        nroEvaluado ++;
    }
    return (void *)(intptr_t)candidato;
}


int main () {
    
    //Variables
    pthread_t hilo;
    int primo;
    int enesimoPrimo;

    // Indicar proposito del programa
    printf("Este programa determina el N-esimo primo \n");

    // Leer datos
    printf("Ingresel el valor de N: ");
    scanf("%d", &enesimoPrimo);
    
    // Crear Hilo
    pthread_create(&hilo, NULL, &calcula_primo, &enesimoPrimo);

    // Mostrar actividad
    printf("Proceso principal esperando ... \n");

    // Esperar que termine el hilo y tomar el resutlado.
    pthread_join(hilo, (void*)&primo);

    // Mostrar el resultado
    printf("El %d-esimo numero primo es %d.\n", enesimoPrimo, primo);

    // Salir
    return 0;
}
