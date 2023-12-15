#include "visualManipulation.h"
#include "memoryAllocation.h"
#include "tableManipulation.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//INICIO DAS FUNÇÕES
void tabelaSelecionada(Tabela *tabela) {
    //ITERAVEIS
    int i;
    //VARIAVEIS
    char nometabela[100];
    int tamanhoNome = 0; // Variável para armazenar o tamanho da string
    int quantidadeDeEspacos = 26;

    if (tabela != NULL) {
        strncpy(nometabela, tabela->nome, sizeof(nometabela) - 1);
		nometabela[sizeof(nometabela) - 1] = '\0'; // Garante que a string seja terminada corretamente

        nometabela[99] = '\0'; // Garante que a string seja terminada corretamente
        
        tamanhoNome = strlen(nometabela); // Calcula o tamanho da string
        
        if(tamanhoNome > 21){
            printf("| 10. Sair                              |   ");
            for(i = 0;i < 21; i++){
                printf("%c",nometabela[i]);
            }
            printf("...  |\n");
        }else{
            //CALCULA TAMBÉM PARA CASO O NOME TENHA ACENTUAÇÃO
            int tamanho = strlen(nometabela), diferenca = 0;
            char sup;
            for (int i = 0; i < tamanho; i++)
            {
                sup = remove_acento(nometabela[i], &diferenca);//CALCULA QUANTOS LETRAS COM ACENTUAÇÃO TEM
            }
            printf("| 10. Sair                              |   %-*s", quantidadeDeEspacos-diferenca/2, nometabela);
            printf("|\n");
        }
    } else {
        printf("| 10. Sair                              |   Sem Tabela Carregada      |\n");
    }
}


