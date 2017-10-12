//
//  main.cpp
//  CAL
//
//  Created by Gustavo Diel on 24/08/17.
//

#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <Windows.h>

#include <algorithm>
#include <vector>

#include <climits>

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
};

double distance(Ponto *po1, Ponto *po2){
    int dX = (po1->x - po2->x);
    int dY = (po1->y - po2->y);
    return sqrt(dX*dX + dY*dY);
}

int main(){

    std::vector<Ponto*> pontos;
    srand(time(NULL));

    const int NUMERO_DE_PONTOS = 10000;

    for (int i = 0; i < NUMERO_DE_PONTOS; i++){
        pontos.push_back(new Ponto(rand() % NUMERO_DE_PONTOS, rand() % NUMERO_DE_PONTOS));
    }
    iniciaRelogio();
    double menorDistancia = INT_MAX;
    Ponto* menor1 = nullptr;
    Ponto* menor2 = nullptr;

    for (auto ponto : pontos){
        for (auto ponto2 : pontos){
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
    finalizaRelogio();
    printf("Menor distancia encontrada: %lf\n", menorDistancia);
    menor1->print();
    menor2->print();

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
