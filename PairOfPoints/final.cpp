// CALPontos.cpp : Defines the entry point for the console application.
//
// g++ -std=gnu++0x final.cpp -o pfinal

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <Windows.h>

#include <climits>
#include <iostream>

#include <math.h>
#include <algorithm>

using std::min;

// Struct bem simples para testar os algoritmos
typedef struct Ponto {
	int x, y, i;
} Ponto;

//	Mostra o ponto ( T = O(1))
void print(Ponto ponto) {
	printf("P(%u, %u)\n", ponto.x, ponto.y);
};

//Funcoes auxiliares e de distancia
int compareX(const void* a, const void* b)	//	O(1)
{
	Ponto *p1 = (Ponto *)a, *p2 = (Ponto *)b;
	return (p1->x - p2->x);
}

int compareY(const void* a, const void* b)	//	O(1)
{
	Ponto *p1 = (Ponto *)a, *p2 = (Ponto *)b;
	return (p1->y - p2->y);
}

// Algunns defines
LARGE_INTEGER inicio, fim, tempo, frequencia;
void iniciaRelogio();
void finalizaRelogio();
int time_diff(struct timeval x, struct timeval y);

// Para o retorno das funcoes
Ponto menor1;
Ponto menor2;

// Calcula a distancia entre dois pontos
double distance(Ponto po1, Ponto po2) {
	int dX = (po1.x - po2.x);	// O(1)
	int dY = (po1.y - po2.y);	// O(1)
	return sqrt(dX*dX + dY*dY);	//Theta(log n)
}

/* Funcao 1
 * Forca Bruta
 */

double bruteForce(Ponto* pontos, int size) {	// T = O(n**2)	E = O(1)
	double distancia = INT_MAX;
	for (auto i = 0; i < size; i++) {	// O(n)
		//for (auto j = 0; j < size; j++) {	//	O(n)
		for (int j = i+1; j < size; j++) {	//	Soma( i= 1->n, n-i )
			Ponto p1 = pontos[i];
			Ponto p2 = pontos[j];
			if (p1.i != p2.i) {
				double dis = distance(p1, p2);	//	Theta(log n)
				if (dis < distancia) {
					distancia = dis;
				}
			}
		}
	}
	return distancia;
}

/* Funcao 2
 * Distancia da faixa do meio
 */
double FaixaForce(Ponto* pontos, int size) {	// T = O(n**2)	E = O(1)
	double distancia = INT_MAX;
	for (auto i = 0; i < size; i++) {	// O(n)
		//for (auto j = 0; j < size; j++) {	//	O(n)
		for (int j = i+1; j < size && (pontos[j].y - pontos[i].y) <= distancia; j++) {	//	Soma( i= 1->n, n-i )
		//for (int j = i+1; j < size; j++) {
			Ponto p1 = pontos[i];
			Ponto p2 = pontos[j];
			//if (p1.i != p2.i) {
			double dis = distance(p1, p2);	//	Theta(log n)
			if (dis < distancia) {
				distancia = dis;
			}
			//}
		}
	}
	return distancia;
}

/* Funcao 3
* Meu dividir
*	E(n) = 3O(n) + E(n/2)
*	T(n) = 2T(n/2) + O(n**2) 
*	Pelo teorema mestre
*	T(n) = O(n**2)
*	E(n) = O(n)
*/
double divideAndConquer(Ponto* Px, Ponto* Py, int size) {	//	T(n) = 2T(n/2)	+ O(1) + O(n) + O(n log n) = 2T(n/2) + O(n log n)
	int meio = size / 2;
	if (meio <= 3) {
		return bruteForce(Px, size);	// T = O(n**2) -> n <= 7 -> T = O(1) -> max 49 iteracoes
	}

	Ponto mid = Px[meio];

	Ponto* meio1 = (Ponto*)malloc(sizeof(Ponto) * size);	//	E = O(n)
	Ponto* meio2 = (Ponto*)malloc(sizeof(Ponto) * size);	//	E = O(n)

	int m1Counter = 0, m2Counter = 0;

	for (int i = 0; i < size; i++) {	// O(n)
		if (Py[i].x <= mid.x) {
			meio1[m1Counter++] = Py[i];
		}
		else {
			meio2[m2Counter++] = Py[i];
		}
	}

	double d1 = divideAndConquer(Px, meio1, meio);	//	T(n/2)	E(n/2)
	double d2 = divideAndConquer(Px + meio, meio2, size - meio);	//	T(n/2)	E(n/2)

	double menor = min(d1, d2);

	Ponto* strip = (Ponto*)malloc(sizeof(Ponto) * size);	//	E = O(n)
	int stripCounter = 0;
	for (int i = 0; i < size; i++) {	// O(n)
		Ponto p = Py[i];
		if (abs(p.x - mid.x) < menor) {
			strip[stripCounter++] = p;
		}
	}

	double dStrip = FaixaForce(strip, stripCounter);	//	O(n)	E = O(1)

	return min(dStrip, menor);	//	O(1)
}

