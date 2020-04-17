#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

const int T= 99999;
const int THREADS = 2;

typedef struct {
	int pos;
	int *array;
} Data;

void Array(int*);
void * Buscar(void*);

int main(){
	Data * data = (Data*) calloc (THREADS, sizeof(Data));
	int * array = (int *) calloc (T, sizeof(int));

	Array(array);
	int p;

	for(int i = 0; i<THREADS;++i){
		data[i].array = array;
		data[i].pos = p;
		p = p + T/THREADS;
	}

	pthread_t * thread = (pthread_t*) calloc (THREADS, sizeof(pthread_t));

	for (int i = 0; i<THREADS; ++i){
		pthread_create(&thread[i],NULL,Buscar,(void *) &data[i]);
	}

	for (int i = 0; i<THREADS; ++i){
		pthread_join(thread[i], NULL);
	}

	return 0;
}

void Array ( int *array){
	for (int i = 0; i<T; ++i)
		array[i]=0;
	srand(time(0));
	int random = rand() % T;

	array[random]=1;
}

void * Buscar(void *tmp){
	Data * data = (Data *) (tmp);
	int c=0;
	int i = data->pos;

	while (c < T/THREADS){
		if(data->array[i] == 1){
			printf("El 1 esta en la pos %d\n", i);
			pthread_exit(NULL);
		}
		++c;
		++i;
	}
	pthread_exit(NULL);
}