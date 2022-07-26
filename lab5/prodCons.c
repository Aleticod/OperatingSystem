// Nombre	: prodCons.c
// Proposito	: Resuelve el problema del Productor/Consumidor
// Autor	: Edwin Carrasco
// FCreacion	: 26/08/2004
//
#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define TAMBUF 5

int buffer[TAMBUF];

sem_t lleno;	// semaforo que controla si el buffer esta lleno
sem_t vacio;	// semaforo que controla si el buffer esta vacio
sem_t mutex;	// semaforo que garantiza la exclucion mutua

// Productor
void *productor(void *arg) {
	// Variables
	int j;
	int indicep = 0;
	int producido;

	while(1) {
		// producir un elemento
		producido = (rand() % 26) + 65;

		sem_wait(&vacio);
		sem_wait(&mutex);

		// agregar elemento al buffer
		buffer[indicep] = producido;

		// actualizar indecep
		indicep = (indicep + 1) % TAMBUF;

		// Mostrar elemento producido
		printf("Agregando: %c\n", producido);

		// Mostrar el buffer
		for( j = 0; j < TAMBUF; j++)
			printf("%c\t", buffer[j]);

		printf("\n\n");

		sem_post(&mutex);
		sem_post(&lleno);
		sleep(3);
	}

	pthread_exit(0);
}

// Consumidor
void *consumidor(void *arg) {
	// Variables
	int indicec = 0;
	int consumido;
	int asterisco = 42;

	while(1) {
		sleep(4);

		sem_wait(&lleno);
		sem_wait(&mutex);

		// Sacar un elemento del buffer
		consumido = buffer[indicec];

		// Marcar posición consumida
		buffer[indicec] = asterisco;

		// Actualizar indecec
		indicec = (indicec + 1) % TAMBUF;

		// Mostrar elemento consumido
		printf("\t\t\t\t\tSacando: %c\n", consumido);

		sem_post(&mutex);
		sem_post(&vacio);
	}

	pthread_exit(0);
}

int main() {
	// Declaracion de hilos
	pthread_t idprod;
	pthread_t idcons;

	srand(time(0));

	sem_init(&lleno, 0, 0);

	sem_init(&vacio, 0, TAMBUF);

	sem_init(&mutex, 0, 1);

	printf("\n tamaño del buffere %d\n\n", TAMBUF);
	printf("Para terminar la simulacion presiona CTRL + C\n\n");

	pthread_create (&idprod, NULL, productor, NULL);
	pthread_create (&idcons, NULL, consumidor, NULL);
	
	pthread_join(idprod, NULL);
	pthread_join(idcons, NULL);

	return 0;
}	
