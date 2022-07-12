// Nombre       : numAmigos.c
// Proposito    : Imprime los N numeros amigos y la hora del sistema con una senial del teclado
// Autor        : Alex Harvey Pfoccori Quispe
// FCreacion    : 11/07/2022
// FModif       :

// Librerias
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

// Manejador de seniales
static void sigHandler(int sig) {
   
   // Variables
   time_t now;
    
    // Tiempo actual del sistema
    time(&now);

    printf("Fecha y hora del sistema %s",ctime(&now));

}

// Suma de divisores
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

// Verificacion si dos numeros son amigos
bool sonAmigos(int numA, int numB) {
    // Variables
    int sumDivA, sumDivB;

    sumDivA = sumDivisores(numA);
    sumDivB = sumDivisores(numB);

    if (numA == sumDivB && numB == sumDivA) {
        return true;
    }
    else {
        return false;
    }
}

// Modulo principal
int main () {
    // Variables
    int num = 1;
    int sumDiv;
    
    printf("ESTE PROGRAMA IMPRIME LOS N PRIMEROS NUMEROS AMIGOS Y MONITOREA UNA SENIAL DE TECLADO\n");

    // Registramos nuestro manejador de senial
    if (signal(SIGINT, sigHandler) == SIG_ERR)
        exit(1);

    // Imprmir los numeros amigos
    while(1) {
        sumDiv = sumDivisores(num);
        if(sumDiv > num) {
            if(sonAmigos(num, sumDiv)) {
                printf("Numeros amigos %d y %d\n", num, sumDiv);
                sleep(3);
           }
        }
        num ++;
    }
    return 0;
}

