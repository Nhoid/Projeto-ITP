#ifndef memoryAllocation_H
#define memoryAllocation_H
#define TAMANHO_MAX_NOME 50
#include <stdlib.h>
#include <string.h>

//ESTRUTURA DE DADO DE CADA CELULA
typedef union 
{
    int intVal;
    char strVal[TAMANHO_MAX_NOME];
    float floatVal;
}Celula;

//RASTREIO DE TIPO DE DADO
typedef enum {
    INT_TYPE,
    STRING_TYPE,
    FLOAT_TYPE
} DataType;

//ESTRUTURA DA TABELA COMPLETA
typedef struct {
    char nome[TAMANHO_MAX_NOME];
    char **nomeColuna;
    DataType *tiposColuna; // Primeira linha com tipos e dados
    Celula **table; // Restante das linhas com apenas dados
    int linhas, colunas;
} Tabela;

//Construtor tabela
Tabela* criarTabela(int linhas, int colunas, char nome[]);

//AUMENTA A TABELA QUANDO NECESSARIO, AUMENTA UMA LINHA DE CADA VEZ
void aumentarTabela(Tabela *tabela);

//LIBERA A MEMORIA DE TABELAS
void liberarTabela(Tabela *tabela);

#endif