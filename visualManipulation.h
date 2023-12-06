#ifndef visualManipulation_h
#define visualManipulation_h
#include "memoryAllocation.h"
#include <stdbool.h>

void tabelaSelecionada(Tabela *tabela); //MOSTRA DINAMICAMENTE QUAL TABELA ESTA SELECIONADA NA LINHA DA OPÇÃO SAIR

void quadroDeAvisos(Tabela *tabela, QuadroDeAvisos *quadrodeavisos); //GERENCIA O QUADRO DE AVISOS

void interfaceCriarTabela(Tabela **lambda);

#endif