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
    system("cls");
    printf("\n\n");

    int larguraBase = 2 * numDiscos + 4;
    int alturaBase = 13 - numDiscos;
    int numTorre = 0;
    
    for(int i = 0; i < alturaBase * 3; i++){
        numTorre++;
        int numEspacos = numDiscos + 1;
        for (int j = 0; j < numEspacos; j++) {
            printf(" ");
        }
        printf("|");
        for (int j = 0; j < numEspacos; j++) {
            printf(" ");
        }
        printf("      ");
        if(numTorre == 3){
            numTorre = 0;
            printf("\n");
        }
    }
    for(int i = numDiscos - 1; i >= 0; i--){
        for(int j = 0; j < 3; j++){
            if(i <= torres[j]->topo){
                int disco = torres[j]->discos[i];
                int numEspacos = numDiscos - disco;
                for(int j = 0; j < numEspacos; j++){
                    printf(" ");
                }
                printf("[");
                for(int j = 0; j < disco; j++){
                    printf("#");
                }
                printf("|");
                for(int j = 0; j < disco; j++){
                    printf("#");
                }
                printf("]");
                for(int j = 0; j < numEspacos; j++){
                    printf(" ");
                }
            }else{
                for(int j = 0; j < numDiscos + 1; j++){
                    printf(" ");
                }
                printf("|");
                for(int j = 0; j < numDiscos + 1; j++){
                    printf(" ");
                }
            }
            printf("      ");
        }
        printf("\n");
    }
    
    for(int i = 0; i < 3; i++){
        printf("=");
        for(int j = 0; j < larguraBase; j++){
            printf("=");
        }
        printf("   ");
    }
    printf("\n");
    printf("     T1");
    for(int i = 0; i < numDiscos - 2; i++){
        printf(" ");
    }
    printf("T2");
    for(int i = 0; i < numDiscos - 2; i++){
        printf(" ");
    }
    printf("T3\n\n");
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
void resolverHanoi(Pilha *torres[], int numDiscos){
    criarTorres(torres, numDiscos);
    imprimirTorres(torres, numDiscos);
    autoHanoi(numDiscos, torres[0], torres[2], torres[1], torres, numDiscos);
    printf("----------------------------------------------------------------\n\n");
    printf("Resolucao automatica completa.\n");
    printf("Torre de Hanoi com %d discos resolvida.\n", numDiscos);
    printf("----------------------------------------------------------------\n\n");

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

void iniciarJogo(Pilha *torres[], int numDiscos){
    criarTorres(torres, numDiscos);
    imprimirTorres(torres, numDiscos);
    int movimentos = 0;

    while(torres[2]->topo != numDiscos - 1){
        int torreOrigem, torreDestino;
        printf(">> Escolha a torre de origem (1, 2, 3) ou 0 para reiniciar: ");
        scanf("%d", &torreOrigem);
        if(torreOrigem == 0){
            return;
        }
        while(torreOrigem < 1 || torreOrigem > 3 || torres[torreOrigem-1]->topo == -1){
            printf(">> Escolha uma torre valida e nao vazia: {1, 2, 3} ou 0 para reiniciar: ");
            scanf("%d", &torreOrigem);
            if(torreOrigem == 0){
                return;
            }
        }

        printf(">> Escolha a torre de destino (1, 2, 3) ou 0 para reiniciar: ");
        scanf("%d", &torreDestino);
        if(torreDestino == 0){
            return;
        }
        while(torreDestino < 1 || torreDestino > 3 || (topo(torres[torreDestino-1]) != -1 && topo(torres[torreDestino-1]) < topo(torres[torreOrigem-1]))){
            printf(">> Escolha uma torre valida: {1, 2, 3} ou 0 para reiniciar: ");
            scanf("%d", &torreDestino);
            if(torreDestino == 0){
                return;
            }
        }

        moverDisco(torres[torreOrigem-1], torres[torreDestino-1]);
        movimentos++;
        imprimirTorres(torres, numDiscos);
    }

printf("PARABENS\n");
    printf("Torre de Hanoi com %d discos completadas em %d movimentos.\n", numDiscos, movimentos);
    printf("----------------------------------------------------------------\n\n");

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



void limparTela() {
    system("cls"); 
}

void menu() {
    int numDiscos = 0;
    Pilha *torres[3];

    while(1){
        limparTela();
        int menuOpcao;
        printf("-------- TORRES DE HANOI -------\n\n");
        printf("1 - Jogar Manualmente\n2 - Resolver Automaticamente\n3 - Ver Regras do Jogo\n4 - Sair\n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &menuOpcao);

        switch(menuOpcao){
            case 1:
                if(numDiscos == 0){
                    printf("-------------------------------------------\n\n");
                    printf(">> Digite a quantidade de discos (1-13): ");
                    scanf("%d", &numDiscos);
                    while(numDiscos <= 0 || numDiscos > 13){
                        printf("\033[F\033[K");
                        printf(">> ALERTA: Limite de discos = 13\n");
                        printf(">> Digite a quantidade de discos (1-13): ");
                        scanf("%d", &numDiscos);
                    }
                    for(int i = 0; i < 3; i++){
                        torres[i] = criarPilha(numDiscos);
                    }
                }
                iniciarJogo(torres, numDiscos);
                break;
            case 2:
                if(numDiscos == 0){
                    printf("-----------------------------------------\n\n");
                    printf(">> Digite a quantidade de discos (1-13): ");
                    scanf("%d", &numDiscos);
                    while(numDiscos <= 0 || numDiscos > 13){
                        printf("\033[F\033[K");
                        printf(">> ALERTA: Limite de discos = 13\n");
                        printf(">> Digite a quantidade de discos (1-13): ");
                        scanf("%d", &numDiscos);
                    }
                    for(int i = 0; i < 3; i++){
                        torres[i] = criarPilha(numDiscos);
                    }
                }
                resolverHanoi(torres, numDiscos);
                break;
            case 3:
                hanoiRegras();
                break;
            case 4:
                exit(0);
                break;
        }

        if(menuOpcao == 1 || menuOpcao == 2){
            for(int i = 0; i < 3; i++){
                liberarPilha(torres[i]);
            }
            numDiscos = 0;
        }
    }
}

int main() {
    menu();
    return 0;
}
