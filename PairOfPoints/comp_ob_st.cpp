//teste obj


#include <sys/time.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>

LARGE_INTEGER inicio, fim, tempo, frequencia;
void iniciaRelogio();
void finalizaRelogio();
int time_diff(struct timeval x , struct timeval y);


void testeObj();
void testeStruct();

struct st{
	int k, y, z;
};

class cl{
public:
	cl(int k, int y, int z){
		this->k = k;
		this->y = y;
		this->z = z;
	}
	int k, y, z;

	void print(){
		printf("%i %i %i\n", k, y, z);
	};
};


int main(){
	printf("Teste classe\n");
	iniciaRelogio();
	testeObj();
	finalizaRelogio();


	printf("Teste struct\n");
	iniciaRelogio();
	testeStruct();
	finalizaRelogio();
}


void testeObj(){
	int n = 100000;
	std::vector<cl*> vc;
	int i;

	for( i = 0; i < n; i++){
		vc.push_back( new cl( i, i+5, i-15));
	}

	for( auto v : vc){
	}

	for( auto v : vc){
		for(auto v2: vc){

		}
		//v->print();
	}
}


void testeStruct(){
	int n = 100000;
	st vc[n];
	int i, j;

	for( i = 0; i < n; i++ ){
		st nst = {i, i+5, i-15};
		vc[n] = nst;
	}

	for( i = 0; i < n; i++){
		//printf("%i %i %i\n", vc[i].k), vc[i].y, vc[i].z;
	}

	for( i = 0; i < n; i++){
		for( j = 0; j < n; j++){}
		//printf("%i %i %i\n", vc[i].k), vc[i].y, vc[i].z;
	}
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