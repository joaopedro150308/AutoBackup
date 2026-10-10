#include <stdio.h>
#include <error.h>
#include <windows.h>
#include <shlwapi.h>

#include "../configs/configs.h"
#include "caminhos/caminhos.h"
#include "arquivos/arquivos.h"
#include "backups/backups.h"

// ### Configurando pasta Backups ###

int existe_caminho_backups()
{
    char linha[CAMINHO_MAXIMO];
    FILE* fptr;

    fptr = fopen(CAMINHO_BACKUPS_TXT, "r");

    if(fgets(linha, CAMINHO_MAXIMO, fptr) == NULL) {
        printf("Não foi possível abrir o arquivo em %s", CAMINHO_BACKUPS_TXT);
        fclose(fptr);
        return 0;

    } else { // Arquivo encontrado
        char buff[CAMINHO_MAXIMO];

        // Verificando se há conteúdo
        if(fgets(buff, CAMINHO_MAXIMO, fptr) == NULL)
        {
            printf("Não há nada registrado no arquivo em %s", CAMINHO_BACKUPS_TXT);
            fclose(fptr);
            return 0;
        }

        // Verificando se o caminho encontrado faz referêcia à Backups
        buff[strcspn(buff, "\n")] = '\0';

        char *contra_barraPtr = NULL;
        char nome[50];

        contra_barraPtr = strrchr(buff, '\\');
        sprintf(nome, "%s", nome + 1);

        if(strcmp(nome, "Backups") != 0)
        {
            printf("O caminho encontrado não faz referência à Backups.\n");
            fclose(fptr);
            return 0;
        }
        
        // Caso o caminho esteja correto.
        printf("O caminho encontrado faz referência a Backups.\n");
        fclose(fptr);
        return 1;
    }
}

/* Cria ou atualiza o arquivo que conterá o caminho para a pasta Backups. */
void criar_caminho_pasta_backups()
{

    char caminho_backups[CAMINHO_MAXIMO];
    FILE* fptr;

    // Consegue o caminho digitado
    printf("Insira o caminho no qual a pasta Backups será criada: ");

    fgets(caminho_backups, CAMINHO_MAXIMO, stdin);
    caminho_backups[strcspn(caminho_backups, "\n")] = '\0';

    formatarCaminho(caminho_backups);

    sprintf(caminho_backups, "%s\\\\%s", caminho_backups, "Backups");

    // Criando ou atualizando o arquivo
    fptr = fopen("data\\caminho_backups.txt", "w");

    fprintf(fptr, "%s", caminho_backups); // Salva o novo caminho

    fclose(fptr);
}

int conseguir_caminho_Backups(char* retorno)
{
    /* Função que consegue o caminho salvo para a pasta Backups.
       O caminho será copiado para o buffer "retorno". */

    char c_Backups[CAMINHO_MAXIMO] = {'\0'};
    FILE* fptr;

    fptr = fopen(CAMINHO_BACKUPS_TXT, "r");

    if(fptr == NULL) { // Houve erro
        printf("Erro ao encontrar o arquivo: %s\n", CAMINHO_BACKUPS_TXT);
        return 1;

    } else { // Conseguindo caminho
        fgets(c_Backups, CAMINHO_MAXIMO, fptr);
        c_Backups[strspn(c_Backups, "\n")] = '\0';

        strcpy(retorno, c_Backups);
        return 0; // Sucesso
    }

    fclose(fptr);
}

/* 
Função que verifica a existência da pasta Backups, que conterá os backups. Retorna um códio que representa um estado de execução ou um possível diagnóstico de erro.

1 - Sucesso. Pasta encontrada.
0 - Existe um caminho registrado, mas esse não é válido.
*/
int existe_pasta_backups()
{
    char nome_pasta[20];
    char* nameptr;

    printf("Verificando existência da pasta Backups...\n");

    FILE* fptr;
    fptr = fopen(CAMINHO_BACKUPS_TXT, "r");

    char cam_backups[CAMINHO_MAXIMO]; // Caminho para a pasta backups

    if(fptr == NULL){
        printf("Falha ao encontrar a pasta Backups. Não foi possível encontrar o arquivo de caminho.\n");
        return 0;

    } else { // Arquivo do caminho_backups encontrado
        if(fgets(cam_backups, CAMINHO_MAXIMO, fptr) != NULL) { // Pega o caminho se houver algo na linha
            cam_backups[strcspn(cam_backups, "\n")] = '\0';
    
            // Conseguindo o nome da pasta
            nameptr = strrchr(cam_backups, '\\');
            sprintf(nome_pasta, "%s", nameptr + 1);
            
            // Verifica se o nome é Backups
            if(strcmp(nome_pasta, "Backups") == 0){ // Caso seja Backups
    
                if(PathFileExists(cam_backups)) { // Verifica se a pasta está nesse caminho
                    printf("Caminho válido encontrado.\n");
                    return 1;
                
                } else { // Esse caminho não leva à pasta.
                    printf("Caminho inválido encontrado.\n");
                    return 0;
                }
        
    
            } else { // Caso o nome não seja backups. É necessário um outro caminho
                printf("O caminho não faz referência à pasta Backups.\n");
                return 0;
            }

        } else { // Nesse caso, não há nada na linha.
            printf("Não há caminho para Backups registrado.\n");
            return 0;
        }
    }

    fclose(fptr); // Fechando o arquivo
}

int criar_pasta_backups()
{
    /* Cria a pasta Backups */

    char caminho[CAMINHO_MAXIMO];
    char nome_pasta[] = "Backups";

    FILE* fptr;
    fptr = fopen("data\\Caminho_Backups.txt", "r");

    // Consegue o caminho onde será criada
    fgets(caminho, CAMINHO_MAXIMO, fptr); // Já vem formatado
    caminho[strcspn(caminho, "\n")] = '\0';
    
    //sprintf(caminho, "%s\\\\%s", caminho, nome_pasta); // Adiciona o nome da pasta backups ao caminho

    fclose(fptr);

    if(criar_diretorio(caminho) == 0) { // Sucesso
        return 0;
        
    } else { // Fracasso
        DWORD erro = GetLastError();
        printf("Houve um erro ao criar a pasta. Erro: %lu\n", erro);

        // ### possíveis erros ###
        if(erro == 183){
            printf("A pasta já existe.\n");
        }

        return 1;
    }
}
