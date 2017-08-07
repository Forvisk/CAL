//Aula 02 - 04/08/2017
#include <stdio.h>
#include <stdlib.h>

int expoente( int a, int b ){
	int i;
	int r = a;
	for( i = 1; i < b; i++){
		r = r * a;
	}
	printf("%i\n", r);	
}

void **multiplicaMatriz( int **m1, int **m2, int n){
	int mR[n][n];
	int i1, j2, l;
	int k;
	for( i1 = 0; i1 < n; i1++){
		k = 0;
		for( l = 0; l < n; l++){
			for( j2 = 0; j2 < n; j2++){
				k += m1[i1][l]*m2[l][j2];
			}
		}
		mR[i1][l] = k;
	}
	
	for( i1 = 0; i1 < n; i1++){
		for( l = 0; l < n; l++){
			printf("%i ", mR[i1][l]);			
		}
		printf("\n");
	}
}

int main(){
	int a, b;
	scanf("%i %i", &a, &b);
	expoente(a, b);
	return 0;
}
