#include "fileManipulation.h"
#include "tableManipulation.h" //FUNÇÕES DE MANIPULAÇÃO DE TABELA(POR CAUSA DO tipoParaString();)
#include "memoryAllocation.h" //FUNÇÕES DE MANIPULAÇÃO DE MEMORIA(POR CAUSA DA ESTRUTURA DE DADOS)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>



void removerTabela(Tabela *tabela) 
{
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
void salvarArquivo(Tabela *tabela) 
{
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




void listarTabelas() 
{
    FILE *file = fopen("tabelas.itp", "r+");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    char linha[1024];
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


Tabela* carregarTabela(const char* nomeTabela) {
    FILE* arquivo = fopen("tabelas.itp", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return NULL;
    }
    char vacuo[1024];
    char linha[1024];
    bool encontrouTabela = false;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Nomedatabela:") && strstr(linha, nomeTabela)) {
            encontrouTabela = true;
            break;
        }
    }

    if (!encontrouTabela) {
        printf("Tabela '%s' não encontrada no arquivo '%s'.\n", nomeTabela, "tabelas.itp");
        fclose(arquivo);
        return NULL;
    }
    fgets(vacuo, sizeof(vacuo), arquivo); // limpa o separador
   //fgets(linha, sizeof(linha), arquivo);

    int linhas, colunas;
    if (fscanf(arquivo, "Linhas: %d\nColunas: %d\n", &linhas, &colunas) != 2) {
        fprintf(stderr, "Erro na leitura das dimensões da tabela.\n");
        fclose(arquivo);
        return NULL;
    }
    Tabela* tabela = alocarTabela(linhas, colunas);
    alocarMemoriaTabela(tabela);

    strncpy(tabela->nome, nomeTabela, TAMANHO_MAX_NOME - 1);
    tabela->nome[TAMANHO_MAX_NOME - 1] = '\0';

    fgets(linha, sizeof(linha), arquivo); // Lê a linha dos tipos

    char* token = strtok(linha, ",");
    for (int i = 0; i < colunas; i++) {
        if (token == NULL) {
            fprintf(stderr, "Erro na leitura dos tipos de colunas.\n");
            fclose(arquivo);
            return NULL;
        }
        int tipo = atoi(token);
        switch(tipo)
        {
        case 1: tabela->tiposColuna[i] = STRING_TYPE; break;
        case 2: tabela->tiposColuna[i] = INT_TYPE; break;
        case 3: tabela->tiposColuna[i] = FLOAT_TYPE; break;
        default: tabela->tiposColuna[i] = STRING_TYPE; break;
        }
        token = strtok(NULL, ",");
    }
    fgets(vacuo, sizeof(vacuo), arquivo); // limpa o separador
    fgets(linha, sizeof(linha), arquivo); // Lê a linha dos nomes das colunas

    token = strtok(linha, ",");
    for (int i = 0; i < colunas; i++) {
        if (token == NULL) {
            fprintf(stderr, "Erro na leitura dos nomes das colunas.\n");
            fclose(arquivo);
            return NULL;
        }
        token[strcspn(token, "\n")] = '\0';
        tabela->nomeColuna[i] = strdup(token);
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < linhas-1; i++) {
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fprintf(stderr, "Erro ao ler dados da tabela.\n");
        fclose(arquivo);
        return NULL;
    }
    // Remova ou mova esta linha para antes do strtok se for apenas para depuração
    char* token = strtok(linha, ",");
    for (int j = 0; j < colunas; j++) {
        if (token == NULL) {
            fprintf(stderr, "Erro na leitura dos dados da tabela.\n");

            fclose(arquivo);
            return NULL;
        }
        switch (tabela->tiposColuna[j]) {
            case STRING_TYPE:
                token[strcspn(token, "\n")] = '\0';
                strncpy(tabela->table[i][j].strVal, token, TAMANHO_MAX_NOME - 1);
                tabela->table[i][j].strVal[TAMANHO_MAX_NOME - 1] = '\0';
                break;
            case INT_TYPE:
                tabela->table[i][j].intVal = atoi(token);
                break;
            case FLOAT_TYPE:
                tabela->table[i][j].floatVal = atof(token);
                break;
        }
        token = strtok(NULL, ",");
    }
}
    fclose(arquivo);
    return tabela;
}