/*Ficheiro que contém as funções responsáveis por apresentar informação no ecrã
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"
#include "types.h"

/*------------------------------------------------------------------------------
Nome: tabPrint
Argumentos: BOARD
Valor de Retorno: void
Acção da função: Apresenta o tabuleiro no ecrã.
------------------------------------------------------------------------------*/
void tabPrint (BOARD tabState) {

    int l = 0, c = 0;
    
    printf("\n");

    for (l = 0; l <= GRID_SIZE; l++)
    {
        for (c = 0; c <= GRID_SIZE; c++)
        {                                       /*Mostra o char presente em cada casa da matriz*/
            printf("%c ", tabState[l][c]);      /*(o espaço é adicionado para formatar o tabuleiro corretamente).*/
        }
        printf("\n");                           /*Passa para a próxima linha no ecrã visto estar prestes a apresentar*/
    }                                           /*a linha seguinte da matriz.*/
    printf("\n");
    return;
}

/*------------------------------------------------------------------------------
Nome: displayPlayerInfo
Argumentos: PLAYER* currentPlayer
Valor de Retorno: void
Acção da função: Apresenta informação acerca de quem está a jogar no momento.
------------------------------------------------------------------------------*/
void displayPlayerInfo (PLAYER currentPlayer) {

	char tipoDeJogador[10];     /*Guarda a string correspondente ao tipo de jogador para ser posteriormente apresentada.*/

	if (currentPlayer.playerType == HUMANO)         /*Verifica se o jogador é Humano ou IA e atribui o valor adequado*/
	{                                               /*à string referida.*/
		strcpy(tipoDeJogador, "Humano");
	}
	else strcpy(tipoDeJogador, "IA");
	
    printf("Jogador %d (%s) (%c)\n", currentPlayer.nJogador, tipoDeJogador, currentPlayer.symbol);      /*Apresenta a informção do jogador atual.*/

    return;
}

/*------------------------------------------------------------------------------
Nome: score
Argumentos: PLAYER player1, PLAYER player2
Valor de Retorno: void
Acção da função: Apresenta a pontuação de cada jogador no momento.
------------------------------------------------------------------------------*/
void score (PLAYER player1, PLAYER player2) {

	printf("PONTUAÇÃO: %d vs %d\n", player1.nPecas, player2.nPecas);
	fflush(stdout);
	
	return;
}

/*------------------------------------------------------------------------------
Nome: winner
Argumentos: PLAYER player1, PLAYER player2
Valor de Retorno: void
Acção da função: Apresenta o vencedor do jogo no final do mesmo.
------------------------------------------------------------------------------*/
void winner (PLAYER jogador1, PLAYER jogador2) {

	if (jogador1.nPecas > jogador2.nPecas) 
	{
		printf("\nO VENCEDOR É O JOGADOR 1 (HUMANO)!\n");
	}                                                                  /*Verifica qual é o jogador com maior nº de peças,*/
	else if (jogador2.nPecas > jogador1.nPecas)                        /*apresentando o nº e tipo do mesmo no ecrã.*/
	{
		printf("\nO VENCEDOR É O JOGADOR 2 (IA)!\n");
	}
	else 
	{
		printf("\nÉ UM EMPATE!\n");
	}
	
	return;
}