//FUNCTION.h
#ifndef FUNCTION_H
#define FUNCTION_H
#define TAMANHO_MAX_NOME 50
#include <stdbool.h>
//lempa a tela
void limparTela();
typedef union 
{
    int intVal;
    char strVal[TAMANHO_MAX_NOME];
    float floatVal;
}Celula;

//TIPOS DE REGISTRO TIPO DE CADA CELULA
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

//compara valores inteiros para pesquisa
bool comparaInt(int valorTabela, int valorPesquisado, char operador);

// Função que compara valores float de acordo com o operador fornecido
bool comparaFloat(float valorTabela, float valorPesquisado, char operador);

// Função que compara strings de acordo com o operador fornecido
bool comparaString(const char* valorTabela, const char* valorPesquisado, char operador);

//VERIFICA SE JÁ TEM DETERMINADA CHAVE PRIMÁRIA REGISTRADA NA TABELA
bool verificarChave(Tabela *tabela, int chave);

//AUMENTA A TABELA QUANDO NECESSARIO, AUMENTA UMA LINHA DE CADA VEZ
void aumentarTabela(Tabela *tabela);

//LIBERA A MEMORIA DE TABELAS
void liberarTabela(Tabela *tabela);

//REMOVE LINHA PELA POR CHAVE PRIMARIA
void removerLinhaPorChave(Tabela *tabela, int chavePrimaria);

//CALCULAR PROPORÇÃO DA TABELA
void calcularLarguraColunas(Tabela *tabela, int *larguras);

//FAZ PESQUISA DE VALOR NA TABELA
void pesquisaValor(Tabela *tabela);

//PRINTAR A TABELA
void mostrarTabela(Tabela *tabela);

//PEGAR ENTRADA DO USUARIO
void PegarDados(Tabela *tabela);

//CONVERTE O TIPO DE DADO DAS CELULAS PARA TEXTO LEGIVEL
const char* tipoParaString(DataType tipo);

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela, const char *nomeArquivo);
#endif