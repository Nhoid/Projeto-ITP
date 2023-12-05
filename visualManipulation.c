#include "visualManipulation.h"
#include "memoryAllocation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
        	printf("| 9. Sair                               |   ");
        	for(i = 0;i < 21; i++){
        		printf("%c",nometabela[i]);
        	}
        	printf("...  |\n");
        }else{
        	printf("| 9. Sair                               |   %s", nometabela);
        	for(i = 0; i < quantidadeDeEspacos - tamanhoNome; i++){
        		printf(" ");
        	}
        	printf("|\n");
        }
    } else {
        printf("| 9. Sair                               |   Sem Tabela Carregada      |\n");
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
        	}else{
        		printf("                             |\n");
        	}
    	}else{
    		printf("                             |\n");
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
            	if(tamanhoNome > 21){
                	printf(" ");
                	for(i = 0;i < 21; i++){
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
        	}else{
        		printf("                             |\n");
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
    	}else{
    		printf("                             |\n");
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
            }else{
            	printf("                             |\n");
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
    	}else{
    		printf("                             |\n");
    	}
        if(*quadrodeavisos->invalido){
            printf("                             |\n");
        }
        break;
    }
}


(*quadrodeavisos->linhaAviso)++;


}