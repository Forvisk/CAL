/**	* Menor distancia entre dois pontos
	* @autor Adriano Zanella Junior
	* Inicio em 24/08/2017
	* Fim em //
	* Para o dia 20/09/2017
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <Windows.h>
#include <Math.h>

#include <vector>
#include <iostream>


LARGE_INTEGER inicio, fim, tempo, frequencia;


void iniciaRelogio();
void finalizaRelogio();
int time_diff(struct timeval x , struct timeval y);



class Ponto{
public:
	int x, y;
	Ponto( int nx, int ny){
		x = nx;
		y = ny;
	}

	void print(){
		printf("( %i, %i)\n", x, y);
	}
};



int main(){
	int m, n, nump;
	int i, nx, ny;
	time_t t;
	std::vector <Ponto> pontos;

	srand((unsigned) time(&t));


	std::cout<<"Insira a largura, altura e numero de pontos da matriz\n"<<std::endl;
	scanf("%i %i %i", &m, &n, &nump);

	if( nump < 2 || m*n <= nump){
		std::cout<<"Numero de pontos invalidos...encerrando..."<<std::endl;
		return 0;
	}

	pontos.reserve( nump);

	for( i = 0; i < nump; i++){
		nx = rand() % m;
		ny = rand() % n;
		Ponto np( nx, ny);
		pontos[i] = np;
		pontos[i].print();
	}


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

float distancia( Ponto p1, Ponto p2){
	return sqrt( ( p1.x - p2.x)*( p1.x - p2.x) + ( p1.y - p2.y)*( p1.y - p2.y));
}

// rand() % tam;
// srand((unsigned) time(&t));