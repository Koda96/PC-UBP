#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void Array(int*,int);
void Buscar(int*,int);

int main (){
	int *a;
	int T;
	printf("Ingrese el tamano del array");
	scanf("%d", &T);
	a = (int*) calloc (T, sizeof(int)); // Se declara el array dinamicamente

	Array(a,T);
	Buscar(a,T);

	return 0;
}

void Array ( int *a, int T){
	for (int i = 0; i<T; ++i)
		a[i]=0; // Se rellena con ceros
	srand(time(0)); //Se genera la semilla de la funcion random
	int random = rand() % T;

	a[random]=1;
}

void Buscar( int *a, int T){
	for (int i=0; i<T; ++i){
		if(a[i]==1){
			printf("El 1 esta en la pos %d\n", i);
			break;
		}
	}
}