//Nombre            : apuntadores.c
//Proposito         : Muestra el contenido de una variable de manera indiercta
//Autor             : Alex Harvey
//FCreacion         : 
//FModif            :

#include <stdio.h>

int main () {
    //variables
    int var = 300;
    int *ptr;       // Apuntador a una variable entera
    ptr = &var;     // Inicializacion de puntero, ptr almacena la direccion de var

    // Mostrar el valor de "var" directa e indirecta
    printf("\nAcceso Directo: var = %d", var);
    printf("\nAcceso Indirecto (mediante su apuntdor): var = %d", *ptr);
    // Mostrar la direccion de memoria de "var" de dos maneras
    printf("\nDireccion de var mediante el valor almacenado en su apuntador: %d", ptr);
    printf("\n");
}

