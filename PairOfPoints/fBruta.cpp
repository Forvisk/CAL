//
//  main.cpp
//  CAL
//
//  Created by Gustavo Diel on 24/08/17.
//

/*
 Escreva os algoritmo Bubble Sort, Insert Sort, Merge Sort, Quick Sort, Heap Sort, Counting Sort e Bucket Sort. O algoritmo Quick Sort deve ser implementado de duas maneiras: (1) usando o primeiro elemento como pivô, (2) selecionando um elemento qualquer como pivô.
 */

#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <vector>

#include <math.h>

#include <sys/time.h>


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

    printf("Menor distancia encontrada: %lf\n", menorDistancia);
    menor1->print();
    menor2->print();

}



















