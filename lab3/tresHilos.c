// Nombre       : tresHilos.c
// Objetivo     : Muestra el n-esimo multiplo de 3, 7 y 13; n-esimo fibonacci; la suma de los dos anteriores y el producto de los tres 
// Autor        : Alex Harvey Pfoccori Quispe y Marjorie Rodriguez Casas 
// FCracion     : 26/06/2022

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

// Parametros para la funcion que calcula la suma de resultado del numero multiplo y fibonacci
struct resultados {
    int multiplo; // Resultado del hilo que calcula el n-esimo multiplo de 3, 7 y 13
    int fibonacci; // Resultado del hilo que calcula el n-esimo terminoo de fibonacci
};

// Este modulo devuelve el N-esimo multiplo de 3, 7 y 13
void *nesimoMultiplo(void *arg) {
    int N = *((int *)arg);
    int cnt = 0;
    int candidato = 1;
    while (cnt < N) {
        if((candidato % 3 == 0) && (candidato % 7 == 0) && (candidato % 13 == 0)) {
            cnt++;
            candidato++;
        }
        else {
            candidato++;
        }
    }
    candidato = candidato - 1;

    return (void *)(intptr_t)candidato;
}
// Este modulo devuelve el N-esimo numero de fibonacci
void *nesimoFibonacci(void *arg) {
    int N = *((int *)arg);
    int a = 0;
    int b = 1;

    for( int i = 0; i < N; i++) {
        a += b;
        b = a - b;
    }

    return (void *)(intptr_t)b;
}
// Este modulo devuelve la suma de los dos resultados anteriores
void *sumaResultados(void *arg) {
    struct resultados *r = (struct resultados *)arg;
    int suma;

    suma = r->multiplo + r->fibonacci;
    return (void *)(intptr_t)suma;
}

// Modulo principal
int main () {
    
    //Variables
    pthread_t hiloMultiplo;
    pthread_t hiloFibonacci;
    pthread_t hiloSuma;
    struct resultados arg;
    int suma;
    int fibonacci;
    int multiplo;
    int numero;

    // Indicar proposito del programa
    printf("ESTE PROGRAMA CREA 3 HILOS PARA DIFERENTES PROPOSITOS \n");

    // Leer datos
    printf("Ingresel el valor de N: ");
    scanf("%d", &numero);
   
    // Crear los dos primeros hilos (modulo del multiplo y fibonacci)
    pthread_create(&hiloMultiplo, NULL, &nesimoMultiplo, &numero);
    pthread_join(hiloMultiplo, (void*)&multiplo);

    pthread_create(&hiloFibonacci, NULL, &nesimoFibonacci, &numero);
    pthread_join(hiloFibonacci, (void*)&fibonacci);

    // Almacenar los resultados de los dos hilos en la structura arg
    arg.multiplo = multiplo;
    arg.fibonacci = fibonacci;

    // Crear el tercer hilo (modulo de suma de resultados)
    pthread_create(&hiloSuma, NULL, &sumaResultados, &arg);
    pthread_join(hiloSuma, (void*)&suma);

    // Mostrar el resultado
    printf("\nEl %d-esimo numero multiplo de 3, 7 y 13 es %d.\n", numero, multiplo);
    printf("El %d-esimo termino de fibonacci es %d.\n", numero, fibonacci);
    printf("La suma de los resultados de los 2 primeros hilos es  %d.\n", suma);
    printf("La multiplicacion de los resultados de los 3 hilos es %d\n", multiplo * fibonacci * suma);

    // Salir
    return 0;
}
