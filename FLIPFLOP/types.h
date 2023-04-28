/*Ficheiro que contém definição de novos tipos usados na construção do programa
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"

/*Estrutura que contém informação duma jogada.*/
typedef struct jogada					
{
    int partidaX, partidaY;					/*Coordenadas de partida (onde a peça é colocada).*/
	int VchegadaX[N_DIRECOES+1];			/*Coordenadas de chegada (são inseridas num vector devido ao facto*/
	int VchegadaY[N_DIRECOES+1];			/*da mesma jogada poder virar peças em + do que 1 direção).*/
	int direction[N_DIRECOES+1];			/*Vector que guarda todas as direções em que peças são viradas.(as direções estão codificadas sob a forma de ints)*/
	int turnedPieces;						/*Nº de peças que cada jogada permite virar.*/
	int produtoDasCoordenadas;				/*Permite a tomada de decisões por parte da AI.*/
	struct jogada* prox;					/*Apontador que permite criação de pilha com todas as jogadas possíveis*/
											/*interligando as estruturas que representam cada jogada.*/
}JOGADA;


/*Estrutura usada para selecionar uma posição no tabuleiro*/
typedef struct position
{
	int cord1;			/*Composta por duas coordenadas*/
	int cord2;			/*(linha e coluna, respectivamente).*/

}POSITION;


typedef char BOARD[BOARDDIM][BOARDDIM];     /*Definição do tabuleiro como sendo uma matriz 9x9*/


/*Estrutura que contém informações do jogador*/
typedef struct player
{
    int nPecas;			/*Número de peças do jogador em cada estado do jogo.*/
    char symbol;		/*Símbolo que representa peças do jogador no tabuleiro.*/
    int nJogador;		/*Nº do jogador (1 ou 2).*/
	char playerType;	/*Indica se é um jogador humano ou IA.*/

}PLAYER;


/*Estrutura que contém todas as informações acerca do estado do jogo*/
typedef struct GameState 
{
	BOARD tabuleiro;		/*Isto inclui: o tabuleiro, os jogadores 1 e 2, o nº da jogada atual,*/
	PLAYER jogador1;		/*o estado da opção undo(ativo ou não), se existem jogadas possíveis para cada*/
	PLAYER jogador2;		/*jogador e por fim um apontador que aponta para o estado anterior*/
	int nJogadas;			/*permitindo assim ligar todos os estados do jogo (necessário para UNDO).*/
	int undoActive;
	int playable1;
	int playable2;
	struct GameState* PreviousState;

}GAMESTATE;