double dividi(Ponto* pontos, int size) {	//	T(n) = O(n) + 2O(n*log n) = O(n*log n)
	double menorDistancia = INT_MAX;
	int i, j;

	Ponto* Px = (Ponto*)malloc(sizeof(Ponto) * size);
	Ponto* Py = (Ponto*)malloc(sizeof(Ponto) * size);

	for (auto i = 0; i < size; i++) {	//	O(n)
		Px[i] = pontos[i];
		Py[i] = pontos[i];
	}

	std::qsort(Px, size, sizeof(Ponto), compareX);	//	O(n*log n)
	std::qsort(Py, size, sizeof(Ponto), compareY);	//	O(n*log n)


	return divideAndConquer(Px, Py, size);	//	T = O(n**2)
}

int main() {

	int m, n, nump = 0;

	// Nova seed para novos resultados
	srand(time(NULL));

	// Quantidade de pontos a serem testados.
	//auto testes = { 100, 1000, 10000, 20000, 50000, 100000 };
	auto testes = { 10, 100, 1000, 10000, 50000 };


	for (const auto nump : testes) {

		const int maxSizeX = nump * 50;
		const int maxSizeY = nump * 50;

		// Onde iremos guardar os pontos
		Ponto* pontos = (Ponto*)malloc(sizeof(Ponto) * nump);


		// Popula o vetor com pontos aleatorios.
		for (int i = 0; i < nump; i++) {
			pontos[i] = { rand() % maxSizeX, rand() % maxSizeY, i};
		}

		printf("Testando com %i pontos. ", nump);
		
		// *******************************
		//               Forca Bruta
		// *******************************
		printf("Testando forca bruta ");
		{
			// Hmm acho que inicia o relogio.
			iniciaRelogio();

			// Algoritmo aqui :)
			double menorDistancia = bruteForce(pontos, nump);

			// Se pa finaliza o relogio
			finalizaRelogio();

			printf("Menor distancia encontrada por Forca Bruta: %lf\n", menorDistancia);

		}

		// *******************************
		//          Dividir e Conquistar
		// *******************************
		printf("Testando dividir e conquistar ");
		{
			// Hmm acho que inicia o relogio.
			iniciaRelogio();

			// Algoritmo aqui :)
			double menorDistancia2 = dividi(pontos, nump);

			// Se pa finaliza o relogio
			finalizaRelogio();


			printf("Menor distancia encontrada por Dividir e Conquistar: %lf\n", menorDistancia2);

		}

		// Printa so pra gente ter certeza
		/*printf("Menor distancia encontrada: %lf\n", menorDistancia);
		menor1->print();
		menor2->print();*/
		printf("\n\n");
	}

	int c;
	scanf("%d", &c);

}

//Funçõeos de Relógios
void iniciaRelogio() {
	// Inicia o relógio para contar o tempo
	QueryPerformanceFrequency(&frequencia);
	QueryPerformanceCounter(&inicio);
}

void finalizaRelogio() {
	// Interrompe o relógio e calcula o número de microsegundos da operação
	QueryPerformanceCounter(&fim);
	tempo.QuadPart = fim.QuadPart - inicio.QuadPart;
	tempo.QuadPart *= 1000000;
	tempo.QuadPart /= frequencia.QuadPart;
	printf("Tempo da busca: %li us\n", tempo);
	//printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
	//getchar();
}

int time_diff(struct timeval x, struct timeval y) {
	int diff;
	diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
	return diff;
}
