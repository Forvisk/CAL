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

void quickSortFirst( int *vet);
int quickFirst( int *vet, int ini, int fim);
int pivoFirst( int *vet, int ini, int fim);

void quickSortRand( int *vet);
int quickRand( int *vet, int ini, int fim);
int pivoRand( int *vet, int ini, int fim);


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
	//printf("\n...\n");
	//mergeSort(vet);
	//printf("\n...\n");
	//quickSortFirst( vet);
	//printf("\n...\n");
	//quickSortRand(vet);
	//printf("\n...\n");

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
	printf("\nBubble Sort");
	bubble(vet, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);

	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nInsert Sort");
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
	printf("\nMerge Sort");
	merge(vet, 0, 500);
	printf("Merge Sort\n");
	merge(vet, 0, 10);
	printf("\n Ordenado\n");
	for( i = 0; i < 10; i++)
		printf(" %i ", vet[i]);
	*/
	
	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nQuick Sort First");
	quickFirst(vet, 0, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 10; i++)
		printf(" %i ", vet[i]);
	
	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nQuick Sort Rand");
	quickRand(vet, 0, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);

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

void mergeSort( int *vet){
	printf("Iniciando testes com Merge Sort\n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		merge(vet, 0, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		merge(vet, 0, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		merge(vet, 0, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		merge(vet, 0, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		merge(vet, 0, tam0);
		finalizaRelogio();
	}
}

int merge( int *vet, int ini, int fim){
	int meio;
	if( ini - fim < 2)
		return 0;
	else
		printf("ini: %i, fim: %i, meio: %i\n", ini, fim, meio);
	meio = (fim + ini) / 2;
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
	return 1;
}

void doMerge( int *vet, int ini, int meio, int fim){
	printf("doMerge %i : %i : %i", ini, meio, fim);
	int i, j, k;
	i = ini;
	j = meio;
	newVet = malloc( (fim - ini +1)*sizeof(int));
	
	for( k = 0; k < (fim - ini +1); k++){
		if( (i < meio) && ((j >= fim) || (vet[i] < vet[j]))){
			newVet[k] = vet[i];
			i++;
		}else{
			newVet[k] = vet[j];
			j++;
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
	}

	i = ini;
	k = 0;
	while( (i < fim) && (k < (fim-ini+1))){
		vet[i] = newVet[k];
	printf("\n");
	while((i < fim) && ( k < fim-ini+1)){
		vet[i] = aux[k];
		i++;
		k++;
		printf("%i ", vet[i]);
	}
	free(newVet);
}

void quickSortFirst( int *vet){
	printf("Iniciando testes com Quick Sort com o primeiro elemento como pivo \n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		quickFirst(vet, 0, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		quickFirst(vet, 0, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		quickFirst(vet, 0, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		quickFirst(vet, 0, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		quickFirst(vet, 0, tam0);
		finalizaRelogio();
	}
}

int quickFirst( int *vet, int ini, int fim){
	int meio;
	//printf("ini: %i, fim: %i\n", ini, fim);
	if( ini >= fim){
		return 0;
	}
	meio = pivoFirst(vet, ini, fim);
	quickFirst(vet, ini, meio);
	quickFirst(vet, meio+1, fim);
	return 1;
}

int pivoFirst( int *vet, int ini, int fim){
	int pivo = ini;
	int i, aux = 0;
	for( i = ini+1; i < fim; i++){
		if( vet[i] < vet[ini]){
			pivo++;
			aux = vet[i];
			vet[i] = vet[pivo];
			vet[pivo] = aux;
		}
	}
	aux = vet[ini];
	vet[ini] = vet[pivo];
	vet[pivo] = aux;
	//printf("pivo: %i  = %i\n", pivo, vet[pivo]);
	return pivo;
}

void quickSortRand( int *vet){
	printf("Iniciando testes com Quick Sort com um elemento qualquer de pivo \n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		quickRand(vet, 0, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		quickRand(vet, 0, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		quickRand(vet, 0, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		quickRand(vet, 0, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		quickRand(vet, 0, tam0);
		finalizaRelogio();
	}
}

int quickRand( int *vet, int ini, int fim){
	int meio;
	//printf("ini: %i, fim: %i\n", ini, fim);
	if( ini >= fim){
		return 0;
	}
	meio = pivoRand(vet, ini, fim);
	quickRand(vet, ini, meio);
	quickRand(vet, meio+1, fim);
	return 1;
}


int pivoRand( int *vet, int ini, int fim){
	int pivo = ini + rand() % (fim - ini);
	int i, aux = 0;
	//printf("Troca %i[%i] por pivo %i[%i]\n", vet[ini], ini, vet[pivo], pivo);
	aux = vet[pivo];
	vet[pivo] = vet[ini];
	vet[ini] = aux;
	pivo = ini;
	for( i = ini+1; i < fim; i++){
		if( vet[i] < vet[ini]){
			//printf("Troca %i[%i] por %i[%i]\n", vet[i], i, vet[pivo+1], pivo+1);
			pivo++;
			aux = vet[i];
			vet[i] = vet[pivo];
			vet[pivo] = aux;
		}
	}
	aux = vet[ini];
	vet[ini] = vet[pivo];
	vet[pivo] = aux;
	//printf("Troca %i[%i] por pivo %i[%i]\n", vet[ini], ini, vet[pivo], pivo);
	//printf("Meio: %i[%i]\n", vet[pivo], pivo);
	return pivo;
}