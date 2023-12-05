#include "memoryAllocation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAMANHO_MAX_NOME 50

//PRIMEIROS PASSOS PARA CRIAÇÃO DA TABELA
Tabela* alocarTabela(int linhas, int colunas)
{
    Tabela* newTable = (Tabela*) malloc(sizeof(Tabela));
    if (newTable == NULL) {
        printf("Falha na alocação de memória para a tabela.\n");
        return NULL;
    }

    newTable->linhas = linhas;
    newTable->colunas = colunas;

    // Alocando memória para os nomes das colunas e os tipos
    newTable->nomeColuna = (char**) malloc(colunas * sizeof(char*));
    newTable->tiposColuna = (DataType*) malloc(colunas * sizeof(DataType));
    if (newTable->nomeColuna == NULL || newTable->tiposColuna == NULL) {
        printf("Falha na alocação de memória para nomes ou tipos das colunas.\n");
        free(newTable);
        return NULL;
    }

    // Inicializa os ponteiros das colunas como NULL
    for (int i = 0; i < colunas; i++) {
        newTable->nomeColuna[i] = NULL;
    }

    // A tabela ainda não possui células alocadas neste ponto
    newTable->table = NULL;

    return newTable;
}

//ALOCA A MEMORIA DA TABLE
void alocarMemoriaTabela(Tabela* tabela) 
{
    if (tabela == NULL) return;

    tabela->table = (Celula**) malloc(tabela->linhas * sizeof(Celula*));
    if (tabela->table == NULL) {
        printf("Falha na alocação de memória para as células da tabela.\n");
        return;
    }

    for (int i = 0; i < tabela->linhas; i++) {
        tabela->table[i] = (Celula*) malloc(tabela->colunas * sizeof(Celula));
        if (tabela->table[i] == NULL) {
            printf("Falha na alocação de memória para as células da linha %d.\n", i);
            // Liberar memória alocada até agora
            for (int j = 0; j < i; j++) {
                free(tabela->table[j]);
            }
            free(tabela->table);
            return;
        }
    }
}

//CONSTRUTOR DE TABELA
Tabela* construtorTabela(int linhas, int colunas, char nome[]) 
{
    // Aloca memória para a estrutura Tabela
    Tabela* newTable = alocarTabela(linhas, colunas);
    if (newTable == NULL) {
        printf("Falha na alocação de memória para Tabela.\n");
        return NULL;
    }

    // Define o nome da tabela
    strncpy(newTable->nome, nome, TAMANHO_MAX_NOME);

    // Preenche informações sobre colunas e tipos
    char linhaEntrada[100];
    char nomeColuna[TAMANHO_MAX_NOME];
    int tipo;

    printf("A primeira coluna, por padrão, é a coluna da chave primária (tipo inteiro).\n");
    printf("Escreva o nome de cada Coluna seguido de seu tipo (Ex: NomeCliente;1):\n");
    printf("Texto = 1\nNúmero inteiro = 2\nNúmero com casa decimal = 3\n");

    for (int i = 0; i < colunas; i++) {
        if (i == 0) {
            printf("Nome da coluna %d (Chave primária): ", i + 1);
            fgets(linhaEntrada, 100, stdin);
            sscanf(linhaEntrada, "%49[^\n]", nomeColuna);
            newTable->nomeColuna[i] = strdup(nomeColuna);
            newTable->tiposColuna[i] = INT_TYPE;
        } else {
            printf("Nome e tipo da coluna %d: ", i + 1);
            fgets(linhaEntrada, 100, stdin);
            sscanf(linhaEntrada, "%49[^;];%d", nomeColuna, &tipo);
            newTable->nomeColuna[i] = strdup(nomeColuna);

            switch (tipo) {
                case 1: newTable->tiposColuna[i] = STRING_TYPE; break;
                case 2: newTable->tiposColuna[i] = INT_TYPE; break;
                case 3: newTable->tiposColuna[i] = FLOAT_TYPE; break;
                default:
                    printf("Tipo inválido. Atribuindo como texto.\n");
                    newTable->tiposColuna[i] = STRING_TYPE;
            }
        }
    }

    // Aloca memória para as células da tabela
    alocarMemoriaTabela(newTable);

    return newTable;
}

//AUMENTA A TABELA QUANDO NECESSARIO, AUMENTA UMA LINHA DE CADA VEZ
void aumentarTabela(Tabela *tabela) 
{
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
void liberarTabela(Tabela *tabela) 
{
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

QuadroDeAvisos *inicializarQuadroDeAvisos() {
    QuadroDeAvisos *dados = malloc(sizeof(QuadroDeAvisos));
    
    if (dados != NULL) {
        dados->linhaAviso = (int *)calloc(1, sizeof(int));
        *dados->linhaAviso = 0;

        dados->executando = (int *)calloc(1, sizeof(int));
        *dados->executando = 1;

        dados->aviso = (int *)calloc(1, sizeof(int));
        *dados->aviso = 0;

        dados->tabelaCarregada = (int *)calloc(1, sizeof(int));
        *dados->tabelaCarregada = 0;

        dados->salvo = (int *)calloc(1, sizeof(int));
        *dados->salvo = 0;

        dados->quadroAvisosAtivo = (int *)calloc(1, sizeof(int));
        *dados->quadroAvisosAtivo = 0;

        dados->invalido = (int *)calloc(1, sizeof(int));
        *dados->invalido = 0;
    }

    return dados;
}
