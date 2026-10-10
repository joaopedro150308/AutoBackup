#ifndef BACKUPS_H
#define BACKUPS_H

/*
Verifica existência do arquivo caminho_backups.txt e se há nele um possível caminho para a pasta Backups. Retorna 1 em caso positivo; e 0, caso contrário.
*/
int existe_caminho_backups();

/* Cria ou atualiza o arquivo que conterá o caminho para a pasta Backups. */
void criar_caminho_pasta_backups();

/* 
Função que consegue o caminho salvo para a pasta Backups. O caminho será copiado para o buffer "retorno". 
*/
int conseguir_caminho_Backups(char* retorno);

/* 
Função que verifica a existência da pasta Backups, que conterá os backups. Retorna um códio que representa um estado de execução ou um possível diagnóstico de erro.

1 - Sucesso. Pasta encontrada.
0 - Existe um caminho registrado, mas esse não é válido.
*/
int existe_pasta_backups();

/* Cria a pasta Backups no caminho salvo em caminho_backups.txt*/
int criar_pasta_backups();

#endif