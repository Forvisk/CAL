//
//  main.cpp
//  CAL
//
//  Created by Gustavo Diel on 24/08/17.
//
/*
*g++ -std=gnu++0x fBruta.cpp -o brute
*/

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <Windows.h>

#include <algorithm>
#include <vector>

#include <climits>
#include <iostream>

#include <math.h>



LARGE_INTEGER inicio, fim, tempo, frequencia;
void iniciaRelogio();
void finalizaRelogio();
int time_diff(struct timeval x , struct timeval y);


/*
class Ponto {
public:
    Ponto(int a, int b){
        this->x = a; this->y = b;
    }
    int x, y;

    void print(){
        printf("P(%u, %u)\n", this->x, this->y);
    };
};

double distance(Ponto *po1, Ponto *po2){
    int dX = (po1->x - po2->x);
    int dY = (po1->y - po2->y);
    return sqrt(dX*dX + dY*dY);
}
*/

struct Ponto
{
	int x, y;
};

double distance( Ponto po1, Ponto po2){
	int dX = (po1.x - po2.x);
	int dY = (po1.y - po2.y);
	return sqrt(dX*dX + dY*dY);
}

int main(){

	int m, n, nump = 0;
    //std::vector<Ponto*> pontos;
	srand(time(NULL));

	const int NUMERO_DE_PONTOS = 10000;

	std::cout<<"Insira a largura, altura e numero de pontos da matriz\n"<<std::endl;
	scanf("%i %i", &m, &n);
	do{
		scanf("%i", &nump);
		if(nump >= m*n)
			printf("Digite um numero de pontos valido( < %i): ", m*n);
	}while( nump >= m*n);
    /*
    for (int i = 0; i < NUMERO_DE_PONTOS; i++){
        pontos.push_back(new Ponto(rand() % NUMERO_DE_PONTOS, rand() % NUMERO_DE_PONTOS));
    }
    */
    //pontos.reserve(nump);
	Ponto pontos[nump];
	for (int i = 0; i < nump; i++){
        //pontos.push_back(new Ponto(rand() % m, rand() % n));
		pontos[i] = { rand() % m, rand() % n};
	}

	iniciaRelogio();
	double menorDistancia = INT_MAX;
	Ponto menor1;
	Ponto menor2;

	for ( int i = 0; i < nump; i++){
		for ( int j = i+1; j < nump; j++){
            //if (ponto != ponto2 ){
			double distancia = distance( pontos[i], pontos[j]);
			if (distancia < menorDistancia){
				menorDistancia = distancia;
				menor1 = pontos[i];
				menor2 = pontos[i];
			}
            //}
		}
	}
	finalizaRelogio();
	printf("Menor distancia encontrada: %lf\n", menorDistancia);
    //menor1->print();
    //menor2->print();
    printf("P( %i, %i))\n", menor1.x, menor1.y);
    printf("P( %i, %i))\n", menor2.x, menor2.y);

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
	printf("Tempo da busca: %li us\n" , tempo );
        //printf("Relogio parado... Pressione qualquer tecla para continuar\n" );
        //getchar();
	printf("\n...\n");
}

int time_diff(struct timeval x , struct timeval y){
	int diff;
        diff = (y.tv_sec - x.tv_sec) + 1e-6 * (y.tv_usec - x.tv_usec); /* in seconds */
	return diff;
}
