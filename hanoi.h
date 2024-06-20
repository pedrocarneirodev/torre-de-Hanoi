#ifndef HANOI_H
#define HANOI_H

typedef struct Pilha Pilha;

Pilha* criarPilha(int capacidade);
void liberarPilha(Pilha *pilha);
void push(Pilha *pilha, int disco);
int pop(Pilha *pilha);
int topo(Pilha *pilha);
void criarTorres(Pilha *torres[], int numDiscos);
void imprimirTorres(Pilha *torres[], int numDiscos);
void moverDisco(Pilha *origem, Pilha *destino);
void autoHanoi(int n, Pilha *origem, Pilha *destino, Pilha *auxiliar, Pilha *torres[], int numDiscos);
void hanoiRegras();
void resolverHanoi(Pilha *torres[], int numDiscos);
void iniciarJogo(Pilha *torres[], int numDiscos);
void menu();

#endif