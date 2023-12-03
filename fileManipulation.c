#include "fileManipulation.h"
#include "tableManipulation.h" //FUNÇÕES DE MANIPULAÇÃO DE TABELA(POR CAUSA DO tipoParaString();)
#include "memoryAllocation.h" //FUNÇÕES DE MANIPULAÇÃO DE MEMORIA(POR CAUSA DA ESTRUTURA DE DADOS)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>



void removerTabela(Tabela *tabela) {
    FILE *arquivoEntrada, *arquivoSaida;
    char linha[1000];

    char nomeProcurado[100]; 
    strcpy(nomeProcurado, tabela->nome);

    // Abrir o arquivo de entrada
    arquivoEntrada = fopen("tabelas.itp", "r+");
    if (arquivoEntrada == NULL) {
        perror("Erro ao abrir o arquivo de entrada");
        return;
    }

    // Abrir um novo arquivo de saída
    arquivoSaida = fopen("novoarquivo.txt", "w");
    if (arquivoSaida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        fclose(arquivoEntrada);
        return;
    }

    // Copiar linhas até encontrar a tabela com o nome desejado
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        if (strstr(linha, nomeProcurado) != NULL) {
            // Encontrou a tabela com o nome desejado, parar de copiar
            break;
        }
        fputs(linha, arquivoSaida);
    }

    // Copiar linhas após a tabela com o nome desejado
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        if (strstr(linha, "<--->") != NULL) {
            // Encontrou a marca "<--->", parar de copiar
            break;
        }
    }

    // Copiar o restante do arquivo para o arquivo de saída
    while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
        fputs(linha, arquivoSaida);
    }

    // Fechar os arquivos
    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    // Remover o arquivo original
    remove("tabelas.itp");

    // Renomear o novo arquivo para o nome original
    rename("novoarquivo.txt", "tabelas.itp");
    remove("novoarquivo.txt");
}

//SALVA OS DADOS DE UMA TABELA EM UM ARQUIVO
void salvarArquivo(Tabela *tabela) {
    // ITERAVEIS
    int i, j, k;

    removerTabela(tabela);

    char linha[9999];
    long posicaoAtual = 0; // Inicializa a posição atual do ponteiro do arquivo

    if (tabela == NULL) {
        printf("A tabela é nula. Não é possível salvar.\n");
        return;
    }

    FILE *file = fopen("tabelas.itp", "a+"); // Abre o arquivo para leitura e escrita
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar a tabela");
        return;
    }


    //ESCREVENDO TABELA

    //NOME DA TABELA
    fprintf(file, "Nomedatabela: %s\n", tabela->nome);
    //SAIDA: "Nomedatabela:","MIGUEL"

    //Separador de informações da tabela <-->
    fprintf(file, "<-->\n");

    //Informações da tabela
    fprintf(file, "Linhas: %d\n", tabela->linhas);
    fprintf(file, "Colunas: %d\n", tabela->colunas);

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
        fprintf(file, "%s", tabela->nomeColuna[i]);
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
                    fprintf(file, "%s", tabela->table[i][j].strVal);
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
    printf("Tabela '%s' salva com sucesso no arquivo 'tabelas.itp'.\n", tabela->nome);
}




void listarTabelas() {
    FILE *file = fopen("tabelas.itp", "r+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar a tabela");
        return;
    }

    char linha[9999];
    long posicaoAtual = 0; // Inicializa a posição atual do ponteiro do arquivo

    // Lê cada linha do arquivo
    while (fgets(linha, sizeof(linha), file) != NULL) {
        // Remove o caractere de nova linha
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém "Nomedatabela:"
        if (strstr(linha, "Nomedatabela:") != NULL) {
            // Encontrou a linha, agora vamos extrair o nome
            char *posicaoNome = strchr(linha, ':'); // Encontra a posição do caractere ':' na linha
            if (posicaoNome != NULL) {
                // Incrementa a posição para ignorar o ':'
                posicaoNome++;

                // Remove espaços em branco no início, se houver
                while (*posicaoNome == ' ') {
                    posicaoNome++;
                }

                printf("Tabela encontrada: %s\n", posicaoNome);
            }
        }
    }

    fclose(file);
    int p = 1;
    printf("Digite 0 para fechar a lista.\n"); //Segurar a lista aberta
    while(p != 0)
    {
        scanf("%d", &p);
    }

}


void carregarTabela(Tabela *tabela, char nomeProcurado[TAMANHO_MAX_NOME]) {
    FILE *file = fopen("tabelas.itp", "r+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo para salvar a tabela");
        return;
    }

    char linha[9999];
    long posicaoAtual = 0; // Inicializa a posição atual do ponteiro do arquivo

    while (fgets(linha, sizeof(linha), file) != NULL) {
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha contém o nome desejado
        if (strstr(linha, nomeProcurado) != NULL) {
            printf("Nome encontrado: %s\n", nomeProcurado);
            fseek(file, posicaoAtual, SEEK_SET); // Move o ponteiro para a posição correta
            printf("Ponteiro do arquivo movido para a posição: %ld\n", posicaoAtual);

            // Leitura do restante das informações da tabela
            fscanf(file, "<-->\nLinhas: %d\nColunas: %d\n", &tabela->linhas, &tabela->colunas);

            // Alocar memória para as estruturas da tabela
            tabela->nomeColuna = malloc(tabela->colunas * sizeof(char *));
            tabela->tiposColuna = malloc(tabela->colunas * sizeof(DataType));
            tabela->table = malloc(tabela->linhas * sizeof(Celula *));
            for (int i = 0; i < tabela->linhas; i++) {
                tabela->table[i] = malloc(tabela->colunas * sizeof(Celula));
            }

            // Leitura dos nomes das colunas
            fscanf(file, "<-->\n");
            tabela->nomeColuna[0] = malloc(TAMANHO_MAX_NOME);
            for (int i = 0; i < tabela->colunas; i++) {
                fscanf(file, "%[^,],", tabela->nomeColuna[i]);
                tabela->nomeColuna[i + 1] = malloc(TAMANHO_MAX_NOME);
            }

            // Leitura dos tipos de dados das colunas
            for (int i = 0; i < tabela->colunas; i++) {
                char tipo[20];
                fscanf(file, "%[^,],", tipo);
                if (strcmp(tipo, "int") == 0) {
                    tabela->tiposColuna[i] = INT_TYPE;
                } else if (strcmp(tipo, "string") == 0) {
                    tabela->tiposColuna[i] = STRING_TYPE;
                } else if (strcmp(tipo, "float") == 0) {
                    tabela->tiposColuna[i] = FLOAT_TYPE;
                }
            }

            // Leitura dos dados da tabela
            for (int i = 0; i < tabela->linhas; i++) {
                fscanf(file, "<-->\n");
                for (int j = 0; j < tabela->colunas; j++) {
                    switch (tabela->tiposColuna[j]) {
                        case INT_TYPE:
                            fscanf(file, "%d,", &tabela->table[i][j].intVal);
                            break;
                        case STRING_TYPE:
                            fscanf(file, "%[^,],", tabela->table[i][j].strVal);
                            break;
                        case FLOAT_TYPE:
                            fscanf(file, "%f,", &tabela->table[i][j].floatVal);
                            break;
                    }
                }
            }

            fclose(file);
            return;
        }

        posicaoAtual = ftell(file); // Atualiza a posição atual do ponteiro do arquivo
    }

    fclose(file);
    printf("Tabela Não Encontrada.\n");
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
