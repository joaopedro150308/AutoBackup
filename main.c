#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "./data//data.h"
#include "./uteis//uteis.h"

int main()
{
    char op_buff[3];
    char origem[260];
    char destino[260];
    int b = 0, opcao = 999; // Valor booleano
    char c = '\0';

    // Define a codificação
    setlocale(LC_ALL, ".UTF-8");
    limpar();

    // Verificando a existência de uma pasta para conter os backups
    fazer_titulo("VERIFICANDO PASTA BACKUPS", 5);
    pular(); // Pulando a linha
    pular();

    switch(existe_pasta_backups()) {
        case 0: // Existe e caminho e foi encontrada (good ending)
            printf("Pasta Backup já existe e foi encontrada.\n");
            break;
        
        case 1: // Caminho não existe ou a pasta não existe
            if (!existe_caminho_backups()) {
            criar_caminho_pasta_backups();
            } 
            criar_pasta_backups();
            break;

        case 2: // Caminho existe mas é inválido
            criar_caminho_pasta_backups(); // Atualiza o caminho
            criar_pasta_backups();
            break;
    }

    printf("Verificação concluída. Digite qualquer coisa para continuar.\n");
    getchar(); // Pausa o programa

    // Lendo e verificando opção de procedimento a ser realizado
    do {
        limpar();

        fazer_titulo("SELECIONE O PROCEDIMENTO", 5);
        pular();
        pular();

        printf("[1] Iniciar Backup com as configurações atuais\n[2] Alterar configurações\n[0] Voltar/Sair\n");
        linha('-', 15);
        pular();
        printf("Sua escolha: ");

        fgets(op_buff, 3, stdin);
        sscanf(op_buff,"%d", &opcao);

        switch(opcao) { // Conseguindo opção do procedimento
            case 1:
                if(existe_arquivo_para_copiar()) {
                    printf("Iniciando Backup...\n");
                }
                getchar();
                opcao = 999;
                break;
            
            case 2:
                do {
                    limpar();

                    fazer_titulo("ALTERAR ARQUIVOS", 5);
                    pular();
                    pular();

                    printf("[1] Adicionar arquivo/diretório\n[2] Remover arquivo/diretório\n[0] Voltar\n");
                    linha('-', 15);
                    pular();
                    printf("Sua escolha: ");

                    fgets(op_buff, 3, stdin);
                    sscanf(op_buff, "%d", &opcao);

                    switch(opcao) { // Conseguindo opção do procedimento
                        case 1:
                            printf("Adicionando arquivos...\n");
                            adicionar_arquivos(); // Procedimento Add. Arquivos
                            opcao = 999;
                            break;
                        
                        case 2:
                            limpar();
                            printf("   ARQUIVOS SALVOS   ");
                            remover_arquivos();
                            opcao = 999;                          
                            break;

                        case 0:
                            printf("Saindo...\n");
                            break;
                
                        default:
                            printf("Opção inválida. Digite qualquer coisa para tentar novamente.\n");
                            getchar();
                    }
                } while(opcao != 1 && opcao != 2 && opcao != 0);
                opcao = 999; // Passará para o menu anterior
                break;
    
            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida. Digite qualquer coisa para tentar novamente.\n");
                getchar();
        }
    } while(opcao != 1 && opcao != 2 && opcao != 0);

    // Fim do programa
    limpar();
    printf("Encerrando...");

        // Iniciar Backup com as configurações já salvas
        // Alterar arquivos

    // Algorítimo de cópia
        // Lendo caminho da origem

    /*
    limpar();
    printf("Digite o caminho da pasta de origem ('0' para sair): ");
    fgets(origem, sizeof(origem), stdin);
    origem[strcspn(origem, "\n")] = '\0'; // Limpando '\n'

    // Lendo caminho do destino
    printf("Digite o caminho da pasta de destino: ");
    fgets(destino, sizeof(destino), stdin);
    destino[strcspn(destino, "\n")] = '\0'; // Limpando '\n'
     
    // Formatando caminhos
    formatarCaminho(origem);
    formatarCaminho(destino);

    // Copiar diretório(s)
    criar_pasta_mae(origem, destino, destino);
    if(copiar_diretorio(origem, destino) == 0){
        printf("Cópia bem sucedida.\n");
    }
    else{
        printf("Houve uma falha ao copiar.");
    }
    */

    return 0;
}