void quadroDeAvisos(Tabela *tabela,QuadroDeAvisos *quadrodeavisos){
    //ITERAVEIS
    int i;
    //VARIAVEIS
    char nometabela[100];
    int tamanhoNome;
    int quantidadeDeEspacos = 26;

    if (tabela != NULL) {
        strncpy(nometabela, tabela->nome, sizeof(nometabela) - 1);
        nometabela[sizeof(nometabela) - 1] = '\0'; // Garante que a string seja terminada corretamente

        nometabela[99] = '\0'; // Garante que a string seja terminada corretamente
        
        tamanhoNome = strlen(nometabela); // Calcula o tamanho da string
    }

if(*quadrodeavisos->quadroAvisosAtivo == 0){
    if(*quadrodeavisos->linhaAviso <= 4){
        printf("                             |\n");
    }
}else{
    switch(*quadrodeavisos->linhaAviso){
    case 0: 
        if(*quadrodeavisos->aviso){
            printf(" Nenhuma tabela              |\n");// AVISO DE NÃO TER TABELA SELECIONADA
        }
        if(*quadrodeavisos->salvo){
            printf(" Tabela:                     |\n");
        }
        if(tabela != NULL){
        	if(*quadrodeavisos->tabelaCarregada){
            	printf(" Tabela:                     |\n");
        	}
    	}
        if(*quadrodeavisos->invalido){
            printf(" Opção inválida!             |\n");
        }
        break;
    case 1:
        if(*quadrodeavisos->aviso){
            printf(" selecionada.                |\n");// AVISO DE NÃO TER TABELA SELECIONADA
        }
        if(*quadrodeavisos->salvo){
            if(tamanhoNome > 21){
                printf(" ");
                for(i = 0;i < 21; i++){        //ESCREVE O NOME DA TABELA
                    printf("%c",nometabela[i]);
                }
                printf("...    |\n");
            }else{
                printf(" %s",nometabela);
                for(i = 0; i < quantidadeDeEspacos - tamanhoNome; i++){
                    printf(" ");
                }
                printf("  |\n");
            }
        }
        if(*quadrodeavisos->tabelaCarregada){
            if(tabela != NULL){
            	if(tamanhoNome > 21)
                {
                    printf(" ");
                    int tamanho = strlen(nometabela), diferenca = 0;
                    char sup;
                    for (int i = 0; i < tamanho; i++)
                    {
                        sup = remove_acento(nometabela[i], &diferenca);//CALCULA QUANTOS LETRAS COM ACENTUAÇÃO TEM
                    }
                    printf(" %-*s",quantidadeDeEspacos - diferenca, nometabela);
                    printf("...    |\n");
                }else
                {
                    int tamanho = strlen(nometabela), diferenca = 0;
                    char sup;
                    for (int i = 0; i < tamanho; i++)
                    {
                        sup = remove_acento(nometabela[i], &diferenca);//CALCULA QUANTOS LETRAS COM ACENTUAÇÃO TEM
                    }
                    printf(" %-*s",quantidadeDeEspacos - diferenca/2, nometabela);
                    printf("  |\n");
                }
        }
        }

        if(*quadrodeavisos->invalido){
            printf(" Pressione qualquer          |\n");
        }
        break;
    case 2:
        if(*quadrodeavisos->aviso){
            printf(" Crie uma nova               |\n");// AVISO DE NÃO TER TABELA SELECIONADA
        }
        if(*quadrodeavisos->salvo){
            printf("                             |\n");
        }
        if(tabela != NULL){
        	if(*quadrodeavisos->tabelaCarregada){
            	printf("                             |\n");
        	}
    	}
        if(*quadrodeavisos->invalido){
            printf(" tecla para continuar.       |\n");
        }
        break;
    case 3:
        if(*quadrodeavisos->aviso){
            printf(" tabela ou selecione         |\n");// AVISO DE NÃO TER TABELA SELECIONADA
        }
        if(*quadrodeavisos->salvo){
            printf(" Foi salva com sucesso!      |\n");
        }
        if(*quadrodeavisos->tabelaCarregada){
        	if(tabela != NULL){
            	printf(" Carregada com sucesso!      |\n");
            }
        }
        if(*quadrodeavisos->invalido){
            printf("                             |\n");
        }
        break;
    case 4:
        if(*quadrodeavisos->aviso){
            printf(" uma existente.              |\n");// AVISO DE NÃO TER TABELA SELECIONADA
        }
        if(*quadrodeavisos->salvo){
            printf("                             |\n");
        }
        if(tabela != NULL){
        	if(*quadrodeavisos->tabelaCarregada){
            	printf("                             |\n");
        	}
    	}
        if(*quadrodeavisos->invalido){
            printf("                             |\n");
        }
        break;
    }
}


(*quadrodeavisos->linhaAviso)++;


}

void interfaceCriarTabela(Tabela **lambda) {
    int colunas, chave;
    char nome[TAMANHO_MAX_NOME];

    void criarCabecalho(){
        printf("=======================================================================\n");
        printf("|                         CRIAR NOVA TABELA                           |\n");
        printf("=======================================================================\n");
    }

    criarCabecalho();
    printf("| ");
    printf("Qual Nome da Tabela? ");
    scanf(" %49s", nome);
    getchar();
    limparTela();

    criarCabecalho();
    printf("| Nome da sua tabela: %s |\n", nome);
    printf("| ");
    printf("Quantas Colunas você quer na sua tabela? ");
    scanf("%d", &colunas);
    getchar();
    limparTela();

    criarCabecalho();
    printf("| Nome da sua tabela: %s |\n", nome);
    printf("| Quantidade de colunas: %d |\n\n", colunas);

    if (*lambda != NULL) {
        liberarTabela(*lambda); // Libera a tabela anterior se existir
    }

    printf("A primeira coluna é a chave primaria de tipo INTEIRO.\n");
    printf("As próximas colunas devem ter esse formato (Ex: NomeCliente;1)\n");
    printf("Texto = 1    Número inteiro = 2    Número com casa decimal = 3\n\n");

    *lambda = construtorTabela(1, colunas, nome);
}