#include <stdio.h>
#include <windows.h>

#include "src/arquivos/arquivos.h"
#include "configs/configs.h"

int adicionarParaBackup(char* caminho)
{
    int b = 0;

    // Adicionando '\n' ao fim do arquivo
    addEndline(caminho);

    // Inicializar o ponteiro de arquivo
    FILE *fptr;
    fptr = fopen("data\\ListaParaBackup.txt", "a");

    // Adiciona o arquivo à lista
    fprintf(fptr, caminho);

    fclose(fptr);
    fptr = NULL;

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

int verificar_caminho_ja_adicionado(char* caminho)
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

int copiar_diretorio(char* origem, char* destino)
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


// ### Lidando com a lista de pastas a serem copiadas ###
int existe_lista_backups() 
{
    /* Função que verifica a existência do arquivo Lista_backups*/
    FILE* fptr;

    fptr = fopen("data\\Lista_backup.txt", "r");

    if(fptr == NULL) {
        printf("Lista_backups.txt não existe.\n");
        return 0;

    } else {
        printf("Lista_backups.txt existe.\n");
        return 1;
    }
    fclose(fptr);
}

int existe_arquivo_para_copiar()
{
    /* Função que verifica se existe algum caminho para algum arquivo salvo.
       Os arquivos são especificados no documento "Lista_backup.txt" */

    char caminho[CAMINHO_MAXIMO];
    FILE* fptr;

    if(existe_lista_backups()) {
        fptr = fopen("data\\Lista_backup.txt", "r");

        if(fgets(caminho, CAMINHO_MAXIMO, fptr) != NULL) {
            printf("Existe caminho na Lista_Backups.\n");
            return 1;

        } else {
            printf("Não existem caminhos na Lista_Backups.\n");
            return 0;

        }
    } else {
        return 0;
    }
   fclose(fptr);
}

int adicionar_lista_backup(char* arquivo)
{
    /* Função que adiciona o caminho de uma pasta ou arquivo à lista
       para fazer backup. */

    FILE* fptr;

    fptr = fopen(CAMINHO_LISTA_TXT, "a");

    if(fptr == NULL) { // Não abriu corretamente
        printf("Houve um erro ao adicionar o arquivo à Lista_Backups.\nNão foi possível abrir o arquivo em: %s.\n", CAMINHO_LISTA_TXT);
        fclose(fptr);
        return 1;

    } else {
        fprintf(fptr, "%s\n", arquivo); // Adiciona ao arquivo
        printf("Arquivo/caminho adicionado com sucesso.\n");
        fclose(fptr);
        return 0;
    }
}

char **conseguir_arquivos_lista_backups(int* quant_caminhos, int* status) {
    /* Uma função que pega os arquivos presentes na Lista_Backups.txt
       e passa-os para uma matriz, então, retorna essa matriz.
       A quantidade de caminhos é retornada no argumento "quant_caminhos".
       O código de status de execução é retornado no argumento "status" (0=sucesso,1=erro). */

    int cont; // Conta a quantidade de arquivos
    int linhas = 5, colunas = CAMINHO_MAXIMO, linhasAntigas = 0;

    char **novaMatriz = NULL;
    char **arquivos = NULL;

    FILE *fptr = NULL;

    fptr = fopen(CAMINHO_LISTA_TXT, "r");
    
    if(fptr == NULL) {
        printf("Houve um erro ao ler Lista_Backups.txt.\n");
        *status = 1;
        return NULL;

    } else {
        // Alocando memória para "arquivos"
        arquivos = (char**) malloc(linhas * sizeof(char*));
            // Alocando para cada linha
        for(int i = 0; i < linhas; i++) {
            arquivos[i] = (char*) malloc(colunas * sizeof(char));
        }

        // Lendo as linhas do arquivo e passando para o array
        cont = 0;
        while(fgets(arquivos[cont], CAMINHO_MAXIMO, fptr)) {
            cont++;

            // Verificando a necessidade de realocar memória para a matriz (linhas insuficientes)
            if(cont == linhas) { // É necessário realocar memória
                printf("Realocando memória para 'arquivos'...\n");
                linhasAntigas = linhas;
                linhas += 5; // Aumentando as linhas novas
                novaMatriz = (char**) realloc(arquivos, linhas * sizeof(char*));

                if(novaMatriz == NULL) { // Erro ao realocar
                    printf("ERRO: Não foi possível realocar a matriz 'arquivos'.\n");
                    
                    // Liberando memória alocada
                    for(int i = 0; i < linhas; i++) {
                        free(arquivos[i]);
                    }
                    free(arquivos);
                    arquivos = NULL;

                    *status = 1;
                    return NULL;

                } else { // Sucesso ao realocar
                    arquivos = novaMatriz;
                        // Allocando/Inicializando cada nova linha
                    for(int i = linhasAntigas; i < linhas; i++) {
                        arquivos[i] = (char*) malloc(CAMINHO_MAXIMO * sizeof(char));
                    }
                }

                printf("Sucesso ao realocar memória.\n");
            }
        }
    } // Fim leitura dos arquivos

    // Retornos
    *quant_caminhos = cont;
    *status = 0;

    // Liberando ponteiros
    fclose(fptr);
    fptr = NULL;

    return arquivos;
}

void exibir_arquivos_salvos(char** caminhos_lista, int quantidade_caminhos) {
    /* Função que exibe ao usuário os arquivos presentes em Lista_Backups.
       Retorna a quantidade de arquivos salvos. */

    int cont = 0;

    printf("\n------------------------\n");
    printf("[ENDEREÇO] CAMINHO");
    printf("\n------------------------\n");
    for(int i = 0; i < quantidade_caminhos; i++) {
        printf("[%d] %s", i, caminhos_lista[i]);
    }
}

void adicionar_arquivos() {
    /* Sequência de procedimentos para adicionar um arquivo à lista para backup */

    char arquivo[CAMINHO_MAXIMO] = {'\0'};

    // Lendo flag
    printf("Digite o caminho do arquivo ('0' para sair): ");
    fgets(arquivo, CAMINHO_MAXIMO, stdin);
    arquivo[strcspn(arquivo, "\n")] = '\0';
    
    while(strcmp(arquivo, "0") != 0) {
        formatarCaminho(arquivo);
    
        adicionar_lista_backup(arquivo);

        // Releitura do flag
        printf("Digite o caminho do arquivo('0' para sair): "); 
        fgets(arquivo, CAMINHO_MAXIMO, stdin);
        arquivo[strcspn(arquivo, "\n")] = '\0';
    }
}

void remover_arquivos() {
    /* Procedimento que removerá arquivos da lista backups */
    int endereco;
    char scan_buff[5];
    char** caminhos_lista = NULL;
    
    
    int quant_caminhos;
    int status; // Conterá um código de status de execução

    caminhos_lista = conseguir_arquivos_lista_backups(&quant_caminhos, &status); // Consegue a matriz com os caminhos

    // Escrevendo matriz com os caminhos
    if(quant_caminhos>0) {
        exibir_arquivos_salvos(caminhos_lista, quant_caminhos);
        printf("------------------------\n");
    
        // Lendo e validando endereo
        printf("Digite o endereço do caminho a ser excluído (-1 para sair): ");
        fgets(scan_buff, 5, stdin);
        sscanf(scan_buff, "%d", &endereco);
            // Validando
        while(endereco < -1 || endereco > quant_caminhos - 1) {
            printf("Endereço inválido. Digite qualquer coisa para tentar novamente.\n");
            getchar();
            printf("\033c"); // Limpar tela
            // Relendo flag
            printf("Digite o endereço do caminho a ser excluído (-1 para sair): ");
            fgets(scan_buff, 5, stdin);
            sscanf(scan_buff, "%d", endereco);
        }

        // Removendo da lista
    }
    getchar();
}
