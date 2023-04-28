/*Ficheiro que contém funções responsáveis por guardar e atualizar o estado do jogo
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"
#include "types.h"

/*------------------------------------------------------------------------------
Nome: stateStorer
Argumentos: GAMESTATE* apPilha, GAMESTATE estadoDoJogo
Valor de Retorno: GAMESTATE*
Acção da função: Atualiza o estado do jogo guardando todos numa pilha que será
usada para a implementação da funcionalidade UNDO.
------------------------------------------------------------------------------*/
GAMESTATE* stateStorer (GAMESTATE* apPilha, GAMESTATE estadoDoJogo) {

	int i, j;
	GAMESTATE* apAux = apPilha;
	apPilha = (GAMESTATE*) calloc(1, sizeof(GAMESTATE));	/*Cria novo estado*/
	apPilha->PreviousState = apAux;						/*Guarda estado anterior no apontador do novo estado*/

	/*Guarda as informações atuais no novo estado*/
	apPilha->jogador1 = estadoDoJogo.jogador1;
	apPilha->jogador2 = estadoDoJogo.jogador2;
	apPilha->nJogadas = estadoDoJogo.nJogadas;
	
	for(i = 0; i < BOARDDIM; i++)
	{
		for(j = 0; j < BOARDDIM; j++) 
		{
			apPilha->tabuleiro[i][j] = estadoDoJogo.tabuleiro[i][j];
		}
	}
	
	return apPilha;		/*Retorna endereço do novo topo da pilha*/
}

/*------------------------------------------------------------------------------
Nome: undo
Argumentos: GAMESTATE* apPilha, GAMESTATE* estadoDoJogo
Valor de Retorno: GAMESTATE*
Acção da função: Atualiza o estado do jogo guardando todos numa pilha que será
usada para a implementação da funcionalidade UNDO.
------------------------------------------------------------------------------*/
GAMESTATE* undo (GAMESTATE* apPilha, GAMESTATE* estadoDoJogo) {

	int i, j;
	GAMESTATE* apAux = apPilha;
	
	/*Vai à pilha buscar as informações do último estado guardado e transforma o estado atual no estado anterior*/
	estadoDoJogo->jogador1 = apPilha->jogador1;
	estadoDoJogo->jogador2 = apPilha->jogador2;
	estadoDoJogo->nJogadas = apPilha->nJogadas;
	
	for(i = 0; i < BOARDDIM; i++)
	{
		for(j = 0; j < BOARDDIM; j++) 
		{
			estadoDoJogo->tabuleiro[i][j] = apPilha->tabuleiro[i][j];
		}
	}

	apPilha = apPilha->PreviousState;	/*Coloca pilha a apontar para o estado anterior ao último estado guardado*/
	free(apAux);						/*e liberta o último estado. Deste modo se a função voltar a ser chamada (fôr feito undo novamente)*/
										/*a pilha vai estar a apontar para o estado anterior ao "novo" estado atual.*/

	return apPilha;						/*Retorna o novo endereço do topo da pilha*/
}

/*------------------------------------------------------------------------------
Nome: GameIsOver
Argumentos: GAMESTATE estadoDoJogo
Valor de Retorno: int
Acção da função: Verifica se o alguma das condições de finalização do jogo são
verdadeiras. Caso alguma delas seja, retorna 1 (TRUE) e termina o jogo. Caso 
contrário retorna 0 (FALSE) e o jogo pode continuar.
------------------------------------------------------------------------------*/
int GameIsOver (GAMESTATE estadoDoJogo) {

	int NoMorePieces = (estadoDoJogo.jogador1.nPecas == 0 || estadoDoJogo.jogador2.nPecas == 0);
	int NoMorePlays = ((estadoDoJogo.playable1 || estadoDoJogo.playable2) == 0);
	int NoAvalaibleSpace = (estadoDoJogo.jogador1.nPecas + estadoDoJogo.jogador2.nPecas == 64);

	if(NoMorePieces || NoMorePlays || NoAvalaibleSpace) 
	{
		return TRUE;
	}
	else return FALSE;
}