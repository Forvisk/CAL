#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <Windows.h>

LARGE_INTEGER inicio, fim, tempo, frequencia;
int i, j;
int n;	//Tamanho da matriz

void matrizPreenche( int **m1, int **m2){
	srand( time(NULL));
	for( i = 0; i < n; i++)
		for( j = 0; j < n; j++)
			m1[i][j] = rand() % 1000;

	for( i = 0; i < n; i++)
		for( j = 0; j < n; j++)
			m2[i][j] = rand() % 1000;
}

void mostraMatriz( int **m){
	for( i = 0; i < n; i++){
		for( j = 0; j < n; j++)
			printf("%i ", m[i][j]);
		printf("\n");
	}
}

//retirado do exemplo de bubble sort
double time_diff(struct timeval x , struct timeval y){
    double diff;
    diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
    return diff;
}

void multiplicaMatriz( int **m1, int **m2, int **mR){
	int i1, j2, l;
	int k;
	for( i1 = 0; i1 < n; i1++){
		k = 0;
		for( l = 0; l < n; l++){
			for( j2 = 0; j2 < n; j2++){
				k += m1[i1][l]*m2[l][j2];
			}
			mR[i1][l] = k;
		}
	}
	/*
	for( i1 = 0; i1 < n; i1++){
		for( l = 0; l < n; l++){
			printf("%i ", mR[i1][l]);			
		}
		printf("\n");
	}
	*/
}



void main(){
	int **m1, **m2, **mR;
	scanf("%i", &n);
	
	m1 = (int **)malloc(n *sizeof( int*));
	m2 = (int **)malloc(n *sizeof( int*));
	mR = (int **)malloc(n *sizeof( int*));
	for( i = 0; i < n; i++){	
		m1[i] = (int *)malloc(n *sizeof( int*));
		m2[i] = (int *)malloc(n *sizeof( int*));
		mR[i] = (int *)malloc(n *sizeof( int*));
	}

	matrizPreenche( m1, m2);

	mostraMatriz( m1);
	mostraMatriz( m2);
	
	// Inicia o relógio para contar o tempo
    QueryPerformanceFrequency( &frequencia );
    QueryPerformanceCounter( &inicio );



    // Interrompe o relógio e calcula o número de microsegundos da operação
    QueryPerformanceCounter( &fim );
    tempo.QuadPart = fim.QuadPart - inicio.QuadPart;
    tempo.QuadPart *= 1000000;
    tempo.QuadPart /= frequencia.QuadPart;
    printf("Tempo da ordenacao: %li us\n" , tempo );
    printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
    getchar();

    mostraMatriz(mR);
	/*
	int m1[n][n], m2[n][n], mR[n][n];
	srand( time(NULL));
	for( i = 0; i < n; i++)
		for( j = 0; j < n; j++)
			m1[i][j] = rand() % 1000;

	for( i = 0; i < n; i++)
		for( j = 0; j < n; j++)
			m2[i][j] = rand() % 1000;
	*/
	/*
	for( i = 0; i < n; i++){
		for( j = 0; j < n; j++)
			printf("%i ", m1[i][j]);
		printf("\n");
	}
	for( i = 0; i < n; i++){
		for( j = 0; j < n; j++)
			printf("%i ", m2[i][j]);
		printf("\n");
	}
	*/
}
