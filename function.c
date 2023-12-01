#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
//limpa a tela
void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
//CONSTRUTOR DE TABELA
Tabela* criarTabela(int linhas, int colunas, char nome[]) {
    Tabela* newTable = malloc(sizeof(Tabela)); // Aloca memória para a nova tabela
    if (newTable == NULL) {
        printf("Falha na alocação de memória.\n");
        return NULL;
    }

    newTable->nomeColuna = malloc(colunas * sizeof(char*));
    newTable->tiposColuna = malloc(colunas * sizeof(DataType));

    char linhaEntrada[100];
    char nomeColuna[TAMANHO_MAX_NOME];
    int tipo;
    printf("A primeira coluna, por padrão, é a coluna da chave primária.\n");
    printf("E as chaves primarias são todas do tipo inteiro.\n");
    printf("Escreva o nome de cada Coluna seguido de seu tipo (Ex: NomeCliente;1):\n");
    printf("Texto = 1\nNúmero inteiro = 2\nNúmero com casa decimal = 3\n");

    for (int i = 0; i < colunas; i++) {
        if (i == 0)
        {
        printf("Nome da coluna %d(Chave primária): ", i + 1);
         fgets(linhaEntrada, 100, stdin);
        sscanf(linhaEntrada, "%49[^\n]", nomeColuna);
        newTable->nomeColuna[i] = strdup(nomeColuna);
        newTable->tiposColuna[i] = INT_TYPE;
        }else{
        printf("Nome e tipo da coluna %d: ", i + 1);
         fgets(linhaEntrada, 100, stdin);
        sscanf(linhaEntrada, "%49[^;];%d", nomeColuna, &tipo);
        newTable->nomeColuna[i] = strdup(nomeColuna);

        switch (tipo) {
            case 1:
                newTable->tiposColuna[i] = STRING_TYPE;
                break;
            case 2:
                newTable->tiposColuna[i] = INT_TYPE;
                break;
            case 3:
                newTable->tiposColuna[i] = FLOAT_TYPE;
                break;
            default:
                printf("Tipo inválido. Atribuindo como texto.\n");
                newTable->tiposColuna[i] = STRING_TYPE;
        }}
    }

    newTable->table = malloc(linhas * sizeof(Celula*));
    for (int i = 0; i < linhas; i++) {
        newTable->table[i] = malloc(colunas * sizeof(Celula));
    }

    newTable->linhas = linhas;
    newTable->colunas = colunas;
    strcpy(newTable->nome, nome);

    return newTable;
}

// Função que compara valores inteiros de acordo com o operador fornecido
bool comparaInt(int valorTabela, int valorPesquisado, char operador) {
    switch (operador) {
        case '>': return valorTabela > valorPesquisado;
        case '<': return valorTabela < valorPesquisado;
        case '=': return valorTabela == valorPesquisado;
        case 'G': return valorTabela >= valorPesquisado; // Maior ou igual
        case 'L': return valorTabela <= valorPesquisado; // Menor ou igual
        default: return false;
    }
}

// Função que compara valores float de acordo com o operador fornecido
bool comparaFloat(float valorTabela, float valorPesquisado, char operador) {
    switch (operador) {
        case '>': return valorTabela > valorPesquisado;
        case '<': return valorTabela < valorPesquisado;
        case '=': return valorTabela == valorPesquisado;
        case 'G': return valorTabela >= valorPesquisado;
        case 'L': return valorTabela <= valorPesquisado;
        default: return false;
    }
}

// Função que compara strings de acordo com o operador fornecido
bool comparaString(const char* valorTabela, const char* valorPesquisado, char operador) {
    int cmp = strcmp(valorTabela, valorPesquisado);
    switch (operador) {
        case '>': return cmp > 0;
        case '<': return cmp < 0;
        case '=': return cmp == 0;
        case 'G': return cmp >= 0;
        case 'L': return cmp <= 0;
        default: return false;
    }
}

