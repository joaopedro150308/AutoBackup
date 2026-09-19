#include <stdio.h>
#include <error.h>
#include <shlwapi.h>

#include "configs/configs.h"

// ### Configurando pasta Backups ###

int existe_caminho_backups()
{
    char linha[CAMINHO_MAXIMO];
    FILE* fptr;

    fptr = fopen(CAMINHO_BACKUPS_TXT, "r");

    if(fgets(linha, CAMINHO_MAXIMO, fptr) == NULL) {
        return 0;

    } else {
        return 1;
        
    }

    fclose(fptr);
}

void criar_caminho_pasta_backups()
{
    /* Cria ou atualiza o arquivo que conterá o caminho para a pasta Backups. */

    char caminho_backups[CAMINHO_MAXIMO];
    FILE* fptr;

    // Consegue o caminho digitado
    printf("Insira o caminho no qual a pasta Backups será criada: ");

    fgets(caminho_backups, CAMINHO_MAXIMO, stdin);
    caminho_backups[strcspn(caminho_backups, "\n")] = '\0';

    formatarCaminho(caminho_backups);

    sprintf(caminho_backups, "%s\\\\%s", caminho_backups, "Backups");

    // Criando ou atualizando o arquivo
    fptr = fopen("data\\Caminho_Backups.txt", "w");

    fprintf(fptr, "%s", caminho_backups); // Salvo a novo caminho

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

int existe_pasta_backups()
{
    /* Função que verifica a existência da pasta Backups, que conterá os backups 
       Retorna zero caso a pasta exista e o caminho para está seja válido */

    char nome_pasta[20];
    char* nameptr;

    printf("Verificando existência da pasta Backups...\n");

    FILE* fptr;
    fptr = fopen(CAMINHO_BACKUPS_TXT, "r");

    char cam_backups[CAMINHO_MAXIMO]; // Caminho para a pasta backups

    if(fptr == NULL){
        printf("Falha ao encontrar a pasta Backups. Caminho não existe ou foi movido.\n");
        return 1;

    } else { // Algum caminho encontrado
        if(fgets(cam_backups, CAMINHO_MAXIMO, fptr) != NULL) { // Pega o caminho se houver algo na linha
            cam_backups[strcspn(cam_backups, "\n")] = '\0';
    
            // Conseguindo o nome da pasta
            nameptr = strrchr(cam_backups, '\\');
            sprintf(nome_pasta, "%s", nameptr + 1);
            
            // Verifica se o nome é Backups
            if(strcmp(nome_pasta, "Backups") == 0){ // Caso seja Backups
    
                if(PathFileExists(cam_backups)) { // Verifica se o caminho é válido
                    printf("Caminho válido encontrado.\n");
                    return 0;
                
                } else {
                    printf("Caminho inválido encontrado.\n");
                    return 2;
                }
        
    
            } else { // Caso o nome não seja backups
                printf("O caminho não faz referência à pasta Backups.\n");
                return 2;
            }

        } else { // Nesse caso, não há nada na linha
            printf("Não há caminho para Backups registrado.\n");
            return 1;
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
