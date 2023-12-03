//FUNCTION.h
#ifndef fileManipulation_h
#define fileManipulation_h
#include "memoryAllocation.h"
#include <string.h>

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela);

//CARREGA DADOS DE UMA TABELA DE UM ARQUIVO
void carregarTabela(Tabela *tabela, char nome[TAMANHO_MAX_NOME]);

//LISTA DADOS DAS TABELAS DE UM ARQUIVO
void listarTabelas();

#endif