// Nombre           : Muestra las direcciones y contenido de los elementos de arreglos de tipos short, int y double
// Proposito        : Muestra las direcciones y contenido de los elementos de arreglos de tipos short, int y double.
// Autor            : Alex Harvey
// FCreacion        : 
// FModif           :

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
    // Variables
    int i;
    short arreglo_s[10];
    double arreglo_d[10];
    int arreglo_i[10];

    // Indicar proposito del programa
    printf("ESTE PROGRAMA MUESTRA LAS DIRECCIONES Y CONTENIDO DE LOS ELEMENTOS\nDE TRES TIPOS SHORT, INT DOUBLE\n");

    // Inicializar datos aleatorios
    for(i = 0; i < 10; i++) {
    arreglo_s[i] = (short)(1 + rand()%(999));
    arreglo_i[i] = (int)(1 + rand()%(99999));
    arreglo_d[i] = (double)((1 + rand()%(999999999 - 1))*0.1f);
    }

    // Mostrar salida
    printf("\n==========================");
    printf("===========================\n");
    printf("\t\tSHORT\t\tINT\t\tDOUBLE\n");
    printf("\t   Direc: cont  | Direc:  cont  | Direc:  cont");
    printf("\n=========================");
    printf("==========================\n");

    // Imprimir la direccion de cada elemento de cada arreglo
    for(i = 0; i < 10; i ++) {
    printf("\nElemento %d| %d:%4d | %d:%6d | %:%8.2f", i, &arreglo_s[i], arreglo_s[i], &arreglo_i[i],arreglo_i[i], &arreglo_d[i], arreglo_d[i]);
    }

    printf("\n==============================");
    printf("===============================\n");
    printf("\nEsto es una prueba desde vim");
    // Salir
    return 0;
}
