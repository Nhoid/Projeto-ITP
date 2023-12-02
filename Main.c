#include <stdio.h>
#include <stddef.h>
#include "memoryAllocation.h" // FUNÇÕES DE CONTROLE DE MEMORIA
#include "tableManipulation.h" // FUÇÕES DE MANIPULAÇÃO DE TABELA
#include "fileManipulation.h" // FUNÇÕES DE MANIPULAÇÃO DE ARQUIVO

//limpa a tela
void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int main(){
    int opcao, colunas, chave;
    char nome[TAMANHO_MAX_NOME];
    bool executando = true, aviso = false;
    Tabela *lambda = NULL;
    const char *ArquivoTabela = "tabelas.itp";
    while (executando) {
       limparTela(); // Para Qualquer Sistema;

        // Exibe o menu principal
        printf("========================================\n");
        printf("|             MENU PRINCIPAL            |\n");
        printf("========================================\n");
        printf("| 1. Criar Nova Tabela                  |\n");
        printf("| 2. Adicionar dados na tabela          |\n");
        printf("| 3. Visualizar Tabela                  |\n");
        printf("| 4. Remover Linha                      |\n");
        printf("| 5. Pesquisar Valor                    |\n");
        printf("| 6. Salvar Tabela                      |\n");
        printf("| 7. Sair                               |\n");
        printf("========================================\n");
        if (lambda != NULL)
        {
            printf("Tabela selecionada: %s\n", lambda->nome);
        }else if (!aviso) {printf("Nenhuma tabela selecionada ou criada.\n");}
        if (aviso)
        {
            printf("Nenhuma tabela selecionada.\n");
            printf("Crie uma nova tabela ou carregue alguma existente.\n");
            aviso  = false;
        }
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                limparTela();
                printf("Qual Nome da Tabela? \n");
                scanf(" %49s", nome);
                getchar();
                printf("Quantas Colunas você quer na sua tabela? \n");
                scanf("%d", &colunas);
                getchar();
                if (lambda != NULL) {
                    liberarTabela(lambda); // Libera a tabela anterior se existir
                }
                lambda = criarTabela(1, colunas, nome);
                break;
            case 2:
                if (lambda != NULL)
                {
                    limparTela();
                     printf("Tabela selecionada: %s\n", lambda->nome);
                    printf("Quando você não quiser mais adicionar dados a tabela digite -> Fim <-\n");
                    PegarDados(lambda);
                }else{
                    aviso = true;
                }
                break;
            case 3:
                if (lambda != NULL)
                {
                    printf("Tabela selecionada: %s\n", lambda->nome);
                    limparTela();
                    mostrarTabela(lambda);  
                }else{
                    aviso = true;
                }
                break;
            case 4:
                if (lambda != NULL)
                {
                    limparTela();
                     printf("Tabela selecionada: %s\n", lambda->nome);
                    printf("Qual a chave da linha que você quer apagar da tabela '%s': \n", lambda->nome);
                    scanf("%d", &chave);
                    removerLinhaPorChave(lambda, chave);
                }else{
                    aviso = true;
                }
                break;
            case 5:
                limparTela();
                if (lambda != NULL)
                {
                    pesquisaValor(lambda);
                }else{
                    aviso = true;
                }
                break;
            case 6:
                if (lambda != NULL) {
                    salvarArquivo(lambda, ArquivoTabela);
                }else{aviso = true;}
                break;
            case 7:
                executando = false;
                if (lambda != NULL) {
                    liberarTabela(lambda);
                }
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Pressione qualquer tecla para tentar novamente.\n");
                getchar(); // Aguarda o usuário pressionar uma tecla
        }
    }

    return 0;
}