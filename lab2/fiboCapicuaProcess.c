// Nombre		: sumProcessID.c
// Proposito	: Verifica si la suma de los PIDs del padre e hijo es primo o no.
// Autores		: Alex H. Pfoccori Quispe y Marjorie Rodriguez Casas
// FCreacion	: 05/06/2022
// FModif.		:

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <math.h>

int main() {
	// Variables
    int num;
	pid_t primerFork, segundoFork;

	// Indicar el proposito del programa
    puts("=== ESTE PROGRAMA CREA UN PROCESO HIJO Y UN PROCESO NIETO===");

	// Procesar
    // Ingresar un numero por consola
    printf("Ingrese un numero entero: ");    
    scanf("%i", &num);

    
	primerFork = fork(); // Creamos el proceso hijo

    // Evaluar el fork
	if(primerFork == 0) {

		// Este codigo se ejecuta solo en el proceso HIJO

        segundoFork = fork(); // Creamos el proceso nieto

        if(segundoFork == 0) {

            // Este codigo se ejecuta solo en el proceso NIETO
            
            // Este codigo verificca si un numero es par o no
            // procesar
            printf("\nESTE PROCESO SE ESTA EJECUTANDO EN EL PROCESO NIETO\n");
            if(num % 2 == 0)
                printf("El numero %i es par\n", num);
            else
                printf("El numer %i es impar \n", num);

            printf("Soy el proceso nieto y mi PID es %d. ", getpid());
            printf("el PID de mi padre es: %d\n\n", getppid());
            while(1);

        }
        else {

            // Este codigo se ejecuta solo en el proceso HIJO (PADRE DEL NIETO)
            // Codigo de verificacion si un numero es capicua
            // 121 -> true   123 -> false


            // Variables
            int aux[10];
            int cont = 0;
            int reverse =  0;
            int auxNum = num;
            
            // Procesar
            while(auxNum >= 10) {
                int mod = auxNum % 10;
                auxNum = auxNum / 10;
                aux[cont] = mod;
                cont = cont + 1;
            }
            aux[cont] = auxNum;
            printf("\nESTE PROCESO SE ESTA EJECUTANDO EN EL PROCESO HIJO\n");

            for(int i = cont; i >= 0; i--) {
                reverse = reverse + aux[cont - i] * pow(10, i);
            }

            if(num == reverse)
                printf("El numero es capicua y su reverso es %d\n", reverse);
            else
                printf("El numero no es capicua y su reverso es %d\n",  reverse);
            printf("Soy el proceso hijo y mi PID es %d. ", getpid());
            printf("el PID de mi padre es: %d\n\n", getppid());
            while(1);

        }
	}
	else {

        // Este codigo se ejecuta solo en el proceso PADRE
        

        // Codigo de termino n-simo de Fibonacci
        // 0, 1, 1, 2, 3, 5, ...

        // Variables
        unsigned long long a = 0;
        unsigned long long b = 1;

        for(int i = 0; i < num; i++) {

            a += b;
            b = a - b;
            //printf("%i \t\t %lld\n ", i + 1, b);
        }
        // Imprimir el termino n-esimo
        printf("\nESTE PROCESO SE ESTA EJECUTANDO EN EL PROCESO PADRE (ABUELO)\n");
        printf("El termino %i de la serie de fibonacci es: %lld\n", num, b);
		printf("Soy el proceso padre. Mi PID es: %d. ", getpid());
		printf("El PID  de mi padre es: %d\n\n", getppid());
		while(1);
	}

	// Salir
	return 0;
}
