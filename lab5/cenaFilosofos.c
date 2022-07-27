// Nombre	: cenaFilosofos.c
// Proposito	: Muestra la solucion al problema de la cena de filosofos
// Autores	: A. Harvey Pfoccori Quispe y Marjorie Rodriguez Casas
// FCreac	: 26/07/2022
// Ejecución	: ./cenaFilosofos.exe

// Librerias
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
// Para este problema se asume que el tenedor de la derecha le pertence al filosofo 
// Variables globales
#define N 5		// Numero de filosofos y tenedores
#define PENSANDO 2
#define HAMBRIENTO 1
#define COMIENDO 0
// Definicion de funciones globales
#define IZQUIERDA (filnum + 4) % N
#define DERECHA (filnum + 1) % N
 
int estado[N];
int fil[N] = { 0, 1, 2, 3, 4 };
 
sem_t mutex;
sem_t S[N];

// Modulo que verifica el estado de un filosofo
void test(int filnum) {
	// Condicion del filosofo es habriento y los de sus costados no estan cominedo
	if (estado[filnum] == HAMBRIENTO && estado[IZQUIERDA] != COMIENDO && estado[DERECHA] != COMIENDO) {
		// El filosofo se pone a comer
		estado[filnum] = COMIENDO;
		        
		printf("El filosofo %d toma los tenedores %d y %d\n", filnum + 1, IZQUIERDA + 1, filnum + 1);
                printf("El filosofo %d esta comiendo\n", filnum + 1);
		sleep(3);

		sem_post(&S[filnum]);
	}
}

// Tomar los tenedores de la mesa
void tomarTenedor(int filnum) {
	sem_wait(&mutex);
	// Cuando el filosofo quiere tomar los tenedores es por que tiene hambre
	estado[filnum] = HAMBRIENTO;

	printf("El filosofo %d tiene hambre \n", filnum + 1);

	// Poner en estado comiendo si sus vecinos no estan comiendo
	test(filnum);

	sem_post(&mutex);

	// Esperar si no esta disponible para comer
	sem_wait(&S[filnum]);

	sleep(3);
}

// Poner los tenedores a la mesa

void ponerTenedor(int filnum) {
	sem_wait(&mutex);

	// Poner en estado pensando
	estado[filnum] = PENSANDO;

	printf("El filosofo %d pone los tenedores %d y %d\n", filnum + 1, IZQUIERDA + 1, filnum + 1);

	printf("El filosofo %d esta pensando \n", filnum + 1);


	// Analiza a los filosfos de la izquierda y la derecha
	test(IZQUIERDA);
	test(DERECHA);

	sem_post(&mutex);
}

void *filosofo(void *num) {
	while(1) {
		// Numero de filosofo
		int *i = num;
		sleep(3);
		// El filosofo toma los tenedores
		tomarTenedor(*i);
		sleep(3);}
		// El filosofo pone los tenedores
		ponerTenedor(*i);
	}
}


int main() {
	int i;
	// Declaramos los hilos
	pthread_t thread_id[N];
	// Inicializamos los semaforos
	sem_init(&mutex, 0, 1);
	for (i = 0; i < N; i++)
		sem_init(&S[i], 0, 0);

	// Creamos los hilos para los 5 filosofos en estado pensando
	for(i = 0; i < N ; i++)
		pthread_create(&thread_id[i], NULL, filosofo, &fil[i]);
		printf("El filosofo %d esta penssando\n", i + 1);
	}
	// Retornamos los hilos al proceso principal
	for (i = 0; i < N; i++)
		pthread_join(thread_id[i], NULL);
}