//VERIFICA SE JÁ TEM DETERMINADA CHAVE PRIMÁRIA REGISTRADA NA TABELA;
bool verificarChave(Tabela *tabela, int chave)
{
    for (int i = 0; i < tabela->linhas; i++)
    {
        if (tabela->table[i][0].intVal==chave)
        {
            return false;
        }
    }
    return true;
} 

//AUMENTA A TABELA QUANDO NECESSARIO, AUMENTA UMA LINHA DE CADA VEZ
void aumentarTabela(Tabela *tabela) {
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
void liberarTabela(Tabela *tabela) {
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

//REMOVE LINHA PELA POR CHAVE PRIMARIA
void removerLinhaPorChave(Tabela *tabela, int chavePrimaria) {
    int linhaParaRemover = -1;

    // Encontrar a linha com a chave primária especificada
    for (int i = 0; i < tabela->linhas; i++) {
        if (tabela->table[i][0].intVal == chavePrimaria) {
            linhaParaRemover = i;
            break;
        }
    }

    // Se a linha foi encontrada, removê-la
    if (linhaParaRemover != -1) {
        // Libera a memória da linha específica
        free(tabela->table[linhaParaRemover]);

        // Desloca todas as linhas seguintes para cima no array
        for (int i = linhaParaRemover; i < tabela->linhas - 1; i++) {
            tabela->table[i] = tabela->table[i + 1];
        }

        // Diminui o contador de linhas
        tabela->linhas--;

        // Realoca o array da tabela para ter uma linha a menos
        Celula **novaTable = realloc(tabela->table, tabela->linhas * sizeof(Celula*));
        if (novaTable != NULL || tabela->linhas == 0) {
            tabela->table = novaTable;
        } else {
            // Se a realloc falhar e a contagem de linhas não for zero, temos um erro grave
            printf("Erro ao realocar memória após remover linha.\n");
        }
    } else {
        printf("Chave primária não encontrada.\n");
    }
}

//CALCULAR PROPORÇÃO DA TABELA
void calcularLarguraColunas(Tabela *tabela, int *larguras) {
    for (int j = 0; j < tabela->colunas; j++) {
        larguras[j] = strlen(tabela->nomeColuna[j]); // Inicializa com o tamanho do nome da coluna

        for (int i = 0; i < tabela->linhas - 1; i++) {
            int tamanhoCelula = 0;
            switch (tabela->tiposColuna[j]) {
                case INT_TYPE:
                    tamanhoCelula = snprintf(NULL, 0, "%d", tabela->table[i][j].intVal);
                    break;
                case STRING_TYPE:
                    tamanhoCelula = strlen(tabela->table[i][j].strVal);
                    break;
                case FLOAT_TYPE:
                    tamanhoCelula = snprintf(NULL, 0, "%.2f", tabela->table[i][j].floatVal);
                    break;
            }
            if (tamanhoCelula > larguras[j]) {
                larguras[j] = tamanhoCelula;
            }
        }
    }
}

//FAZ PESQUISA DE VALOR NA TABELA
void pesquisaValor(Tabela *tabela) {
    char nomeColunaPesquisa[TAMANHO_MAX_NOME];
    char operador;
    char valorPesquisa[100];
    int indiceColuna = -1;
    int larguras[tabela->colunas];
    memset(larguras, 0, sizeof(larguras));

    // Mostrar o nome de todas as colunas
    printf("Colunas disponíveis:\n");
    for (int i = 0; i < tabela->colunas; i++) {
        printf("%s\n", tabela->nomeColuna[i]);
    }

    // Pergunta ao usuário o nome da coluna para pesquisa
    printf("Digite o nome da coluna para a pesquisa: ");
    fgets(nomeColunaPesquisa, sizeof(nomeColunaPesquisa), stdin);
    nomeColunaPesquisa[strcspn(nomeColunaPesquisa, "\n")] = 0; // Remove a quebra de linha

    // Encontra o índice da coluna pelo nome
    for (int i = 0; i < tabela->colunas; i++) {
        if (strcmp(tabela->nomeColuna[i], nomeColunaPesquisa) == 0) {
            indiceColuna = i;
            break;
        }
    }
    if (indiceColuna == -1) {
        printf("Coluna não encontrada.\n");
        return;
    }

    // Pergunta o tipo de comparação
    printf("Digite o tipo de comparação desejada (>, <, =, G para >=, L para <=): ");
    operador = getchar();
    getchar(); // Limpa o buffer de entrada

    // Pergunta o valor a ser pesquisado
    printf("Digite o valor para pesquisa: ");
    fgets(valorPesquisa, sizeof(valorPesquisa), stdin);
    valorPesquisa[strcspn(valorPesquisa, "\n")] = 0; // Remove a quebra de linha

    // Prepara as larguras das colunas para o cabeçalho
    calcularLarguraColunas(tabela, larguras);

    // Imprime o cabeçalho da tabela
    for (int j = 0; j < tabela->colunas; j++) {
        printf("| %-*s ", larguras[j], tabela->nomeColuna[j]);
    }
    printf("|\n");

    // Linha separadora
    for (int j = 0; j < tabela->colunas; j++) {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) {
            printf("-");
        }
    }
    printf("+\n");

    // Realiza a pesquisa e imprime os resultados
    for (int i = 0; i < tabela->linhas; i++) {
        bool match = false;
        // A comparação é feita apenas com base no tipo da coluna
        switch (tabela->tiposColuna[indiceColuna]) {
            case INT_TYPE:
                match = comparaInt(tabela->table[i][indiceColuna].intVal, atoi(valorPesquisa), operador);
                break;
            case FLOAT_TYPE:
                match = comparaFloat(tabela->table[i][indiceColuna].floatVal, atof(valorPesquisa), operador);
                break;
            case STRING_TYPE:
                match = comparaString(tabela->table[i][indiceColuna].strVal, valorPesquisa, operador);
                break;
        }
        if (match) {
            // Imprime a linha completa que corresponde à pesquisa
            for (int j = 0; j < tabela->colunas; j++) {
                switch (tabela->tiposColuna[j]) {
                    case INT_TYPE:
                        printf("| %-*d ", larguras[j], tabela->table[i][j].intVal);
                        break;
                    case STRING_TYPE:
                        printf("| %-*s ", larguras[j], tabela->table[i][j].strVal);
                        break;
                    case FLOAT_TYPE:
                        printf("| %-*.2f ", larguras[j], tabela->table[i][j].floatVal);
                        break;
                }
            }
            printf("|\n");
        }
    }

    // Linha final
    for (int j = 0; j < tabela->colunas; j++) {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) {
            printf("-");
        }
    }
    printf("+\n");

    printf("Digite 0 para voltar ao menu.\n");
    scanf("%d", &indiceColuna); // Reutiliza a variável para a entrada do usuário
    getchar(); // Limpa o buffer de entrada
}


