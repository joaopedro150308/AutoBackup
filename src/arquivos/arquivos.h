#ifndef ARQUIVOS_H
#define ARQUIVOS_H

// ### CRUD de ARQUIVOS/caminhos ###
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

#endif