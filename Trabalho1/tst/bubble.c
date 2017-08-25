//Trabalho 1 - Bubble sort
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <Windows.h>

//#define tam 1000000

LARGE_INTEGER inicio, fim, tempo, frequencia;

int populaVetor( int *vet, int tam, int tipo);
void bubbleSort( int *vet);
void bubble( int *vet, int tam);
int time_diff(struct timeval x , struct timeval y);

void iniciaRelogio();
void finalizaRelogio();

int tam = 1000000;
int tam1 = 25000, tam2 = 50000, tam3 = 75000, tam4 = 100000;

int main(){


	time_t t;
	int *vet, i;
	srand((unsigned) time(&t));

	printf("Iniciando bubble sort\n");

	vet = malloc( tam * sizeof(int));
	/*
	populaVetor( vet, tam, 1);
	populaVetor( vet, tam, 2);
	populaVetor( vet, tam, 3);
	populaVetor( vet, tam, 4);
	*/
	bubbleSort( int vet);

	free(vet);

	return 0;
}

void iniciaRelogio(){
	// Inicia o relógio para contar o tempo
    QueryPerformanceFrequency( &frequencia );
    QueryPerformanceCounter( &inicio );
}

void finalizaRelogio(){
    // Interrompe o relógio e calcula o número de microsegundos da operação
    QueryPerformanceCounter( &fim );
    tempo.QuadPart = fim.QuadPart - inicio.QuadPart;
    tempo.QuadPart *= 1000000;
    tempo.QuadPart /= frequencia.QuadPart;
    printf("Tempo da ordenacao: %li us\n" , tempo );
    printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
    getchar();
}

//retirado do exemplo de bubble sort
int time_diff(struct timeval x , struct timeval y){
    int diff;
    diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
    return diff;
}

int populaVetor( int *vet, int tam, int tipo){
	int i;
	printf("Iniciando vetor de %i numeros ", tam);

	//vet = malloc( tam * sizeof(int));
	switch (tipo){
		case 1:
			printf("crescente.\n");
			for( i = 0; i < tam; i++){
				vet[i] = i+1;
			}
			break;
		case 2:
			printf("decrescente.\n");
			for( i = tam-1; i > 0; i--){
				vet[i] = i+1;
			}
			break;
		case 3:
			printf("aleatorio.\n");
			for(i = 0; i < tam; i++){
				vet[i] = rand() % 1000;
			}
			break;
		case 4:
			printf("aleatorio com 100000000.\n");
			for(i = 0; i < tam; i++){
				vet[i] = rand() % 1000;
			}
			i = rand() % tam;
			vet[i] = 100000000;
			break;
		default:
			printf("\nErro!\n");
			return 0;
	}
	/*
	for( i = 0; i < 100; i++)
		printf("%i ", vet[i]);
	printf("\n");
	*/
	return 1;
}

void bubbleSort( int *vet){
	printf("Iniciando testes com Bubble Sort\n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		bubble(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		bubble(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		bubble(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		bubble(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam, 1)){
		iniciaRelogio();
		bubble(vet, tam);
		finalizaRelogio();
	}
}

void bubble( int *vet ,int tam){
	int i, j, aux;
	for( i = 0; i < tam; i++){
		for( j = i+1; j < tam; j++){
			if( vet[i] == vet[j]){
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
		}
	}
}