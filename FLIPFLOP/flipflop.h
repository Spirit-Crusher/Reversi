/*Ficheiro que contém definições utéis à construção e compreensão do programa
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BOARDDIM 9	    /*Tamanho do tabuleiro total (incluindo numeração das linhas e colunas)*/
#define GRID_SIZE 8     /*Tamanho real do tabuleiro (em que é possível colocar peças)*/
#define MIN 1			/*Valor mínimo de qualquer coordenada duma jogada possível*/
#define UNDO 0 			/*Definição do valor das coordenadas da casa que representará undo*/

/*--------------------------------------------------------------------------------------------
Definição dos símbolos que representam os vaŕios estados possíveis de cada casa do tabuleiro*/

#define CRUZ 'X'		
#define BOLA 'O'
#define VAZIO '.'
#define HIPOTESE 'P'
/*--------------------------------------------------------------------------------------------
Definição de valores boleanos para tornar o código mais fácil de entender*/

#define TRUE 1
#define FALSE 0
/*--------------------------------------------------------------------------------------------
Definição dos char que reprensentam cada tipo de jogador*/

#define HUMANO 'H'
#define AI 'I'
/*--------------------------------------------------------------------------------------------
Codificação das 8 direções existentes no tabuleiro sob a forma de int de forma
a serem mais fáceis de manipular comparativamente a uma string.*/
	
#define N_DIRECOES 8

#define UP 1        /* -1 0, l e c respectivamente */
#define DOWN 2      /* +1 0, l e c respectivamente */
#define LEFT 3      /* 0 -1, l e c respectivamente */
#define RIGHT 4     /* 0 +1, l e c respectivamente */
#define R2TOP 5     /* -1 -1, l e c respectivamente */
#define L2BOT 6     /* +1 +1, l e c respectivamente */
#define R2BOT 7     /* +1 -1, l e c respectivamente */
#define L2TOP 8     /* -1 +1, l e c respectivamente */
/*-----------------------------------------------------------------------------------------*/