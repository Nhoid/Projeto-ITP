#include "memoryAllocation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANHO_MAX_NOME 50

//CONSTRUTOR DE TABELA
Tabela* criarTabela(int linhas, int colunas, char nome[]) {
    Tabela* newTable = malloc(sizeof(Tabela)); // Aloca memória para a nova tabela
    if (newTable == NULL) {
        printf("Falha na alocação de memória.\n");
        return NULL;
    }

    newTable->nomeColuna = malloc(colunas * sizeof(char*));
    newTable->tiposColuna = malloc(colunas * sizeof(DataType));

    char linhaEntrada[100];
    char nomeColuna[TAMANHO_MAX_NOME];
    int tipo;
    printf("A primeira coluna, por padrão, é a coluna da chave primária.\n");
    printf("E as chaves primarias são todas do tipo inteiro.\n");
    printf("Escreva o nome de cada Coluna seguido de seu tipo (Ex: NomeCliente;1):\n");
    printf("Texto = 1\nNúmero inteiro = 2\nNúmero com casa decimal = 3\n");

    for (int i = 0; i < colunas; i++) {
        if (i == 0)
        {
        printf("Nome da coluna %d(Chave primária): ", i + 1);
         fgets(linhaEntrada, 100, stdin);
        sscanf(linhaEntrada, "%49[^\n]", nomeColuna);
        newTable->nomeColuna[i] = strdup(nomeColuna);
        newTable->tiposColuna[i] = INT_TYPE;
        }else{
        printf("Nome e tipo da coluna %d: ", i + 1);
         fgets(linhaEntrada, 100, stdin);
        sscanf(linhaEntrada, "%49[^;];%d", nomeColuna, &tipo);
        newTable->nomeColuna[i] = strdup(nomeColuna);

        switch (tipo) {
            case 1:
                newTable->tiposColuna[i] = STRING_TYPE;
                break;
            case 2:
                newTable->tiposColuna[i] = INT_TYPE;
                break;
            case 3:
                newTable->tiposColuna[i] = FLOAT_TYPE;
                break;
            default:
                printf("Tipo inválido. Atribuindo como texto.\n");
                newTable->tiposColuna[i] = STRING_TYPE;
        }}
    }

    newTable->table = malloc(linhas * sizeof(Celula*));
    for (int i = 0; i < linhas; i++) {
        newTable->table[i] = malloc(colunas * sizeof(Celula));
    }

    newTable->linhas = linhas;
    newTable->colunas = colunas;
    strcpy(newTable->nome, nome);

    return newTable;
}

//AUMENTA A TABELA QUANDO NECESSARIO, AUMENTA UMA LINHA DE CADA VEZ
void aumentarTabela(Tabela *tabela) {
    int novoTamanho = tabela->linhas + 1; // Calcula o novo tamanho da tabela
    Celula **novaTable = realloc(tabela->table, novoTamanho * sizeof(Celula*)); // Realoca com o novo tamanho
    if (novaTable == NULL) {
        printf("Erro ao adicionar nova linha\n");
        return;
    }

    novaTable[tabela->linhas] = malloc(tabela->colunas * sizeof(Celula)); // Aloca a nova linha
    if (novaTable[tabela->linhas] == NULL) {
        printf("Erro ao alocar memória para nova linha\n");
        return;
    }

    tabela->table = novaTable; // Atualiza o ponteiro da tabela
    tabela->linhas = novoTamanho; // Atualiza o contador de linhas
}

//LIBERA A MEMORIA DE TABELAS
void liberarTabela(Tabela *tabela) {
    // Primeiro, liberar a memória de cada nome de coluna
    for (int i = 0; i < tabela->colunas; i++) {
        free(tabela->nomeColuna[i]);
    }
    // Agora, liberar o array de nomes de colunas
    free(tabela->nomeColuna);
    free(tabela->tiposColuna);

    // Em seguida, liberar a memória de cada célula da tabela
    for (int i = 0; i < tabela->linhas - 1; i++) {
        free(tabela->table[i]);
    }
    free(tabela->table);
}