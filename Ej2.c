#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int T;
const int P=500;

int may=-1;
int pos=-1;

void Array(int*);
void Buscar(int*);

int main(){
	printf("Ingrese el tamano del array");
	scanf("%d", &T);

	int * array = (int *) calloc (T, sizeof(int));

	Array(array);
	Buscar(array);

	printf("Mayor: %d\n", may);
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