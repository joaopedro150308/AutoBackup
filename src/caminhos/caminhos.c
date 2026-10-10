#include <stdio.h>
#include <string.h>

#include "../configs/configs.h"
#include "caminhos/caminhos.h"

// ### FORMATAÇÃO ###

void eliminarAspas(char* caminho)
{
    
    char novoCaminho[CAMINHO_MAXIMO];
    char* ptrAspas;

    char aspas = '"';
    char* ptrA = &aspas;
    
    // Verificando a presença de aspas
    if(strcspn(caminho, ptrA) == strlen(caminho)) { // Não há aspas
        //printf("Caminho não está entre aspas.\n");

    } else { // Existem aspas
        ptrAspas = strtok(caminho, ptrA);
        while (ptrAspas != NULL)
        {
            strcat(novoCaminho, ptrAspas); // Adiciona a parte sem aspas à string de saida
            ptrAspas = strtok(NULL, ptrA); // Altera o token
        }

        memset(caminho, '\0', sizeof(caminho)); // Limpa o  caminho antigo
        strcpy(caminho, novoCaminho); // Atualiza o caminho com as alterações
        
        memset(novoCaminho, '\0', sizeof(novoCaminho)); // Reseta novoCaminho
        
        ptrAspas = NULL;
        ptrA = NULL;

        //printf("Aspas removidas com sucesso.\n");
    }
}

void duplicarContraBarras(char* caminho)
{
    char novoCaminho[CAMINHO_MAXIMO] = {'\0'};

    char *ptrBarras;

    ptrBarras = strtok(caminho, "\\"); // Pega parte do caminho antigo
    while (ptrBarras != NULL)
    {
        strcat(novoCaminho, ptrBarras); // Adiciona token ao novo caminho
        
        ptrBarras = strtok(NULL, "\\"); // Consegue a próxima parte do caminho antigo, ou é NULL

        if (ptrBarras != NULL) // Verifica se o ponteiro ficou nulo. Adiciona "\\" até o ponteiro ficar nulo
        {
            strcat(novoCaminho, "\\\\");
        }
    }

    strcpy(caminho, novoCaminho); // Atualiza o caminho antigo
}

void addEndline(char* caminho)
{
    char quebra = '\n';
    char* ptrQ = &quebra;

    strcat(caminho, "\n"); // Adiciona a quebra de linha
}

void retirarEndlinde(char* caminho)
{
    int quebraLinhaIndex = 0;

    quebraLinhaIndex = strcspn(caminho, "\n");
    caminho[quebraLinhaIndex] = '\0';
}

void addCharCuringa(char* caminho)
{
    strcat(caminho, "\\\\*");
}

void formatarCaminho(char* caminho)
{
    /*Formata o caminho especificado (colocando contra-barras duplas, por exemplo)*/
    //eliminarAspas(caminho);
    duplicarContraBarras(caminho);
    eliminarAspas(caminho);
}   
