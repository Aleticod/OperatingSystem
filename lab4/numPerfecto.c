// Nombre       : numPerfecto.c
// Proposito    : Muestra los N primeros numeros perfectos, el prgrama termina con la segunda senial
// Autor        : Alex Harvey Pfoccori Quispe
// FCreacion    : 11/07/2022
// FModif       :

// Librerias
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// Variables globales
bool bandera = false;
int cont = 0;

// Manejador del senial
void sigHandler() {
    cont++;
    switch (cont) {
        case 1:
            printf("Vuelva a interrumpir para terminar\n");
            break;
        case 2:
            bandera = true;
            break;
        default:
            break;
    }
}

// Modulo de la suma de divisores
int sumDivisores(int num) {
    // Variables
    int sum = 0;
    int limite = num / 2 + 1;

    for (int i = 1; i <= limite && i < num; i ++) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

// Modulo que verifica si es un numero perfecto
bool esPerfecto(int num) {
    if (sumDivisores(num) == num) {
        return true;
    }
    else {
        return false;
    }
}

// Modulo principal
int main () {
    // Varialbes
    int num = 1;
    
    // Proposito del programa
    printf("ESTE PROGRAMA IMPRIME LOS N PRIMEROS NUMEROS PERFECTOS Y TERMINA CON LA SEGUNDA SENIAL DEL TECLADO\n");

    // Registramos nuestro manejador de senial
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        exit(1);

    // Imprimimos los numeros perfectos
    while(!bandera) {
        if(esPerfecto(num)) {
            printf("Este es un numero perfecto %d\n", num);
            sleep(4);
        }
        num ++;
    }
    return 0;
}

