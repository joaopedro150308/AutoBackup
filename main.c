#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "./data//data.h"
#include "./uteis//uteis.h"

int main()
{
    char caminho[260];
    int b = 0; // Valor booleano

    // Define a codificação
    setlocale(LC_ALL, ".UTF-8");
    limpar();

    // Lendo caminhos
    printf("Digite o caminho de um arquivo ('0' para sair): ");
    fgets(caminho, sizeof(caminho), stdin);
        // Limpando '\n'
    caminho[strcspn(caminho, "\n")] = '\0';
    
    while (strcmp(caminho, "0") != 0) // Enquanto for diferente de "0"
    {
        // Formatando
        formatarCaminho(caminho);
        verificarTipoCaminho(caminho);
        conseguir_origem(caminho);
        //conseguir_caminhos(caminho);

        if (verificar_caminho_ja_adicionado(caminho) == 1)
        {
            printf("Caminho já adicionado.\n");
        }
        else // Adicionar, caso não o tenha feito ainda
        {
            printf("Caminho ainda não adicionado.\n");

            b = adicionarParaBackup(caminho); // Adicionando

            // Verificando status da operação de adição
            if (b == 0)
            {
                printf("Falha ao adicionar à lista de backup.\n");
            }
            else
            {
                printf("Adição bem sucedida.\n");
            }
        }
        
        printf("PRESSIONE QUALQUER TECLA PARA CONTINUAR. . .\n");
        getch();

        // Releitura do flag
        limpar();
        printf("Digite o caminho de um arquivo ('0' para sair): ");
        fgets(caminho, sizeof(caminho), stdin);
            // Limpando '\n'
        caminho[strcspn(caminho, "\n")] = '\0';
    }
    

    return 0;
}