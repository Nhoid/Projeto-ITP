//FUNCTION.h
#ifndef fileManipulation_h
#define fileManipulation_h
#include "memoryAllocation.h"
#include <string.h>

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela);

//CARREGA DADOS DE UMA TABELA DE UM ARQUIVO
Tabela* carregarTabela(const char* nomeTabela);

//LISTA DADOS DAS TABELAS DE UM ARQUIVO
void listarTabelas();

//EXCLUI TABELA DE UM ARQUIVO
void removerTabela();

#endif