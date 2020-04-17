#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

const int T = 99999;

void Array(int*);
void Buscar(int*);

int main (){
	int *a;
	a = (int*) calloc (T, sizeof(int));

	Array(a);
	Buscar(a);

	return 0;
}

void Array ( int *a){
	for (int i = 0; i<T; ++i)
		a[i]=0;
	srand(time(0));
	int random = rand() % T;

	a[random]=1;
}

void Buscar( int *a){
	for (int i=0; i<T; ++i){
		if(a[i]==1){
			printf("El 1 esta en la pos %d\n", i);
			break;
		}
	}
}