//PRINTAR A TABELA
void mostrarTabela(Tabela *tabela) {
    int p = 1;
    if (tabela->linhas == 0) {
        printf("A tabela está vazia.\n");
        return;
    }

    int larguras[tabela->colunas];
    calcularLarguraColunas(tabela, larguras);

    // Imprime o cabeçalho da tabela
    for (int j = 0; j < tabela->colunas; j++) {
        printf("| %-*s ", larguras[j], tabela->nomeColuna[j]);
    }
    printf("|\n");

    // Linha separadora
    for (int j = 0; j < tabela->colunas; j++) {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) {
            printf("-");
        }
    }
    printf("+\n");

    // Imprime os dados da tabela
    for (int i = 0; i < tabela->linhas-1; i++) {
        for (int j = 0; j < tabela->colunas; j++) {
            switch (tabela->tiposColuna[j]) {
                case INT_TYPE:
                    printf("| %-*d ", larguras[j], tabela->table[i][j].intVal);
                    break;
                case STRING_TYPE:
                    printf("| %-*s ", larguras[j], tabela->table[i][j].strVal);
                    break;
                case FLOAT_TYPE:
                    printf("| %-*.2f ", larguras[j], tabela->table[i][j].floatVal);
                    break;
            }
        }
        printf("|\n");
    }
    printf("Digite 0 para voltar ao menu\n");
    while(p != 0)
    {
        scanf("%d", &p);
    }
}


