#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

const int T= 99999;

int may=-1;
int pos=-1;

void Array(int*);
void Buscar(int*);

int main(){
	int * array = (int *) calloc (T, sizeof(int));

	Array(array);
	Buscar(array);

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

void Buscar (int *array){
	int c = 0;
	int i = 0;

	while (c<T){
		if(array[i]>may){
			may = array[i];
			pos = i;
		}
		++c;
		++i;
	}
}