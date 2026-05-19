#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

void eliminarAspas(char* caminho)
{
    char novoCaminho[260];
    char* ptrAspas;
    
    char aspas = '"';
    char* ptrA = &aspas;

    ptrAspas = strtok(caminho, ptrA);
    while (ptrAspas != NULL)
    {
        strcat(novoCaminho, ptrAspas); // Adiciona a parte, sem aspas, à string de saida

        ptrAspas = strtok(NULL, ptrA); // Altera o token
    }

    strcpy(caminho, novoCaminho); // Atualiza o caminho com as alterações

    //novoCaminho[0] = '\0'; 
    memset(novoCaminho, '\0', sizeof(novoCaminho)); // Reseta novoCaminho
}

void duplicarContraBarras(char* caminho)
{
    char novoCaminho[260];

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

void formatarCaminho(char* caminho)
{
    /*Formata o caminho especificado (colocando contra-barras duplas, por exemplo)*/
    eliminarAspas(caminho);
    duplicarContraBarras(caminho);
    addEndline(caminho);
}   

int adicionarParaBackup(char* caminho)
{
    int b = 0;
    // Retorna um valor que representará verdadeiro ou false (0 para falso)
    // Adiciona um caminho a lista de arquivos para backup

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

void verificarTipoCaminho(char* caminho)
{
    struct stat caminho_stat;

    if (stat(caminho, &caminho_stat) != 0)
    {
        printf("Erro acessando o caminho: %s\n", strerror(errno));
        return;
    }

    if (S_ISDIR(caminho_stat.st_mode))
    {
        printf("É um diretório.\n");
    }
    else if (S_ISREG(caminho_stat.st_mode))
    {
        printf("É um arquivo regular\n");
    }
    else
    {
        printf("Não é uma pasta e nem um arquivo.\n");
    }
}