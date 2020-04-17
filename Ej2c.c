#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

const int T= 99999;
int THREADS;
int may=-1;
int pos=-1;

typedef struct {
	int pos;
	int *array;
} Data;

void Array(int*);
void * Buscar(void*);

int main(){
	printf("Ingrese la cantidad de hilos con la cual se va a buscar \n");
	scanf("%d", &THREADS);
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

	printf("Mayor: %d\n", may);
	printf("Posicion: %d\n", pos);

	return 0;
}

void Array ( int *array){
	srand(time(0));
	int random = rand() % T;

	for (int i = 0; i<T; ++i){
		array[i]=random;
		random = rand() % T;
	}

	int randomPos = rand() % T;


	array[randomPos]=random;
}

void * Buscar (void *tmp){
	Data * data = (Data *) (tmp);
	int c=0;
	int i = data->pos;
	while (c<T/THREADS){
		if(data->array[i]>may){
			may = data->array[i];
			pos = i;
		}
		++c;
		++i;
	}
	pthread_exit(NULL);
}