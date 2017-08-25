#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <Windows.h>

int main(){
	int i;
	//int k[1000000];
	int *k;

	k = malloc(1000000 * sizeof(int));
	for( i = 0; i< 1000000; i++){
		k[i] = i;
		printf("%i ", i);
	}
	free(k);
}