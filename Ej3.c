#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int T;
const int P=500;
int THREADS;
int may=-1;
int pos=-1;

struct {
  pthread_mutex_t mutex;
  char symbol;
} shared = { PTHREAD_MUTEX_INITIALIZER };

typedef struct {
    int pos;
    int *array;
} Data;

void Array(int*);
void * Buscar(void*);

int main(){
    printf("Ingrese el tamano del array");
    scanf("%d", &T);

    printf("Ingrese la cantidad de hilos con la cual se va a buscar (2-9) \n");
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

    printf("\n\nMayor: %d\n", may);
    printf("Posicion: %d\n", pos);

    return 0;
}

void Array ( int *array){
    srand(time(0));
    int random = rand() % P-1;

    for (int i = 0; i<T; ++i){
        array[i]=random;
        random = rand() % P-1;
    }

    int randomPos = rand() % T;


    array[randomPos]=P;
}

void * Buscar (void *tmp){
    Data * data = (Data *) (tmp);
    int c=0;
    int i = data->pos;
    while (c<T/THREADS){
        if(data->array[i]>may){
            pthread_mutex_lock(&shared.mutex);//Con esto nos aseguramos que el que pase
            printf("Se gana al mutex\n");     //a linea 81 significa que tiene el mutex a su poder
            may = data->array[i];
            pos = i;
            printf("Se libera el mutex\n");
            pthread_mutex_unlock(&shared.mutex);
        }
        ++c;
        ++i;
    }
    printf("Cambio de THREAD\n");
    printf("Ultima posicion %d\n",i);
    pthread_exit(NULL);
}