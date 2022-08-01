// Nombre	: lectoresEscritores.c
// Proposito	: Muestra la solucion al problema de lectores escritores
// Autores	: A. Harvey Pfoccori Quispe y Marjorie Rodriguez Casas
// FCreac	: 26/07/2022
// Ejecución	: ./lectoresEscritores.exe

// Librerias
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
// Para este problema se asume que el tenedor de la derecha le pertence al filosofo 
// Variables globales
#define MAXLECTORES 10		// Numero de lectores maximos

int nroLec = 0;

// Definicion de funciones globales
 
sem_t mutex;
sem_t lector;
sem_t escritor;

// Modulo que verifica el estado de un filosofo
void escribir(int num) {
	// Condicion del filosofo es habriento y los de sus costados no estan cominedo
	if (num == 0) {
		// El escritor se pone a escribir
		
		printf("El escritor esta escribiendo\n");	
		sleep(3);

		sem_post(&escritor);
	}
}

// Tomar los tenedores de la mesa
int leer(int num) {
	
	sem_wait(&lector);	
	sem_wait(&mutex);
		// Cuando el filosofo quiere tomar los tenedores es por que tiene hambre
	num++;

	printf("Ingresa un lector numeor de lectore %d\n", num);

		// Poner en estado escribiendo en caso que no haya lectores
	escribir(num);

	sem_post(&mutex);
	sleep(2);
	
	// Esperar si no esta disponible para comer
	sem_wait(&escritor);
	sleep(3);
	return num;
}

// Poner los tenedores a la mesa

void dejarLeer(int num) {
	sem_wait(&mutex);

	// Poner en estado pensando
	num--;

	printf("El lector se retira\n");

	// Analiza a los filosfos de la izquierda y la derecha
	escribir(num);
	sem_post(&lector);
	sem_post(&mutex);
}

void *usuario(void *num) {
	while(1) {
		// Numero de filosofo
		int i = *(int*)num;
		sleep(3);
		// El filosofo toma los tenedores
		i = leer(i);
		sleep(3);
		// El filosofo pone los tenedores
		dejarLeer(i);
	}
}


int main() {
	// Declaramos los hilos
	pthread_t idusuario;
	
	sem_init(&lector, 0, 1);
	// Inicializamos los semaforos
	sem_init(&mutex, 0, 1);
	sem_init(&escritor, 0, MAXLECTORES);

	// Creamos los hilos para los 5 filosofos en estado pensando
	pthread_create(&idusuario, NULL, usuario, &nroLec);
	// Retornamos los hilos al proceso principal
	pthread_join(idusuario, NULL);
}
