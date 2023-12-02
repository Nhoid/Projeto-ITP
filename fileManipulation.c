#include "fileManipulation.h"
#include "tableManipulation.h" //FUNÇÕES DE MANIPULAÇÃO DE TABELA(POR CAUSA DO tipoParaString();)
#include "memoryAllocation.h" //FUNÇÕES DE MANIPULAÇÃO DE MEMORIA(POR CAUSA DA ESTRUTURA DE DADOS)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela, const char *nomeArquivo) {
    if (tabela == NULL) {
        printf("A tabela é nula. Não é possível salvar.\n");
        return;
    }

    FILE *file = fopen(nomeArquivo, "a"); // Abre o arquivo para acréscimo
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar a tabela");
        return;
    }

    fprintf(file, "Início da Tabela: %s\n", tabela->nome);
    // Escrevendo os nomes e os tipos das colunas
    for (int j = 0; j < tabela->colunas; j++) {
        fprintf(file, "%s(%s)", tabela->nomeColuna[j], tipoParaString(tabela->tiposColuna[j])); // Escreve o nome e o tipo da coluna
        if (j < tabela->colunas - 1) fprintf(file, ","); // Separador
    }
    fprintf(file, "\n");

    // Escrevendo os dados das linhas
    for (int i = 0; i < tabela->linhas; i++) {
        for (int j = 0; j < tabela->colunas; j++) {
            switch (tabela->tiposColuna[j]) {
                case INT_TYPE:
                    fprintf(file, "%d", tabela->table[i][j].intVal);
                    break;
                case STRING_TYPE:
                    fprintf(file, "\"%s\"", tabela->table[i][j].strVal);
                    break;
                case FLOAT_TYPE:
                    fprintf(file, "%f", tabela->table[i][j].floatVal);
                    break;
            }
            if (j < tabela->colunas - 1) fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "Fim da Tabela: %s\n", tabela->nome); // Marca o fim da tabela
    fclose(file);
    printf("Tabela '%s' salva com sucesso no arquivo '%s'.\n", tabela->nome, nomeArquivo);
}