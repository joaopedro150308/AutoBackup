#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <errno.h>

#define CAMINHO_MAXIMO 260

void eliminarAspas(char* caminho)
{
    char novoCaminho[CAMINHO_MAXIMO];
    char* ptrAspas;
    
    char aspas = '"';
    char* ptrA = &aspas;

    ptrAspas = strtok(caminho, ptrA);
    while (ptrAspas != NULL)
    {
        strcat(novoCaminho, ptrAspas); // Adiciona a parte, sem aspas, à string de saida

        ptrAspas = strtok(NULL, ptrA); // Altera o token
    }

    memset(caminho, '\0', sizeof(caminho)); // Limpa o  caminho antigo
    strcpy(caminho, novoCaminho); // Atualiza o caminho com as alterações

    //novoCaminho[0] = '\0'; 
    memset(novoCaminho, '\0', sizeof(novoCaminho)); // Reseta novoCaminho
}

void duplicarContraBarras(char* caminho)
{
    char novoCaminho[CAMINHO_MAXIMO];

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
    eliminarAspas(caminho);
    duplicarContraBarras(caminho);
}   

int adicionarParaBackup(char* caminho)
{
    int b = 0;
    // Retorna um valor que representará verdadeiro ou false (0 para falso)
    // Adiciona um caminho a lista de arquivos para backup

    // Adicionando '\n' ao fim do arquivo
    addEndline(caminho);

    // Inicializar o ponteiro de arquivo
    FILE *fptr;
    fptr = fopen("ListaParaBackup.txt", "a");

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

int conseguir_caminhos(char* caminho) // Consegue todos os arquivos a partir de um dado caminho de diretório
{
    WIN32_FIND_DATA findData;
    HANDLE hFind;

    char caminhoBuffer[CAMINHO_MAXIMO];

    // Formatando caminho de ficheiro para conseguir todos os arquivos presentes
    int j = snprintf(caminhoBuffer, CAMINHO_MAXIMO, "%s\\\\*", caminho); // Adicionando "\\*"
    retirarEndlinde(caminhoBuffer);

    // Consegue o primeiro arquivo no dado caminho
    hFind = FindFirstFile(caminhoBuffer, &findData);

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

        char caminho_completo[CAMINHO_MAXIMO];
        snprintf(caminho_completo, CAMINHO_MAXIMO, "%s\\\\%s", caminho, findData.cFileName);
        
        if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // Se for diretório
        {
            conseguir_caminhos(caminho_completo);
        }
        else
        {
            printf("\nArquivo: %s\n", caminho_completo);
        }

    }  while (FindNextFile(hFind, &findData));
    

    FindClose(hFind);
    
    return 0; // Pardão de retorno bem-sucedido
}