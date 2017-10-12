/*
*	Compila: g++ -std=gnu++0x dAndC.cpp -o cpop
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


class Ponto {
public:
	Ponto(int a, int b){
		this->x = a; this->y = b;
	}
	int x, y;

	void print(){
		printf("P(%u, %u)\n", this->x, this->y);
	};

	int get_y(){
		return y;
	};

};


float min( float x, float y);
double divideandconquest( std::vector<Ponto*> pontos, int nump);
double menorDistanciaPP( std::vector<Ponto*> Px, std::vector<Ponto*> Py, int nump);
double brute( std::vector<Ponto*> P, int nump);
double stripDistancia( std::vector<Ponto*> strip, double menorDistancia);
bool stripComp_y( Ponto* p1, Ponto* p2, double dist);

double distance(Ponto *po1, Ponto *po2){
	long int dX = (po1->x - po2->x);
	long int dY = (po1->y - po2->y);
	return sqrt(dX*dX + dY*dY);
}

bool funcaoPraOrdernar (Ponto* p1, Ponto* p2) { return ( p1->y < p2->y  ); }

int main(){

	int m, n, nump = 0;
	time_t t;
	double menorDistancia;

	std::vector<Ponto*> pontos;

//srand(time(NULL));
	srand((unsigned) time(&t));

	const int NUMERO_DE_PONTOS = 10000;


	std::cout<<"Insira a largura, altura e numero de pontos da matriz\n"<<std::endl;
	scanf("%i %i", &m, &n);
	do{
		scanf("%i", &nump);
		if(nump >= m*n)
			printf("Digite um numero de pontos valido( < %i): ", m*n);
	}while( nump >= m*n);

	//pontos.reserve(nump);
	for (int i = 0; i < nump; i++){
		pontos.push_back(new Ponto(rand() % m, rand() % n));
		//pontos[i] = new Ponto( rand() % m, rand() % n);
		//pontos[i]->print();
	}
	//printf("Exit 1\n");
	iniciaRelogio();

	menorDistancia = divideandconquest( pontos, nump);

	finalizaRelogio();
	printf("Menor distancia encontrada: %lf\n", menorDistancia);
	//brute( pontos, nump);
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

//Dividir e Conquistar
double divideandconquest( std::vector<Ponto*> pontos, int nump){
	double menorDistancia = INT_MAX;
	int i, j;

	std::vector<Ponto*> Px;
	std::vector<Ponto*> Py;

	for( auto ponto : pontos){
		Px.push_back(ponto);
		Py.push_back(ponto);
	}

	std::sort (Px.begin(), Px.end(), funcaoPraOrdernar);
	std::sort (Py.begin(), Py.end(), funcaoPraOrdernar);
	/*
	printf("Px\n");
	for (auto ponto2 : Px){
		ponto2->print();
	}
	printf("Py\n");
	for (auto ponto2 : Py){
		ponto2->print();
	}
	*/

	menorDistancia = menorDistanciaPP( Px, Py, nump);

	return menorDistancia;
}  

double menorDistanciaPP( std::vector<Ponto*> Px, std::vector<Ponto*> Py, int nump){
	double menorDistancia = INT_MAX;
	double md1, md2;
	int meio = nump/2;

	if (nump < 3){
		//printf("Exit PPbrute %4i", nump);
		return brute(Px, nump);
	}

	Ponto* pmeio = Px[meio];
	std::vector<Ponto*> Pyd;
	std::vector<Ponto*> Pye;


	printf("Loop Tam: %4i\n", nump);
	for( auto ponto : Py){
		if( ponto->x <= pmeio->x)
			Pye.push_back(ponto);
		else
			Pyd.push_back(ponto);
	}

	//printf("Menor Px %4i %4i\n", meio, nump-meio);
	md1 = menorDistanciaPP( Px, Pye, meio);
	md2 = menorDistanciaPP( Px, Pyd, nump-meio);

	if( md1 < md2)
		menorDistancia = md1;
	else
		menorDistancia = md2;

	std::vector<Ponto*> strip;
	for( auto ponto : Py){
		if( abs(ponto->x - pmeio->x) < menorDistancia)
			strip.push_back(ponto);
	}

	double stripMe = stripDistancia( strip, menorDistancia);
	if( menorDistancia < stripMe){
		//printf("Exit PPMd    %4i : %lf\n", nump, menorDistancia);
		return menorDistancia;
	}
	else{
		//printf("Exit PPStrip %4i : %lf\n", nump, stripMe);
		return stripMe;
	}

	//printf("Exit PP      %4i\n", nump);
	return menorDistancia;
}

double brute( std::vector<Ponto*> P, int nump){
	double menorDistancia = INT_MAX;
    Ponto* menor1 = nullptr;
    Ponto* menor2 = nullptr;
    printf("Loop brute tam: %i\n", nump*nump);
	for (auto ponto : P){
		for (auto ponto2 : P){
			if (ponto != ponto2 ){
				double distancia = distance(ponto, ponto2);
				if (distancia < menorDistancia){
					menorDistancia = distancia;
                    menor1 = ponto;
                    menor2 = ponto2;
				}
			}
		}
	}
	//printf(" : %lf\n", menorDistancia);
    //menor1->print();
    //menor2->print();
	return menorDistancia;
}

double stripDistancia( std::vector<Ponto*> strip, double menorDistancia){
	double dm = menorDistancia;

	//for( auto ponto = strip.begin(); ponto != std::end(strip); ++ponto){
	for( auto ponto : strip){
		for( auto ponto2 = ponto++; ponto2 < strip.back() && stripComp_y( ponto, ponto2, dm); ++ponto2){
			//printf("...");
			double newd = distance( ponto, ponto2);
			if( newd < dm)
				dm = newd;
		}
	}
	return dm;
}

bool stripComp_y( Ponto *p1, Ponto *p2, double dist){
	return (p2->y - p1->y) < dist;
}
