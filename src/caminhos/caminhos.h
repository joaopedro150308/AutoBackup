#ifndef CAMINHOS_H
#define CAMINHOS_H


/* Função que limpa as aspas de um caminho(sting). Útil quando o usuário copia um endereço de um arquivo e cola-o diretamente no cmd. */
void eliminarAspas(char* caminho);

/* Duplica as contra barras de um caminho. */
void duplicarContraBarras(char* caminho);

/* Adiciona uma quebra de linha '\n' ao caminho */
void addEndline(char* caminho);

/* Retira uma quebra de linha do caminho */
void retirarEndlinde(char* caminho);

/* Adiciona, ao final do caminho, a expressão "//*" que representa um caractere para retornar todos os caminhos de arquivos presentes naquele diretório */
void addCharCuringa(char* caminho);

/* Duplica contra barras e elimina as aspas do caminho. */
void formatarCaminho(char* caminho);


#endif