#ifndef tableManipulation_h
#define tableManipulation_h
#include "memoryAllocation.h"
#include <stdlib.h>
#include <stdbool.h>

//compara valores inteiros para pesquisa
bool comparaInt(int valorTabela, int valorPesquisado, char operador);

// Função que compara valores float de acordo com o operador fornecido
bool comparaFloat(float valorTabela, float valorPesquisado, char operador);

// Função que compara strings de acordo com o operador fornecido
bool comparaString(const char* valorTabela, const char* valorPesquisado, char operador);

//VERIFICA SE JÁ TEM DETERMINADA CHAVE PRIMÁRIA REGISTRADA NA TABELA
bool verificarChave(Tabela *tabela, int chave);

//CALCULAR PROPORÇÃO DA TABELA
void calcularLarguraColunas(Tabela *tabela, int *larguras);

//CONVERTE O TIPO DE DADO DAS CELULAS PARA TEXTO LEGIVEL
const char* tipoParaString(DataType tipo);

//REMOVE LINHA PELA POR CHAVE PRIMARIA
void removerLinhaPorChave(Tabela *tabela, int chavePrimaria);

//FAZ PESQUISA DE VALOR NA TABELA
void pesquisaValor(Tabela *tabela);

//PRINTAR A TABELA
void mostrarTabela(Tabela *tabela);

//PEGAR ENTRADA DO USUARIO
void PegarDados(Tabela *tabela);

#endif