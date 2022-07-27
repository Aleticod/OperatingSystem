




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5
#define IZQUIERDA(x) ((x) != 0 ? (x) - 1 : (N - 1))
#define DERECHA(x) (((x) + 1) % N)

void pensar (int i);
void comer (int i);
void tomarTenedor (int i);
void ponerTenedor (int i);
void comprobar (int i);
void *Filosofo(void*);

typedef enum {
	PENSANDO, HAMBRIENTO, COMIENDO
} status;


status estado[N];

sem_t mutex;

sem_t s[N];

int main() {
	int v[N], i;

	sem_init(&mutex, 0, 1);

	pthread_t filosofo[N];

	for(i = 0; i < N; i++) {
		sem_init(&s[i], 0, 0);
		estado[i] = PENSANDO;
	}

	for(i = 0; i < N; i++) {
		v[i] = i;
		pthread_create(&filosofo[i], NULL, Filosofo, (void*)&v[i]);
	}

	for(i = 0; i < N; i++) {
		pthread_join(filosofo[i], NULL);
	}

	return 0;
}

void *Filosofo(void *i) {
	int id, j;
	id = *(int*) i;

	for(j = 0; j < 2; j++) {
		pensar(id);
		tomarTenedor(id);
		comer(id);
		ponerTenedor(id);
		printf("\n-----\n");
	}
	return 0;
}

void pensar(int id) {
	printf("Filosofo %d pensando \n", id + 1);
	sleep(3);
}


void comer(int id) {
	printf("Filosofo %d comiendo \n", id + 1);
	sleep(3);
}

void tomarTenedor(int id) {
	sem_wait(&mutex);


	estado[id] = HAMBRIENTO;
	comprobar(id);
	sem_post(&mutex);

	sem_wait(&s[id]);
}

void comprobar(int id) {
	if(estado[id] == HAMBRIENTO && estado[IZQUIERDA(id)] != COMIENDO && estado[DERECHA(id)] != COMIENDO) {
		estado[id] = COMIENDO;

		sem_post(&s[id]);
	}
}

void ponerTenedor(int id) {
	sem_wait(&mutex);

	estado[id] = PENSANDO;

	comprobar(IZQUIERDA(id));
	comprobar(IZQUIERDA(id));
	sem_post(&mutex);
}
