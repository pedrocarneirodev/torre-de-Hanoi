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
void imprimirTorres(Pilha *torres[], int numDiscos){
    printf("\n\n");
    for(int i = numDiscos - 1; i >= 0; i--){
        for(int j = 0; j < 3; j++){
            if(i <= torres[j]->topo){
                if(torres[j]->discos[i] < 10){
                    printf("| %.2d |   ", torres[j]->discos[i]);
                }else{
                    printf("| %.2d |   ", torres[j]->discos[i]);
                }
            }else{
                printf("|    |   ");
            }
        }
        printf("\n");
    }
    printf("------- -------- --------\n");
    printf("  T1      T2      T3\n\n");
}

void moverDisco(Pilha *origem, Pilha *destino){
    int disco = pop(origem);
    if(disco != -1){
        push(destino, disco);
    }
}

void autoHanoi(int n, Pilha *origem, Pilha *destino, Pilha *auxiliar, Pilha *torres[], int numDiscos){
    if(n == 1){
        moverDisco(origem, destino);
        imprimirTorres(torres, numDiscos);
        return;
    }
    autoHanoi(n-1, origem, auxiliar, destino, torres, numDiscos);
    moverDisco(origem, destino);
    imprimirTorres(torres, numDiscos);
    autoHanoi(n-1, auxiliar, destino, origem, torres, numDiscos);
}



void hanoiRegras(){
    system("cls");
    printf("----------------------------------------------------------------\n\n");
    printf("Objetivo:\n");
    printf("Mover todos os discos da primeira torre para a terceira torre,\n");
    printf("usando a segunda torre como auxiliar.\n\n");
    printf("Regras:\n");
    printf("1. Existem tres torres e um numero variavel de discos de tamanhos diferentes.\n");
    printf("2. Apenas um disco pode ser movido por vez.\n");
    printf("3. Um disco maior nao pode ser colocado sobre um disco menor.\n");
    printf("4. Todos os discos comecam empilhados em ordem decrescente na primeira torre.\n\n");
    printf("Instrucoes:\n");
    printf("1. O jogador pode escolher o numero de discos.\n");
    printf("2. O jogo oferece modos automatico e manual.\n");
    printf("3. Pode reiniciar o jogo a qualquer momento.\n\n");
    printf("----------------------------------------------------------------\n");

    char opcao;
    do{
        printf("\n-> Deseja voltar ao menu (s/n): ");
        scanf(" %c", &opcao);

        if(opcao == 'n'){
            exit(0);
        }else if(opcao != 's'&& opcao != 'n'){
            printf("\033[F\033[K");
            printf("Opcao incorreta. Tente novamente.");
        }
    }while(opcao != 's');
}
