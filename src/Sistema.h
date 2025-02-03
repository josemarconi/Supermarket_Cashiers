#ifndef SISTEMA_H
#define SISTEMA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Cliente 
{
    char nome[100];
    char CPF[14]; 
    int prioridade;
    int itens_Carrinho;
    struct Cliente* prox;

} Cliente;

typedef struct Caixa 
{
    int id;
    int aberto;
    Cliente* filaPrioridade[3];
    // Fila ligada //
    // Uma array de três ponteiros cada ponteiro aponta para a lista de prioridade// 
    // uma para cada tipo de prioridade de cliente (1,2 e 3) (lista ligada)//

} Caixa;

int contarCaixasAbertos(Caixa* caixas, int numCaixas);
int caixaComMenosClientes(Caixa* caixas, int numCaixas);
int cpfJaCadastrado(Caixa* caixas, int numCaixas, const char* cpf);
void cadastrarCliente(Caixa* caixas, int numCaixas);
void atenderCliente(Caixa* caixas, int numCaixas);
void abrirFecharCaixa(Caixa* caixas, int numCaixas, int idCaixa, int abrir);
void imprimirClientesEspera(Caixa* caixas, int numCaixas);
void imprimirStatusCaixas(Caixa* caixas, int numCaixas);

#endif // SISTEMA_H