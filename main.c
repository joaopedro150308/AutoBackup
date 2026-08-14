#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "./data//data.h"
#include "./uteis//uteis.h"

int main()
{
    char origem[260];
    char destino[260];
    int b = 0, opcao = 0; // Valor booleano

    // Define a codificação
    setlocale(LC_ALL, ".UTF-8");
    limpar();

    // Verificando a existência de uma pasta para conter os backups
    fazer_titulo("VERIFICANDO PASTA BACKUPS", 5);
    pular(); // Pulando a linha
    pular();

    if(existe_pasta_backups() == 0){ // Existe
        printf("Pasta Backup já existe e foi encontrada.\n");

    } else {
        // Verificar existência de um caminho
        if(!existe_caminho_backups()) {
            criar_caminho_pasta_backups();
        }   
        criar_pasta_backups();
    }

    printf("Verificação concluída. Digite qualquer coisa para continuar.\n");
    getchar();

    // Lendo e verificando opção de procedimento a ser realizado

    do {
        limpar();

        fazer_titulo("SELECIONE O PROCEDIMENTO", 5);
        pular();
        pular();

        printf("[1] Iniciar Backup com as configurações atuais\n[0] Alterar configurações\n");
        linha('-', 15);
        pular();
        printf("Sua escolha: ");

        scanf("%d", &opcao); // Lendo a opção
        while(getchar() != '\n');

        switch(opcao){
            case 1:
                printf("Iniciando Backup...\n");
                break;
            
            case 0:
                printf("Alterando arquivos...\n");
                break;
    
            default:
                printf("Opção inválida. Digite qualquer coisa para tentar novamente.\n");
                getchar();

        }
    } while(opcao != 1 && opcao != 0); 
        // Iniciar Backup com as configurações já salvas
        // Alterar arquivos

    // Algorítimo de cópia
        // Lendo caminho da origem
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

    return 0;
}