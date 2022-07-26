// Nombre	: alternancia.c
// Proposito	: Demuestra la alternancia de acceso a la seccion critica
// Autor	: Edwin Carrasco
// FCreacion	: 12/01/2021
// Ejecucion	: ./alternancia.exe
//
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;

// lo que hace cada hilo

void *competir(void *arg) {
	int idH = *((int*) arg);
	int tiempoTrabajo = rand() % 6 + 1;

	printf("Soy el hilo %d: Entrare a mi seccion critica por %d\n", idH, tiempoTrabajo);
	sleep(tiempoTrabajo);

	// Entrar a la region critica
	sem_wait(&mutex);
	printf("\n\t\t soy el hilo %d: EN MI SECCION CRITICA\n", idH);
	while (tiempoTrabajo > 0) {
		printf("\t\t\tSalg en %d\n", tiempoTrabajo);
		sleep(1);
		tiempoTrabajo--;
	}

	// Salir de la region critica
	printf("\n\t\tHilo %d: Saliendo ...\n", idH);
	sem_post(&mutex);

	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	// Variables
	int index = 0;
	int cnt = 0;
	int nroHilos = 0;

	// Leer argumentos del programa
	if(argc < 2) {
		fprintf(stderr, "Para ejecutar el programa escriba: \n alternancia nro_hilos\n");
		exit(0);
	}

	// Leer datos
	nroHilos = atoi(argv[1]);

	srand(time(0));

	// Indicar el proposito del programa
	printf("\nEste programa muestra la ejecución concurrente de %d hilos\n", nroHilos);
	printf("------------------------------------\n\n");

	// Procesar
	pthread_t arregloHilos[nroHilos];
	int idHilos[nroHilos];

	// Inicializacion de semaforos
	sem_init(&mutex, 0, 1);

	// Creacion de hilos
	while(index < nroHilos) {
		idHilos[index] = index;
		pthread_create(&(arregloHilos[index]), NULL, competir, &idHilos[index]);
		index++;
	}

	// Esperar hilos
	sleep(5);

	while(cnt < nroHilos) {
		pthread_join(arregloHilos[cnt], NULL);
		cnt++;
	}

	// salir
	return 0;
}


