#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hanoi.h"

typedef struct Pilha{
    int *discos;
    int topo;
    int capacidade;
} Pilha;

Pilha* criarPilha(int capacidade){
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));
    if(!pilha){
        printf("Erro ao alocar memoria para a pilha.\n");
        exit(1);
    }
    pilha->discos = (int *)malloc(capacidade * sizeof(int));
    if(!pilha->discos){
        printf("Erro ao alocar memoria para os discos.\n");
        exit(1);
    }
    pilha->topo = -1;
    pilha->capacidade = capacidade;
    return pilha;
}

void liberarPilha(Pilha *pilha){
    free(pilha->discos);
    free(pilha);
}

void push(Pilha *pilha, int disco){
    if(pilha->topo == pilha->capacidade - 1){
        printf("Erro: Pilha cheia.\n");
        return;
    }
    pilha->discos[++pilha->topo] = disco;
}

int pop(Pilha *pilha){
    if(pilha->topo == -1){
        printf("Erro: Pilha vazia.\n");
        return -1;
    }
    return pilha->discos[pilha->topo--];
}



int topo(Pilha *pilha){
    if(pilha->topo == -1){
        return -1;
    }
    return pilha->discos[pilha->topo];
}

void criarTorres(Pilha *torres[], int numDiscos){
    for(int i = numDiscos; i > 0; i--){
        push(torres[0], i);
    }
}
