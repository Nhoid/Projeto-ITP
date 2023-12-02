#include "fileManipulation.h"
#include "tableManipulation.h" //FUNÇÕES DE MANIPULAÇÃO DE TABELA(POR CAUSA DO tipoParaString();)
#include "memoryAllocation.h" //FUNÇÕES DE MANIPULAÇÃO DE MEMORIA(POR CAUSA DA ESTRUTURA DE DADOS)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela) {
    //ITERAVEIS
    int i,j,k;

    if (tabela == NULL) {
        printf("A tabela é nula. Não é possível salvar.\n");
        return;
    }

    FILE *file = fopen("tabelas.itp", "a"); // Abre o arquivo para acréscimo
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar a tabela");
        return;
    }

    //ESCREVENDO TABELA

    //NOME DA TABELA
    fprintf(file, "\"Nomedatabela:\",\"%s\"\n", tabela->nome);
    //SAIDA: "Nomedatabela:","MIGUEL"

    //Separador de informações da tabela <-->
    fprintf(file, "<-->\n");

    //Informações da tabela
    fprintf(file, "\"Linhas:\",%d\n", tabela->linhas);
    fprintf(file, "\"Colunas:\",%d\n", tabela->colunas);

    //Tipos das colunas
    for(i = 0;i < tabela->colunas;i++){
        switch (tabela->tiposColuna[i]) {
                case STRING_TYPE:
                    fprintf(file, "1");
                    break;
                case INT_TYPE:
                    fprintf(file, "2");
                    break;
                case FLOAT_TYPE:
                    fprintf(file, "3");
                    break;
            }
        (i != tabela->colunas-1) ? fprintf(file, ",") : fprintf(file, "\n");
    }

    //Separador de informações da tabela <-->
    fprintf(file, "<-->\n");

    //Nome das colunas
    for(i = 0; i < tabela->colunas;i++){
        fprintf(file, "\"%s\"", tabela->nomeColuna[i]);
        //Se ainda tiver colunas digita "," senão pula a linha
        (i != tabela->colunas-1) ? fprintf(file, ",") : fprintf(file, "\n");
    }

    //Informações das celulas
    for(i = 0; i < tabela->linhas-1;i++){
        for(j = 0; j < tabela->colunas;j++){
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
            if(j != tabela->colunas-1){
                fprintf(file, ",");
            }
        }
        fprintf(file,"\n");
    }


    //Separador de tabela <--->
    fprintf(file, "<--->\n");

    fclose(file);
    /*
    MENSAGEM RETIRADA POR CONTA DA NATUREZA DA LIMPEZA DE TELA
    printf("Tabela '%s' salva com sucesso no arquivo 'tabelas.itp'.\n", tabela->nome);
    */
}


//ESTRUTURA DE UMA TABELA
/*
typedef struct {
    char nome[TAMANHO_MAX_NOME];
    char **nomeColuna;
    DataType *tiposColuna; // Primeira linha com tipos e dados
    Celula **table; // Restante das linhas com apenas dados
    int linhas, colunas;
} Tabela;
*/
