#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <errno.h>
#include <shlwapi.h>

#define CAMINHO_MAXIMO 260

// ### FORMATAÇÃO ###
void eliminarAspas(char* caminho)
{
    
    char novoCaminho[CAMINHO_MAXIMO];
    char* ptrAspas;

    char aspas = '"';
    char* ptrA = &aspas;
    
    // Verificando a presença de aspas
    if(strcspn(caminho, ptrA) == strlen(caminho)) { // Não há aspas
        printf("Caminho não está entre aspas.\n");

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

        printf("Aspas removidas com sucesso.\n");
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

// ### MANIPULAÇÃO DE ARQUIVOS ###
int adicionarParaBackup(char* caminho)
{
    int b = 0;
    // Retorna um valor que representará verdadeiro ou false (0 para falso)
    // Adiciona um caminho a lista de arquivos para backup

    // Adicionando '\n' ao fim do arquivo
    addEndline(caminho);

    // Inicializar o ponteiro de arquivo
    FILE *fptr;
    fptr = fopen("data\\ListaParaBackup.txt", "a");

    // Adiciona o arquivo à lista
    fprintf(fptr, caminho);

    fclose(fptr);

    // Código de operação bem sucedida
    b = 1;

    return b;
} 

int verificarTipoCaminho(char* caminho)
{
    DWORD atributos = GetFileAttributesA(caminho);

    if (atributos == INVALID_FILE_ATTRIBUTES)
    {
        printf("Caminho inválido ou não encontrado.\n");
        return -1;
    }

    if (atributos & FILE_ATTRIBUTE_DIRECTORY)
    {
        printf("O caminho é um diretório.\n");
        return 1;
    }
    else
    {
        printf("O caminho é um arquivo.\n");
        return 0;
    }
}

int verificar_caminho_ja_adicionado(char* caminho) // Retorna 0 se ainda não foi adicionado e 1 caso contrário
{
    int ja_adicionado = 0; //Falso
    char linha[CAMINHO_MAXIMO];
    int contraBarIndex = 0;

    FILE* fptr;

    fptr = fopen("ListaParaBackup.txt", "r");

    while (fgets(linha, CAMINHO_MAXIMO, fptr))
    {
        // Eliminando quebra de linha
        contraBarIndex = strcspn(linha, "\n");
        linha[contraBarIndex] = '\0'; 

        if (strcmp(linha, caminho) == 0) // São iguais
        {
            ja_adicionado = 1; // Verdadeiro
            return ja_adicionado;
        }
    }

    fclose(fptr); // Fechando arquivo
}

void conseguir_origem(char* caminho)
{
    char* ctrbPtr; // Ponteiro para a última contra barra
    char caminhoBuff[CAMINHO_MAXIMO];

    strcpy(caminhoBuff, caminho); // Faz uma cópia do caminho original para não altera-lo
    ctrbPtr = strrchr(caminhoBuff, '\\');

    *(ctrbPtr - 1) = '\0';

    printf("%s", caminhoBuff);
}

int criar_diretorio(char* caminho)
{
    if(!CreateDirectory(caminho, NULL))
    {
        return 1; // Houve erro
    }

    printf("Pasta criada com sucesso em %s\n", caminho);
    return 0;
}

int copiar_diretorio(char* origem, char*destino) // Consegue todos os arquivos a partir de um dado caminho de diretório
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    char caminhoOrigem[CAMINHO_MAXIMO] = {'\0'};
    char caminhoDestino[CAMINHO_MAXIMO] = {'\0'};

    // Formatando caminho de ficheiro para conseguir todos os arquivos presentes
    int j = snprintf(caminhoOrigem, CAMINHO_MAXIMO, "%s\\\\*", origem); // Adicionando "\\*"
    retirarEndlinde(caminhoOrigem);

    // Consegue o primeiro arquivo no dado caminho
    hFind = FindFirstFile(caminhoOrigem, &findData);

    do
    {
        // Verifica possível erro
        if (hFind == INVALID_HANDLE_VALUE)
        {
            printf("Erro ao inicar busca.\n");
            return 1;
        }

        // Primeiro arquivo
        if (!strcmp(findData.cFileName, ".") || !strcmp(findData.cFileName, ".."))
        {
            continue;
        }

        snprintf(caminhoOrigem, CAMINHO_MAXIMO, "%s\\\\%s", origem, findData.cFileName);
        snprintf(caminhoDestino, CAMINHO_MAXIMO, "%s\\\\%s", destino, findData.cFileName);
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // Se for diretório
        {
            criar_diretorio(caminhoDestino);
            copiar_diretorio(caminhoOrigem, caminhoDestino); // Se for um pasta, chama novamente a função
        }
        else
        {
            CopyFile(caminhoOrigem, caminhoDestino, FALSE); // Se for arquivo, copia para o destino
        }

    }  while (FindNextFile(hFind, &findData));
    
    FindClose(hFind);
    
    return 0; // Pardão de retorno bem-sucedido
}

int criar_pasta_mae(char* origem, char* destino, char* retorno)
{
    /* Função que cria uma pasta mãe, pasta que guarda outras pastas e arquivos.
       É a pasta de nível mais alto de um dado caminho. 
       Ao criar a nova pasta, seu caminho é copiado para "retorno".
       Se este for NULL, não haverá retorno.*/

    char nome_pasta_mae[CAMINHO_MAXIMO] = {'\0'};
    char* nomeptr;
    char caminho_pasta_mae[CAMINHO_MAXIMO] = {'\0'};
   
    nomeptr = strrchr(origem, '\\') + 1; // Localiza o nome da pasta (Vem depois da última \)

    strcpy(nome_pasta_mae, nomeptr);
    sprintf(caminho_pasta_mae, "%s\\\\%s", destino, nome_pasta_mae);

    criar_diretorio(caminho_pasta_mae);

    strcpy(retorno, caminho_pasta_mae);
}

// ### Configurando pasta Backups ###
int existe_caminho_backups()
{
    char linha[CAMINHO_MAXIMO];
    FILE* fptr;

    fptr = fopen("data\\Caminho_Backups.txt", "r");

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

int existe_pasta_backups()
{
    /* Função que verifica a existência da pasta Backups, que conterá os backups 
       Retorna zero caso a pasta exista e o caminho para está seja válido */

    char nome_pasta[20];
    char* nameptr;

    printf("Verificando existência da pasta Backups...\n");

    FILE* fptr;
    fptr = fopen("data\\Caminho_Backups.txt", "r");

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
                    return 1;
                }
        
    
            } else { // Caso o nome não seja backups
                printf("O caminho não faz referência à pasta Backups.\n");
                return 1;
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
