// Nombre       : cuatroHilos.c
// Objetivo     : Muestra el promedio, maximo, minimo y la frecuancia de un array de elementos.
// Autor        : Alex Harvey Pfoccori Quispe y Marjorie Rodriguez Casas
// FCracion     : 26/06/2022

#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Este modulo devuelve el promedio de los elementos de un array 
void *promedio(void *arg) {
    int suma;
    int tamanio;
    float promedio;
    float* result = malloc(sizeof(int));
    tamanio = ((int *)arg)[0];
    suma = 0;
    for(int i = 1; i <= tamanio; i++){
        suma += ((int *)arg)[i];
    }
    promedio = ((float)suma) / ((float)tamanio);
    *result = promedio;
    return (void *) result;
}
// Este modulo devuelve el elemento mayor de un array
void *maximo(void *arg) {
    int tamanio;
    tamanio = ((int *)arg)[0];

    int max = ((int *)arg)[1];
    for(int i = 2; i <= tamanio; i++) {
        if(max < ((int *)arg)[i]){
            max = ((int *)arg)[i];
        }
    }
    return (void *)(intptr_t)max;
}
// Este modulo devuelve el elemento menor de un array
void *minimo(void *arg) {
    int tamanio;
    tamanio = ((int *)arg)[0];
    
    int min = ((int *)arg)[1];
    for(int i = 2; i <= tamanio; i++) {
        if(min > ((int *)arg)[i]) {
            min = ((int *)arg)[i];
        }
    }
    return (void *)(intptr_t)min;
}
// Este modulo devuelve la frecuencia de los elementos
void frecuencia(void *arg) {
    int tamanio;
    tamanio = ((int *)arg)[0];
    int elementos[tamanio];
    int frec[tamanio];
    int tam = 1;
    elementos[0] = ((int *)arg)[1];
    frec[0] = 1;
    for(int i = 2; i <=tamanio; i++) {
        int aux = 0;
        int j = 0;

        while(j < tam) {
            if(((int *)arg)[i] == elementos[j]) {
                frec[j] += 1;
                aux++;
            }
            j++;
        }
        if(aux == 0) {
            elementos[j] = ((int *)arg)[i];
            frec[j] = 1;
            tam ++;
        }
    }

    int j = 0;
    while(j < tam) {
        printf("El elemento es %d y su frecuencia es %d\n",elementos[j], frec[j]);
        j++;
    }
}

// Modulo principal
int main () {
    
    //Variables
    pthread_t hiloPromedio;
    pthread_t hiloMaximo;
    pthread_t hiloMinimo;
    pthread_t hiloFrecuencia;
    int minimoElem;
    int maximoElem;
    float *promedioElem;
    int tam;

    clock_t t0, t1;

    // Indicar proposito del programa
    printf("ESTE PROGRAMA CREA 4 HILOS PARA DIFERENTES PROPOSITOS \n");

    // Leer datos
    printf("Ingrese el numero de elementos del array N: ");
    scanf("%d", &tam);
    
    int datosArray[tam + 1];
    datosArray[0] = tam;

    for(int i = 1; i <= tam; i++) {
        printf("Ingresel elemento %d: ", i);
        scanf("%d",&datosArray[i]);
    }
    
    t0 = clock();
    // El hilo que calcula el promedio 
    pthread_create(&hiloPromedio, NULL, &promedio, &datosArray);
    pthread_join(hiloPromedio, (void*)&promedioElem);

    // El hilo que halla el maximo
    pthread_create(&hiloMaximo, NULL, &maximo, &datosArray);
    pthread_join(hiloMaximo, (void*)&maximoElem);

    // El hilo que halla el minimo
    pthread_create(&hiloMinimo, NULL, &minimo, &datosArray);
    pthread_join(hiloMinimo, (void*)&minimoElem);

    // El hilo que halla las frecuencias
    pthread_create(&hiloFrecuencia, NULL, (void*)frecuencia, &datosArray);
    pthread_join(hiloFrecuencia, NULL);

    t1 = clock();

    // Mostrar el resultado
    printf("\nEl valor promedio de los datos de array es  %f\n", *promedioElem);
    printf("El valor maximo del los datos del array es  %d\n", maximoElem);
    printf("El valor minimo del los datos del array es  %d\n", minimoElem);
    double time = (double)(t1 - t0)/CLOCKS_PER_SEC;
    printf("El tiempo demorado es %lf\n", time);
    // Salir
    return 0;
}
