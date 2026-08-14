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

    if(existe_pasta_backups() == 0){ // Existe
        printf("Pasta Backup já existe e foi encontrada.\n");

    } else {
        // Verificar existência de um caminho
        if(!existe_caminho_backups()) {
            criar_caminho_pasta_backups();
        } 
        
        criar_pasta_backups();
    }

    // Lendo opção do procedimento a ser realizado


    // Lendo caminho da origem
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
    if(copiar_diretorio(origem, destino) == 0){
        printf("Cópia bem sucedida.\n");
    }
    else{
        printf("Houve uma falha ao copiar.");
    }

    return 0;
}