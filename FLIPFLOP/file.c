/*Ficheiro que contém funções responsáveis por efetuar o registo do jogo no ficheiro
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"
#include "types.h"

/*------------------------------------------------------------------------------
Nome: tabPrintFicheiro
Argumentos: BOARD tabState, FILE* Ficheiro
Valor de Retorno: void
Acção da função: Análogo ao tabPrint mas escreve no ficheiro. 
(Consultar ficheiro "screen.c" para mais informações)
------------------------------------------------------------------------------*/
void tabPrintFicheiro (BOARD tabState, FILE* Ficheiro) {

    int l = 0, c = 0;
    
    fprintf(Ficheiro, "\n");
	fflush(Ficheiro);
	
    for (l = 0; l <= GRID_SIZE; l++)
    {
        for (c = 0; c <= GRID_SIZE; c++)
        {
            fprintf(Ficheiro, "%c ", tabState[l][c]);
			fflush(Ficheiro);
        }
        fprintf(Ficheiro, "\n");
		fflush(Ficheiro);
    }
    fprintf(Ficheiro, "\n");
	fflush(Ficheiro);
	
    return;
}

/*------------------------------------------------------------------------------
Nome: displayPlayerInfoFicheiro
Argumentos: PLAYER currentPlayer, FILE* Ficheiro
Valor de Retorno: void
Acção da função: Análogo ao displayPlayerInfo mas escreve no ficheiro.
(Consultar ficheiro "screen.c" para mais informações)
------------------------------------------------------------------------------*/
void displayPlayerInfoFicheiro (PLAYER currentPlayer, FILE* Ficheiro) {

	char tipoDeJogador[10];
	
	if (currentPlayer.playerType == HUMANO) 
	{
		strcpy(tipoDeJogador, "Humano");
	}
	else strcpy(tipoDeJogador, "IA");
	
    fprintf(Ficheiro, "Jogador %d (%s) (%c)\n", currentPlayer.nJogador, tipoDeJogador, currentPlayer.symbol);
    fflush(Ficheiro);
    return;
}

/*------------------------------------------------------------------------------
Nome: scoreFicheiro
Argumentos: PLAYER player1, PLAYER player2, FILE* Ficheiro
Valor de Retorno: void
Acção da função: Análogo ao score mas escreve no ficheiro.
(Consultar ficheiro "screen.c" para mais informações)
------------------------------------------------------------------------------*/
void scoreFicheiro (PLAYER player1, PLAYER player2, FILE* Ficheiro) {

    fprintf(Ficheiro,"PONTUAÇÃO: %d vs %d\n", player1.nPecas, player2.nPecas);
    fflush(Ficheiro);

    return;
}

/*------------------------------------------------------------------------------
Nome: endingFicheiro
Argumentos: PLAYER jogador1, PLAYER jogador2, FILE* Ficheiro
Valor de Retorno: void
Acção da função: Escreve informações relativas ao fim do jogo no ficheiro.
(Consultar ficheiro "screen.c" para mais informações)
------------------------------------------------------------------------------*/
void endingFicheiro (PLAYER jogador1, PLAYER jogador2, FILE* Ficheiro) {

	if (jogador1.nPecas > jogador2.nPecas) 
	{
		fprintf(Ficheiro, "\nO VENCEDOR É O JOGADOR 1 (HUMANO)!\n");
	}
	else if (jogador2.nPecas > jogador1.nPecas) 
	{
		fprintf(Ficheiro, "\nO VENCEDOR É O JOGADOR 2 (IA)!\n");
	}
	else 
	{
		fprintf(Ficheiro, "\nÉ UM EMPATE!\n");
	}
	
	return;
}

/*------------------------------------------------------------------------------
Nome: Ledger
Argumentos: GAMESTATE estadoDoJogo, PLAYER currentPlayer, FILE* Ficheiro
Valor de Retorno: void
Acção da função: Função mãe que chama as funções que fazem o resgisto dos dados
no ficheiro. (Consultar ficheiro "screen.c" para mais informações)
------------------------------------------------------------------------------*/
void Ledger (GAMESTATE estadoDoJogo, PLAYER currentPlayer, FILE* Ficheiro) {
	
    tabPrintFicheiro(estadoDoJogo.tabuleiro, Ficheiro);
    displayPlayerInfoFicheiro(currentPlayer, Ficheiro);
    scoreFicheiro(estadoDoJogo.jogador1, estadoDoJogo.jogador2, Ficheiro);
		
	return;
}