#ifndef UTEIS_H
#define UTEIS_H

#include <stdio.h>
#include <string.h>

/* Limpa o terminal */
void limpar(void) 
{
    printf("\033c");
}

/* Faz uma linha */
void linha(char simbolo, int quantidade);

/* Escreve um texto centralizado em um determinado número de espaços */
void escrever_centralizado(char* texto, int espacos);

/* Faz um título */
void fazer_titulo(char* titulo, int espacos);


#endif