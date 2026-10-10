#ifndef ARQUIVOS_H
#define ARQUIVOS_H

/*
Retorna um valor que representará verdadeiro ou false (0 para falso) Adiciona um caminho a lista de arquivos para backup
*/
int adicionarParaBackup(char* caminho);

/* Verifica o tipo da estrutura referida pelo caminho. Retorna um código: -1 = caminho inválido, 1 = (diretório), 0 = arquivo */
int verificarTipoCaminho(char* caminho);

/* Verifica se um dado caimnho já foi adicionada à pasta backups*/
int verificar_caminho_ja_adicionado(char* caminho);

/* Consegue a origem de um caminho. Não sei o que isso quer dizer :p */
void conseguir_origem(char* caminho);

/* Cria um diretório no caminho especificado. Retorna um código de execução bem sucedida */
int criar_diretorio(char* caminho);

/* Copia todos os arquivos, pastas e subpastas a partir de um dado caminho (origem) para um outro local (destino) */
int copiar_diretorio(char* origem, char* destino);


/* Função que cria uma pasta mãe, pasta que guarda outras pastas e arquivos. É a pasta de nível mais alto de um dado caminho. Ao criar a nova pasta, seu caminho é copiado para "retorno". Se este for NULL, não haverá retorno. */
int criar_pasta_mae(char* origem, char* destino, char* retorno);




/* Função que verifica a existência do arquivo Lista_backups*/
int existe_lista_backups();


/* Função que verifica se existe algum caminho para algum arquivo salvo.
   Os arquivos são especificados no documento "Lista_backup.txt" */
int existe_arquivo_para_copiar();

/* Função que adiciona o caminho de uma pasta ou arquivo à lista
   para fazer backup. */
int adicionar_lista_backup(char* arquivo);


/* Uma função que pega os arquivos presentes na Lista_Backups.txt
   e passa-os para uma matriz, então, retorna essa matriz.
   A quantidade de caminhos é retornada no argumento "quant_caminhos".
   O código de status de execução é retornado no argumento "status" (0=sucesso,1=erro). */
char **conseguir_arquivos_lista_backups(int* quant_caminhos, int* status);

/* 
Função que exibe ao usuário os arquivos presentes em Lista_Backups.
Retorna a quantidade de arquivos salvos. 
*/
void exibir_arquivos_salvos(char** caminhos_lista, int quantidade_caminhos);

/* Sequência de procedimentos para adicionar um arquivo à lista para backup */
void adicionar_arquivos();

/* Procedimento que removerá arquivos da lista backups */
void remover_arquivos();

#endif