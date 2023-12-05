#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include "memoryAllocation.h" // FUNÇÕES DE CONTROLE DE MEMORIA
#include "tableManipulation.h" // FUÇÕES DE MANIPULAÇÃO DE TABELA
#include "fileManipulation.h" // FUNÇÕES DE MANIPULAÇÃO DE ARQUIVO
#include "visualManipulation.h" //FUNÇÕES DE MANIPULAÇÃO VISUAL


//INICIO DAS DIRETIVAS DE PRE PROCESSAMENTO
//Inclui o windows.h quando esta sendo executado no windows
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
//limpa a tela
void limparTela() {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}
void esperarTempo(int tempo){
    #ifdef _WIN32
    Sleep(tempo * 1000);  // Pausa a execução por 5000 milissegundos (5 segundos)
    #else
    sleep(tempo);     // Pausa a execução por 5 segundos
    #endif
}
//FIM DAS DIRETIVAS DE PRE PROCESSAMENTO


int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(65001); // Se estiver no Windows, define a página de códigos para UTF-8
    #endif
    FILE *arquivo;
    arquivo = fopen("tabelas.itp", "a+"); //Garantindo existencia do arquivo
    fclose(arquivo);

    

    //Alocando memorias para o quadro de avisos
    QuadroDeAvisos *quadrodeavisos = inicializarQuadroDeAvisos();


    int opcao, colunas, chave;
    char nome[TAMANHO_MAX_NOME];

    Tabela *lambda = NULL;
    while (*(quadrodeavisos->executando)) {
        limparTela(); // Para Qualquer Sistema;
        // Exibe o menu principal
        printf("=======================================================================\n");
        printf("|                         MENU PRINCIPAL                              |\n");
        printf("=======================================================================\n");
        printf("| Criação e Seleção de Tabelas:         | Autores:                    |\n");
        printf("| 1. Criar Nova Tabela                  |   - Geraldo Filho           |\n");
        printf("| 2. Selecionar Tabela                  |   - Miguel Arcanjo          |\n");
        printf("| 3. Listar Tabelas                     |                             |\n");
        printf("|---------------------------------------|");quadroDeAvisos(lambda,quadrodeavisos);
        printf("| Manipulação de Dados:                 |");quadroDeAvisos(lambda,quadrodeavisos);
        printf("| 4. Adicionar dados na tabela          |");quadroDeAvisos(lambda,quadrodeavisos);
        printf("| 5. Visualizar Tabela                  |");quadroDeAvisos(lambda,quadrodeavisos);
        printf("| 6. Remover Linha                      |");quadroDeAvisos(lambda,quadrodeavisos);
        printf("| 7. Pesquisar Valor                    |                             |\n");//CONSERTAR
        printf("|---------------------------------------|                             |\n");
        printf("| Gerenciamento de Tabela:              |                             |\n");
        printf("| 8. Salvar Tabela                      | Tabela Selecionada:         |\n");
        tabelaSelecionada(lambda);
        printf("=======================================================================\n");
        //Reiniciando variavel dos ponteiros da função quadroDeAvisos();
        *(quadrodeavisos->aviso) = 0;
        *(quadrodeavisos->quadroAvisosAtivo) = 0;
        *(quadrodeavisos->linhaAviso) = 0;
        *(quadrodeavisos->salvo) = 0;
        *(quadrodeavisos->invalido) = 0;

        

        //PEGAR ESCOLHA
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer de entrada

        switch (opcao) {
            case 1: //CRIAR UMA TABELA
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
                lambda = construtorTabela(1, colunas, nome);
                break;
            case 2: // CARREGAR TABELA
                printf("Digite o nome de uma tabela: ");
                if (fgets(nome, sizeof(nome), stdin) != NULL) {
                    nome[strcspn(nome, "\n")] = '\0';
                } else {
                    printf("Erro ao ler a entrada.\n");
                }
                if(lambda != NULL) {
                    liberarTabela(lambda); // Libera a tabela anterior se existir
                }
                lambda = carregarTabela(nome);
                *(quadrodeavisos->tabelaCarregada) = 1;
                *(quadrodeavisos->quadroAvisosAtivo) = 1;
                break;
            case 3://LISTAR TABELAS EXISTENTES
                listarTabelas();
                break;
            case 4://ADICIONAR DADOS NA TABELA SELECIONADA
                if (lambda != NULL)
                {
                    limparTela();
                    printf("Tabela selecionada: %s\n", lambda->nome);
                    printf("Quando você não quiser mais adicionar dados a tabela digite -> Fim <-\n");
                    PegarDados(lambda);
                }else{
                    *(quadrodeavisos->aviso) = 1;
                    *(quadrodeavisos->quadroAvisosAtivo) = 1;
                }
                break;
            case 5://MOSTRAR TABELA SELECIONADA
                if (lambda != NULL)
                {
                    printf("Tabela selecionada: %s\n", lambda->nome);
                    limparTela();
                    mostrarTabela(lambda);  
                }else{
                    *(quadrodeavisos->aviso) = 1;
                    *(quadrodeavisos->quadroAvisosAtivo) = 1;
                }
                break;
                
            case 6://REMOVE LINHA POR CHAVE
                if (lambda != NULL)
                {
                    limparTela();
                    printf("Tabela selecionada: %s\n", lambda->nome);
                    printf("Qual a chave da linha que você quer apagar da tabela '%s': \n", lambda->nome);
                    scanf("%d", &chave);
                    removerLinhaPorChave(lambda, chave);
                }else{
                    *(quadrodeavisos->aviso) = 1;
                    *(quadrodeavisos->quadroAvisosAtivo) = 1;
                }
                break;
            case 7://PESQUISA VALOR NA TABELA
                limparTela();
                if (lambda != NULL)
                {
                    pesquisaValor(lambda);
                }else{
                    *(quadrodeavisos->aviso) = 1;
                    *(quadrodeavisos->quadroAvisosAtivo) = 1;
                }
                break;
            case 8://SALVA TABELA NO BANCO DE DADOS
                if (lambda != NULL) {
                    salvarArquivo(lambda);
                    *(quadrodeavisos->salvo) = 1;
                    *(quadrodeavisos->quadroAvisosAtivo) = 1;
                }else{*(quadrodeavisos->aviso) = 1; *(quadrodeavisos->quadroAvisosAtivo) = 1;}
                break;
            case 9://SAIR DO PROGRAMA
                *(quadrodeavisos->executando) = 0;
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