//PEGAR ENTRADA DO USUARIO
void PegarDados(Tabela *tabela) {
    char buffer[100]; // Buffer para entrada do usuário
    bool continuar = true, chaveValida;
    int linhaAtual = tabela->linhas - 1; // Ajustado para corresponder ao índice correto
    int chave, resultado;
    char *endPtr;
    while (continuar) {
        // Se já existem linhas, aloca uma nova linha
        if (linhaAtual >= 0) {
            aumentarTabela(tabela);
        }

        printf("Inserindo dados para a linha %d:\n", linhaAtual + 1);
        //FAZ A VERIFICAÇÃO SE A CHAVE PRIMARIA INSERIDA JA EXISTE NA TABELA
        do {
            printf("Digite o valor para a chave primária: ");
            fgets(buffer, sizeof(buffer), stdin);
            if (strcmp(buffer, "Fim\n") == 0) {
                continuar = false;
                chaveValida = true;
                break;
            }

            chave = (int) strtol(buffer, &endPtr, 10);
            if (*endPtr != '\n' && *endPtr != '\0') {
                printf("Tipo de chave inválida, a chave precisa ser um número inteiro puro.\n");
                continue;
            }

            chaveValida = verificarChave(tabela, chave);
            if (!chaveValida) {
                printf("Chave primária já existe. Por favor, insira uma chave primária única.\n");
            }
        } while (!chaveValida);
        if (!continuar)
        {
            break;
        }
        tabela->table[tabela->linhas-2][0].intVal = chave;
        for (int j = 1; j < tabela->colunas; j++) {
            printf("Digite o valor para a coluna '%s': ", tabela->nomeColuna[j]);
            fgets(buffer, 100, stdin); // Lê a entrada do usuário
            // Verifica se o usuário digitou 'Fim'
            if (strcmp(buffer, "Fim\n") == 0) {
                continuar = false;
                break;
            }

            // Processa a entrada com base no tipo de dado da coluna
            switch (tabela->tiposColuna[j]) {
                case INT_TYPE:
                    tabela->table[linhaAtual][j].intVal = atoi(buffer);
                    break;
                case STRING_TYPE:
                    strncpy(tabela->table[linhaAtual][j].strVal, buffer, TAMANHO_MAX_NOME - 1);
                    tabela->table[linhaAtual][j].strVal[strcspn(tabela->table[linhaAtual][j].strVal, "\n")] = 0; // Remove a quebra de linha
                    break;
                case FLOAT_TYPE:
                    tabela->table[linhaAtual][j].floatVal = atof(buffer);
                    break;
            }
        }

        if (continuar) {
            linhaAtual++;
        }
    }

    // Ajusta o tamanho final da tabela, se necessário
    if (linhaAtual == -1) {
        // Se nenhuma linha foi adicionada, não ajusta o tamanho
        tabela->linhas = 0;
    } else {
        tabela->linhas = linhaAtual+1;
    }
}
//CONVERTE O TIPO DE DADO DAS CELULAS PARA TEXTO LEGIVEL
const char* tipoParaString(DataType tipo) {
    switch (tipo) {
        case INT_TYPE:
            return "Inteiro";
        case STRING_TYPE:
            return "String";
        case FLOAT_TYPE:
            return "Flutuante";
        default:
            return "Desconhecido";
    }
}
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