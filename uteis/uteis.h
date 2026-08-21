#include <stdio.h>

void limpar(void) /* Limpa o terminal */
{
    printf("\033c");
}

void pular(void)
{
    /* Pular linha */
    printf("\n");
}

void linha(char simbolo, int quantidade)
{
    /* Faz uma linha */

    for(int i = 0; i < quantidade; i++) {
        printf("%c", simbolo);
    }
}

void escrever_centralizado(char* texto, int espacos)
{
    /* Escreve um texto centralizado em um determinado número de espaços */

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }

    printf("%s", texto);

    for(int i = 0; i < espacos; i++) {
        printf(" ");
    }
}

void fazer_titulo(char* titulo, int espacos)
{
    int linhas_tamanho;
    linhas_tamanho = strlen(titulo) + (2*espacos);

    linha('=', linhas_tamanho);
    pular();
    escrever_centralizado(titulo, espacos);
    pular();
    linha('=', linhas_tamanho);

}