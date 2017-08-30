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

void heapSort( int *vet);
void heap( int *vet, int tam);
void heapfy( int *vet, int tam, int i);
void buildHeap( int *vet, int tam);

void countingSort( int *vet);
void countSort( int *vet, int tam);


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
	//heapSort( vet);
	//printf("\n...\n");
	countingSort(vet);
	printf("\n...\n");
	countingSort(vet);
	printf("\n...\n");
	
	*/

	
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

	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nMerge Sort");
	merge(vet, 0, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	
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

	printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nHeap Sort");
	heap(vet, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);

		printf("\n Populando\n");
	populaVetor( vet, 500, 3);
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);
	printf("\nCounting Sort");
	countSort(vet, 500);
	printf("\n Ordenado\n");
	for( i = 0; i < 500; i++)
		printf(" %i ", vet[i]);

	free(vet);

	return 0;
}

//Funçõeos de Relógios
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

int time_diff(struct timeval x , struct timeval y){
	int diff;
		diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
	return diff;
}

//Popula o vetor
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

//Funções de Bubble Sort
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

//Funções de Insert Sort
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

//Funções de Merge Sort
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
	//int k;
	if( fim - ini < 2){
		//printf("\nSaindo %i - %i\n", ini, fim);
		return 0;
	}
	meio = (fim + ini) / 2;
	//printf("ini: %i, fim: %i, meio: %i\n", ini, fim, meio);

	merge( vet, ini, meio);
	//for( k=ini; k<meio;k++)
	//	printf("%i ", vet[k]);
	//printf("\n");
	merge( vet, meio, fim);
	//for( k=meio+1; k<fim;k++)
	//	printf("%i ", vet[k]);
	//printf("\n");
	doMerge( vet, ini, meio, fim);
	//printf("\n");
	return 1;
}

void doMerge( int *vet, int ini, int meio, int fim){
	//printf("doMerge %i : %i : %i\n", ini, meio, fim);
	int i, j, k;
	int *newVet;
	i = ini;
	j = meio;
	newVet = malloc( (fim - ini +1) * sizeof(int));
	k = 0;
	while( (i < meio) && (j < fim)){
		if( vet[i] <= vet[j]){
			//printf("%i[%i] <= %i[%i]\n", vet[i], i, vet[j], j);
			newVet[k] = vet[i];
			i++; 
		}else{
			//printf("%i > %i\n", vet[i], vet[j]);
			newVet[k] = vet[j];
			j++;
		}
		//printf("%i[%i]\n", newVet[k], k);
		k++;
	}
	//printf("i:%i %i j:%i %i k:%i %i\n", i, meio, j, fim, k, (fim - ini +1));
	if( i == meio){
		while( j < fim){
			newVet[k] = vet[j];
			//printf("j: %i[%i]\n", newVet[k], k);
			j++;
			k++;
		}
	}else{
		while( i < meio){
			newVet[k] = vet[i];
			//printf("i: %i[%i]\n", newVet[k], k);
			i++;
			k++;
		}
	}
	k = 0;
	i = ini;
	while( k < (fim-ini+1) && i < fim){
		vet[i] = newVet[k];
		//printf("%i ", vet[i]);
		k++;
		i++;
	}

	free(newVet);
}

//Funções de Quick Sort com primeiro elemento como pivo
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

//Funções Quick Sort com pivo aleatório
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

//Funções de Heap Sort
void heapSort( int *vet){
	printf("Iniciando testes com Heap Sort\n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		heap(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		heap(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		heap(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		heap(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		heap(vet, tam0);
		finalizaRelogio();
	}
}

void heap( int *vet, int tam){
	int i, aux;
	buildHeap( vet, tam);
	for( i = tam-1; i > 0; i--){
		aux = vet[0];
		vet[0] = vet[i];
		vet[i] = aux;
		heapfy(vet, i, 0);
	}
}

void heapfy( int *vet, int tam, int i){
	int e, d, maior, aux;
	e = (2*i + 1);
	d = (2*i + 2);
	if( (e < tam) && ( vet[e] > vet[i]) )
		maior = e;
	else
		maior = i;

	if( (d < tam) && ( vet[d] > vet[maior]) )
		maior = d;

	if( maior != i){
		aux = vet[i];
		vet[i] = vet[maior];
		vet[maior] = aux;
		heapfy( vet, tam, maior);
	}
}

void buildHeap( int *vet, int tam){
	int i;
	for( i = tam/2; i >= 0; i--)
		heapfy( vet, tam, i);
}


//Funções de Counting Sort
void countingSort( int *vet){
	printf("Iniciando testes com Heap Sort\n");

	if( populaVetor( vet, tam1, 1)){
		iniciaRelogio();
		countSort(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 1)){
		iniciaRelogio();
		countSort(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 1)){
		iniciaRelogio();
		countSort(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 1)){
		iniciaRelogio();
		countSort(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 1)){
		iniciaRelogio();
		countSort(vet, tam0);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam1, 2)){
		iniciaRelogio();
		countSort(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 2)){
		iniciaRelogio();
		countSort(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 2)){
		iniciaRelogio();
		countSort(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 2)){
		iniciaRelogio();
		countSort(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 2)){
		iniciaRelogio();
		countSort(vet, tam0);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam1, 3)){
		iniciaRelogio();
		countSort(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 3)){
		iniciaRelogio();
		countSort(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 3)){
		iniciaRelogio();
		countSort(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 3)){
		iniciaRelogio();
		countSort(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 3)){
		iniciaRelogio();
		countSort(vet, tam0);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam1, 4)){
		iniciaRelogio();
		countSort(vet, tam1);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam2, 4)){
		iniciaRelogio();
		countSort(vet, tam2);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam3, 4)){
		iniciaRelogio();
		countSort(vet, tam3);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam4, 4)){
		iniciaRelogio();
		countSort(vet, tam4);
		finalizaRelogio();
	}

	if( populaVetor( vet, tam0, 4)){
		iniciaRelogio();
		countSort(vet, tam0);
		finalizaRelogio();
	}
}

void countSort( int *vet, int tam){
	int i, k;
	int maior = 0;
	int *aux;
	for( i = 0; i < tam; i++){
		if( vet[i] > maior)
			maior = vet[i];
	}
	aux = malloc( (maior+1) * sizeof(int));
	for( i = 0; i < (maior+1); i++)
		aux[i] = 0;
	for( i = 0; i < tam; i++)
		aux[ vet[i]]++;
	k = 0;
	//for( i =0; i < (maior+1); i++)
	//	printf(" %i[%i]", aux[i], i);
	//printf("\n");
	for( i = 0; i < (maior+1); i++){
		while((aux[i] > 0) && ( k < tam)){
			vet[k] = i;
			aux[i]--;
			k++;
		}
	}


}