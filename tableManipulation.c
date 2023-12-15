#include "tableManipulation.h"
#include "memoryAllocation.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// Função que compara valores inteiros de acordo com o operador fornecido
bool comparaInt(int valorTabela, int valorPesquisado, char operador) 
{
    switch (operador) 
    {
        case '>': return valorTabela > valorPesquisado;
        case '<': return valorTabela < valorPesquisado;
        case '=': return valorTabela == valorPesquisado;
        case 'G': return valorTabela >= valorPesquisado; // Maior ou igual
        case 'L': return valorTabela <= valorPesquisado; // Menor ou igual
        default: return false;
    }
}

// Função que compara valores float de acordo com o operador fornecido
bool comparaFloat(float valorTabela, float valorPesquisado, char operador) 
{
    switch (operador) 
    {
        case '>': return valorTabela > valorPesquisado;
        case '<': return valorTabela < valorPesquisado;
        case '=': return valorTabela == valorPesquisado;
        case 'G': return valorTabela >= valorPesquisado;
        case 'L': return valorTabela <= valorPesquisado;
        default: return false;
    }
}

// Função que compara strings de acordo com o operador fornecido
bool comparaString(const char* valorTabela, const char* valorPesquisado, char operador) 
{
    int cmp = strcmp(valorTabela, valorPesquisado);
    switch (operador)
     {
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

//REMOVE ACENTO DA LETRA QUE FOI DADO COMO ENTRADA
char remove_acento(char c, int *tamanho) 
{
    // Lista de caracteres acentuados e seus equivalentes não acentuados
    const char *com_acento = "áéíóúàèìòùâêîôûäëïöüãõñç";
    const char *sem_acento = "aeiouaeiouaeiouaeiouaonc";
    
    for (int i = 0; com_acento[i] != '\0'; i++) 
    {
        if (c == com_acento[i]) 
        {
            (*tamanho)--;
            return sem_acento[i];
        }
    }

    return c; // Retorna o próprio caractere se não for acentuado
}

//CONSTROI TODA A STRING DE ENTRADA EM UMA SEM ACENTUAÇÃO
char *criar_copia_sem_acentos(const char *str, int *tamanho) 
{
    char *copia = malloc(strlen(str) + 1); // Aloca memória para a cópia
    int voide;
    if (copia == NULL) 
    {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; str[i] != '\0'; i++) 
    {
        copia[i] = remove_acento(str[i], &voide);
    }
    copia[strlen(str)] = '\0'; // Certifica-se de terminar a string corretamente
    return copia;
}

//CALCULA A LARGURA NECESSARIA PARA CADA TABELA
void calcularLarguraColunas(Tabela *tabela, int *larguras) 
{
    for (int j = 0; j < tabela->colunas; j++) 
    {
        larguras[j] = strlen(tabela->nomeColuna[j]);
        for (int i = 0; i < tabela->linhas; i++) 
        {
            int tamanhoCelula = 0;
            switch (tabela->tiposColuna[j]) 
            {
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
            tamanhoCelula += 2; // Adiciona espaçamento para a formatação da tabela

            if (tamanhoCelula > larguras[j]) 
            {
                larguras[j] = tamanhoCelula;
            }
        }
    }
}


//CONVERTE O TIPO DE DADO DAS CELULAS PARA TEXTO LEGIVEL
const char* tipoParaString(DataType tipo) 
{
    switch (tipo) 
    {
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

//CONSTRUTOR DE TABELA
Tabela* construtorTabela(int linhas, int colunas, char nome[]) 
{
    // Aloca memória para a estrutura Tabela
    Tabela* newTable = alocarTabela(linhas, colunas);
    if (newTable == NULL) 
    {
        printf("Falha na alocação de memória para Tabela.\n");
        return NULL;
    }

    // Define o nome da tabela
    strncpy(newTable->nome, nome, TAMANHO_MAX_NOME);

    // Preenche informações sobre colunas e tipos
    char linhaEntrada[100];
    char nomeColuna[TAMANHO_MAX_NOME];
    int tipo;

    for (int i = 0; i < colunas; i++) 
    {

        if (i == 0) 
         {
            do
            {
                printf("Nome da coluna %d (Chave primária): ", i + 1);
                fgets(linhaEntrada, 100, stdin);
                // Verifica se a entrada contém ponto e vírgula, indicando uma tentativa de definir um tipo
                if (strchr(linhaEntrada, ';') != NULL)
                {
                    printf("Não é permitido definir um tipo para a chave primária. Por favor, insira apenas o nome.\n");
                    nomeColuna[0] = '\0'; // Reseta o nome da coluna para forçar o loop
                    continue;
                }
                sscanf(linhaEntrada, "%49[^\n]", nomeColuna);
            } while (nomeColuna[0] == '\0'); // Repete se o nome da coluna for vazio

            newTable->nomeColuna[i] = strdup(nomeColuna);
            newTable->tiposColuna[i] = INT_TYPE;
        } 
        else 
        {
            do
            {
                printf("Nome e tipo da coluna %d: ", i + 1);
                fgets(linhaEntrada, 100, stdin);
                sscanf(linhaEntrada, "%49[^;];%d", nomeColuna, &tipo);
            } while (nomeColuna[0] == '\0' || strchr(linhaEntrada, ';') == NULL); // Repete se o nome da coluna for vazio ou se não houver separador para o tipo

            newTable->nomeColuna[i] = strdup(nomeColuna);

            switch (tipo) 
            {
                case 1: newTable->tiposColuna[i] = STRING_TYPE; break;
                case 2: newTable->tiposColuna[i] = INT_TYPE; break;
                case 3: newTable->tiposColuna[i] = FLOAT_TYPE; break;
                default:
                    printf("Tipo inválido. Atribuindo como texto.\n");
                    newTable->tiposColuna[i] = STRING_TYPE;
            }
        }
    }

    // Aloca memória para as células da tabela
    alocarMemoriaTabela(newTable);

    return newTable;
}


//REMOVE LINHA PELA POR CHAVE PRIMARIA
void removerLinhaPorChave(Tabela *tabela, int chavePrimaria) 
{
    int linhaParaRemover = -1;

    // Encontrar a linha com a chave primária especificada
    for (int i = 0; i < tabela->linhas; i++) 
    {
        if (tabela->table[i][0].intVal == chavePrimaria) 
        {
            linhaParaRemover = i;
            break;
        }
    }

    // Se a linha foi encontrada, removê-la
    if (linhaParaRemover != -1) 
    {
        // Libera a memória da linha específica
        free(tabela->table[linhaParaRemover]);

        // Desloca todas as linhas seguintes para cima no array
        for (int i = linhaParaRemover; i < tabela->linhas - 1; i++) 
        {
            tabela->table[i] = tabela->table[i + 1];
        }

        // Diminui o contador de linhas
        tabela->linhas--;

        // Realoca o array da tabela para ter uma linha a menos
        Celula **novaTable = realloc(tabela->table, tabela->linhas * sizeof(Celula*));
        if (novaTable != NULL || tabela->linhas == 0) 
        {
            tabela->table = novaTable;
        } else 
        {
            // Se a realloc falhar e a contagem de linhas não for zero, temos um erro grave
            printf("Erro ao realocar memória após remover linha.\n");
        }
    } else 
    {
        printf("Chave primária não encontrada.\n");
    }
}

//FAZ PESQUISA DE VALOR NA TABELA
void pesquisaValor(Tabela *tabela) 
{
    char nomeColunaPesquisa[TAMANHO_MAX_NOME];
    char operador;
    char valorPesquisa[100];
    int indiceColuna = -1;
    int larguras[tabela->colunas];
    memset(larguras, 0, sizeof(larguras));

    // Mostrar o nome de todas as colunas
    printf("Colunas disponíveis:\n");
    for (int i = 0; i < tabela->colunas; i++) 
    {
        printf("%s\n", tabela->nomeColuna[i]);
    }

    // Pergunta ao usuário o nome da coluna para pesquisa
    printf("Digite o nome da coluna para a pesquisa: ");
    fgets(nomeColunaPesquisa, sizeof(nomeColunaPesquisa), stdin);
    nomeColunaPesquisa[strcspn(nomeColunaPesquisa, "\n")] = 0; // Remove a quebra de linha

    // Encontra o índice da coluna pelo nome
    for (int i = 0; i < tabela->colunas; i++) 
    {
        if (strcmp(tabela->nomeColuna[i], nomeColunaPesquisa) == 0) 
        {
            indiceColuna = i;
            break;
        }
    }
    if (indiceColuna == -1) 
    {
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
    for (int j = 0; j < tabela->colunas; j++) 
    {
        int tamanho = strlen(tabela->nomeColuna[j]), diferenca = 0;;
        char sup;
        for (int i = 0; i < tamanho; i++)
        {
            sup = remove_acento(tabela->nomeColuna[j][i], &diferenca);
        }
        printf("| %-*s ", larguras[j]-(diferenca/2), tabela->nomeColuna[j]);
    }
    printf("|\n");

    // Linha separadora
    for (int j = 0; j < tabela->colunas; j++) 
    {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) 
        {
            printf("-");
        }
    }
    printf("+\n");

    // Realiza a pesquisa e imprime os resultados
    for (int i = 0; i < tabela->linhas; i++) 
    {
        bool match = false;
        // A comparação é feita apenas com base no tipo da coluna
        switch (tabela->tiposColuna[indiceColuna]) 
        {
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
        if (match) 
        {
            // Imprime a linha completa que corresponde à pesquisa
            for (int j = 0; j < tabela->colunas; j++) 
			{
			    switch (tabela->tiposColuna[j]) 
			    {
			        case INT_TYPE:
			            printf("| %-*d ", larguras[j], tabela->table[i][j].intVal);
			            break;
			        case STRING_TYPE:
			        {
			            char sup;
			            int tamanho = strlen(tabela->table[i][j].strVal);
			            int diferenca = 0;
			
			            for (int k = 0; k < tamanho; k++)
			            {
			                sup = remove_acento(tabela->table[i][j].strVal[k], &diferenca);
			            }
			            printf("| %-*s ", larguras[j] - (diferenca / 2), tabela->table[i][j].strVal);
			            break;
			        }
			        case FLOAT_TYPE:
			            printf("| %-*.2f ", larguras[j], tabela->table[i][j].floatVal);
			            break;
			    }
			}

            printf("|\n");
        }
    }

    // Linha final
    for (int j = 0; j < tabela->colunas; j++) 
    {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) 
        {
            printf("-");
        }
    }
    printf("+\n");

    printf("Digite 0 para voltar ao menu.\n");
    scanf("%d", &indiceColuna); // Reutiliza a variável para a entrada do usuário
    getchar(); // Limpa o buffer de entrada
}

//PRINTAR A TABELA
void mostrarTabela(Tabela *tabela) 
{
    int p = 1;
    bool acento=false;
    int diferenca, tamanho;
    if (tabela->linhas == 0) 
    {
        printf("A tabela está vazia.\n");
        return;
    }

    int larguras[tabela->colunas];
    calcularLarguraColunas(tabela, larguras);

    // Imprime o cabeçalho da tabela
    for (int j = 0; j < tabela->colunas; j++) 
    {
        int tamanho = strlen(tabela->nomeColuna[j]), diferenca = 0;;
        char sup;
        for (int i = 0; i < tamanho; i++)
        {
            sup = remove_acento(tabela->nomeColuna[j][i], &diferenca);
        }
        printf("| %-*s ", larguras[j]-(diferenca/2), tabela->nomeColuna[j]);
    }
    printf("|\n");

    // Linha separadora
    for (int j = 0; j < tabela->colunas; j++) 
    {
        printf("+");
        for (int k = 0; k < larguras[j] + 2; k++) 
        {
            printf("-");
        }
    }
    printf("+\n");

    // Imprime os dados da tabela
    for (int i = 0; i < tabela->linhas-1; i++) 
    {
        for (int j = 0; j < tabela->colunas; j++) 
        {
            switch (tabela->tiposColuna[j]) 
            {
                case INT_TYPE:
                    printf("| %-*d ", larguras[j], tabela->table[i][j].intVal);
                    break;
                case STRING_TYPE:
                    tamanho = strlen(tabela->table[i][j].strVal), diferenca = 0;
                    char sup;
                    for (int k = 0; k < tamanho; k++)
                    {
                        sup = remove_acento(tabela->table[i][j].strVal[k], &diferenca);
                    }
                    printf("| %-*s ", larguras[j]-(diferenca/2), tabela->table[i][j].strVal);
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
void PegarDados(Tabela *tabela) 
{
    char buffer[100]; // Buffer para entrada do usuário
    bool continuar = true, chaveValida = false, inteiro;
    int linhaAtual = tabela->linhas - 1; // Ajustado para corresponder ao índice correto
    int chave, resultado;
    char *endPtr;
    while (continuar) 
    {
        // Se já existem linhas, aloca uma nova linha
        if (linhaAtual >= 0) 
        {
            aumentarTabela(tabela);
        }

        printf("Inserindo dados para a linha %d:\n", linhaAtual + 1);
        //FAZ A VERIFICAÇÃO SE A CHAVE PRIMARIA INSERIDA JA EXISTE NA TABELA
        do 
        {
            int chave, verificacaoTotal = 0;
            char buffer[100];
            char *endPtr;

            printf("Digite o valor para a chave primária: ");

            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0; // Remover nova linha

            if (strcmp(buffer, "Fim") == 0) 
            {
                continuar = false;
                break;
            }


            chave = strtol(buffer, &endPtr, 10);

            if (buffer == endPtr || *endPtr != '\0') 
            {
                printf("Tipo de chave inválida, a chave precisa ser um número inteiro puro.\n");
                continue;
            }else
            {
                verificacaoTotal++;
            }

            // Verifica se a chave é negativa
            if (chave < 0)
            {
                printf("A chave primária não pode ser negativa. Por favor, insira um número positivo.\n");
                continue;
            }else
            {
                verificacaoTotal++;
            }

            // Aqui, inserir a função verificarChave que checa se a chave já existe na tabela
            chaveValida = verificarChave(tabela, chave);
            if (!chaveValida) 
            {
                printf("Chave primária já existe. Por favor, insira uma chave primária única.\n");
                verificacaoTotal = false;
            }else
            {
                verificacaoTotal++;
            }
            if (verificacaoTotal == 3)
            {
                continuar == true;
                break;
            }

        } while (!chaveValida && continuar);
        if (!continuar) 
        {
            break;
        }else if (strcmp(buffer, "Fim") == 0)
        {
            break;
        }
        tabela->table[tabela->linhas-2][0].intVal = chave;
        for (int j = 1; j < tabela->colunas; j++) 
        {
            printf("Digite o valor para a coluna '%s': ", tabela->nomeColuna[j]);
            fgets(buffer, 100, stdin); // Lê a entrada do usuário
            // Verifica se o usuário digitou 'Fim'
            buffer[strcspn(buffer, "\n")] = 0; // Remove o '\n' no final
            if (strcmp(buffer, "Fim") == 0) 
            {
                continuar = false;
                break;
            }

            // Processa a entrada com base no tipo de dado da coluna
            switch (tabela->tiposColuna[j]) 
            {
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

        if (continuar) 
        {
            linhaAtual++;
        }
    }

    // Ajusta o tamanho final da tabela, se necessário
    if (linhaAtual == -1) 
    {
        // Se nenhuma linha foi adicionada, não ajusta o tamanho
        tabela->linhas = 0;
    } else 
    {
        tabela->linhas = linhaAtual+1;
    }
}