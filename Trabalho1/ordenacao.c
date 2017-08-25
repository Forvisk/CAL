	/*Trabalho 1 - Ordenacao
	* @autor Adriano Zanella Junior
	* Inicio em 24/08/2017
	* Fim em //
	*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <sys/time.h>
	#include <Windows.h>

LARGE_INTEGER inicio, fim, tempo, frequencia;

void iniciaRelogio();
void finalizaRelogio();
int time_diff(struct timeval x , struct timeval y);

int populaVetor( int *vet, int tam, int tipo);

void bubbleSort( int *vet);
void bubble( int *vet, int tam);

void insertSort( int *vet);
void insert( int *vet, int tam);

void mergeSort( int *vet);
int merge( int *vet, int ini, int fim);
void doMerge( int *vet, int ini, int meio, int fim);



int static tam0 = 1000000;
int static tam1 = 25000;
int static tam2 = 50000;
int static tam3 = 75000;
int static tam4 = 100000;

int main(){


	time_t t;
	int *vet, i;
	srand((unsigned) time(&t));

	printf("Iniciando Ordenacoes\n");
		printf("%i", (5 - 2) / 2);
	vet = malloc( tam0 * sizeof(int));
		/*
		populaVetor( vet, tam0, 1);
		populaVetor( vet, tam0, 2);
		populaVetor( vet, tam0, 3);
		populaVetor( vet, tam0, 4);
		*/
		//bubbleSort( vet);
		//printf("\n...\n");
		//insertSort(vet);

	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("Bubble Sort\n");
	bubble(vet, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);

	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("Insert Sort\n");
	insert(vet, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	free(vet);

	/*
	//Deixamos o merge para depois
	printf("\n Populando\n");
	populaVetor( vet, 10, 3);
	for( i = 0; i < 10; i++)
		printf(" %i ", vet[i]);
	printf("Merge Sort\n");
	merge(vet, 0, 10);
	printf("\n Ordenado\n");
	for( i = 0; i < 10; i++)
		printf(" %i ", vet[i]);
	*/

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
		//printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
		//getchar();
	printf("\n...\n");
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
		for( i = tam-1; i >= 0; i--){
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

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		bubble(vet, tam0);
		finalizaRelogio();
	}
}

void bubble( int *vet, int tam){
	int i, j, aux;
	for( i = 0; i < tam; i++){
		for( j = i+1; j < tam; j++){
			if( vet[i] > vet[j]){
				aux = vet[i];
				vet[i] = vet[j];
				vet[j] = aux;
			}
		}
	}
}

void insertSort( int *vet){
	printf("Iniciando testes com Insert Sort\n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		insert(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		insert(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		insert(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		insert(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		insert(vet, tam0);
		finalizaRelogio();
	}
}

void insert( int *vet, int tam){
	int i, j, aux;
	for(i = 0; i < tam; i++){
		for( j = i; j >= 0; j--){
			if( vet[j] < vet[j-1]){
				aux = vet[j];
				vet[j] = vet[j-1];
				vet[j-1] = aux;
			}
		}
	}
}

void mergeSort( int *vet);

int merge( int *vet, int ini, int fim){
	int meio = (fim - ini) / 2;
	if( ini < 2)
	printf("\n Merge %i - %i : %i", ini, fim, meio);
	if( ini >= fim){
		//printf("Saida");
		return 0;
	}
	merge( vet, ini, meio);
	merge( vet, meio+1, fim);
	doMerge( vet, ini, meio, fim);
	return 0;
}

void doMerge( int *vet, int ini, int meio, int fim){
	printf("doMerge %i : %i : %i", ini, meio, fim);
	int i, j, k;
	int *aux;
	aux = malloc((fim - ini +1) * sizeof(int));

	i = ini;
	j = meio;
	k = 0;
	while( ((i < meio) || (j < fim)) && (k < fim-ini+1)){
		if( i < meio){
			if( j < fim){
				if( vet[i] < vet[j]){
					aux[k] = vet[i];
					i++;
				}else if(vet[i] > vet[j]){
					aux[k] = vet[j];
					j++;
				}else{
					aux[k] = vet[i];
					i++;
				}
			}else{
				aux[k] = vet[i];
				i++;
			}
		}else{
			if( j < fim){
				aux[k] = vet[j];
				j++;
			}
		}
		k++;
	}
	i = ini;
	k = 0;
	printf("\n");
	while((i < fim) && ( k < fim-ini+1)){
		vet[i] = aux[k];
		i++;
		k++;
		printf("%i ", vet[i]);
	}
	free(aux);
}
