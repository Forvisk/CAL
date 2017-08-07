//Aula 02 - 04/08/2017
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <Windows.h>

//Adriano Zanella Junior
/*
Contagem de tempo retirada do exemplo de bubble sort do professor
*/

LARGE_INTEGER inicio, fim, tempo, frequencia;

long long expoente( long long a, long long b ){
	int i;
	long long r = a;
	for( i = 1; i < b; i++){
		r = r * a;
	}
	//printf("%lli\n", r);	
	return r;
}

//retirado do exemplo de bubble sort
double time_diff(struct timeval x , struct timeval y){
    double diff;
    diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
    return diff;
}

/*
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
*/

int main(){
	long long a, b, r;
	scanf("%lli %lli", &a, &b);


    // Inicia o relógio para contar o tempo
    QueryPerformanceFrequency( &frequencia );
    QueryPerformanceCounter( &inicio );

	r = expoente(a, b);

	   // Interrompe o relógio e calcula o número de microsegundos da operação
    QueryPerformanceCounter( &fim );
    tempo.QuadPart = fim.QuadPart - inicio.QuadPart;
    tempo.QuadPart *= 1000000;
    tempo.QuadPart /= frequencia.QuadPart;
    printf("Tempo da ordenacao: %li us\n" , tempo );
    printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
    getchar();

    printf("%lli", r);
	return 0;
}
