/*Ficheiro que contém funções responsáveis por efetuar tudo o que tenha a ver com
selecção e realização das jogadas de ambos os jogadores.
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"
#include "types.h"

JOGADA* novaJogada(JOGADA* topo, int pX, int pY, int i, int j, int direcaoAtual, int possibleSwitches);
JOGADA* Add2Jogada(JOGADA* topo, int i, int j, int direcaoAtual, int possibleSwitches);

/*------------------------------------------------------------------------------
Nome: playerInput
Argumentos: BOARD tabState, GAMESTATE* topoEstados, int undoActive
Valor de Retorno: POSITION
Acção da função: Lê o input do jogador e devolve a jogada escolhida pelo mesmo.
------------------------------------------------------------------------------*/
POSITION playerInput (BOARD tabState, GAMESTATE* topoEstados, int undoActive) {
    
    int linha, coluna;
	int nc;
	int valid = FALSE;
	char ch;
	POSITION casaSelecionada;

	while (valid == FALSE) 		/*Loop que pede input ao jogador enquanto o mesmo ñ apresentar um input válido*/
	{
		fflush(stdin);
	   	printf("Jogada (linha coluna): ");
    	nc = scanf("%d %d", &linha, &coluna);	/*Faz scan do input do jogador e guarda o número de conversões numa variável*/
	
		fscanf(stdin, "%c", &ch);		/*Faz scan a tudo o que tenha ficado retido no buffer de input*/
	
		if(nc !=2 && ch == 'u' && !undoActive)
		{
			fprintf(stderr, "\nOPÇÃO UNDO Ñ DISPONÍVEL.\n");  /*Foi inserido o char "u" de modo a usar a função undo mas mesma*/
			valid = FALSE;									  /*ñ está ativa. Deste modo, o input é inválido.*/
		}
		else if (nc != 2 && ch == 'u' && undoActive) 	/*A opção undo está ativa e foi selecionada. Resta ver se é valida*/
		{
			if (topoEstados == NULL)
			{
				fprintf(stderr, "\nUNDO INVÁLIDO. Ñ EXISTEM JOGADAS ANTERIORES.\n\n");  /*Como a pilha dos estados está vazia, sabemos que*/ 
				valid = FALSE;															/*ñ existem jogadas anteriores. Deste modo, o input é inválido.*/
			}
			else 
			{
				casaSelecionada.cord1 = 0;			/*Existem jogadas anteriores e a opção undo está ativa. Deste modo, o input é válido*/
				casaSelecionada.cord2 = 0;			/*e a jogada pode ser realizada sendo por isso guardada para ser devolvida no fim do loop.*/
				valid = TRUE;						/*(Undo é representado pela jogada (0,0))*/
			}
		}
		else if (nc == 2) 	/*São introduzidas coordenadas de uma casa*/
		{
			if (linha < MIN || linha > GRID_SIZE || coluna < MIN || coluna > GRID_SIZE || tabState[linha][coluna] != HIPOTESE)
	    	{
	        	fprintf(stderr, "\nERRO: JOGADA INVÁLIDA.\nTENTE NOVAMENTE!\n\n");		/*O input excede as dimensões do tabuleiro*/
	        	valid = FALSE;															/*logo, é inválido.*/
	    	}
	    	else 
	    	{
				casaSelecionada.cord1 = linha;		/*O input está dentro dos limites do tabuleiro*/
				casaSelecionada.cord2 = coluna;		/*e é válido sendo o mesmo guardado e posteriormente devolvido pelo função.*/
				valid = TRUE;
	    	}	
		}
		else 
		{
			fprintf(stderr, "\nCONVERSÃO MAL-SUCEDIDA.\nTENTE NOVAMENTE!\n\n");		/*O input ñ faz sentido e o utilizador*/
			valid = FALSE;															/*é informado da invalidez dos dados que introduziu.*/
		}	
	}

    return casaSelecionada;			/*A casa selcionada é devolvida para que a jogada posso ser efetuada pelo "PieceSwitcher"*/
}

/*------------------------------------------------------------------------------
Nome: PieceSwicther
Argumentos: BOARD tabState, PLAYER* currentPlayer, PLAYER* otherPlayer, 
POSITION playerInput, JOGADA* TopoPilhaJogadas
Valor de Retorno: void
Acção da função: Faz a viragem das peças tendo em conta a jogada escolhida.
------------------------------------------------------------------------------*/
void PieceSwitcher (BOARD tabState, PLAYER* currentPlayer, PLAYER* otherPlayer, POSITION playerInput, JOGADA* TopoPilhaJogadas) {

	JOGADA* apTopo = TopoPilhaJogadas;
	int i, j;
	JOGADA* apAux = NULL;
	int direcaoAtual = 1;		/*A direção atual de viragem é guardada nesta variável. Isto representa o índice do vector de direções da jogada*/
								/*(Para mais informação sobre a forma como as direções são guardadas e avaliadas consultar documentação de "jogadasPossíveis")*/
	do
	{
		apAux = apTopo;
		direcaoAtual = 1;

		if (playerInput.cord1 == apTopo->partidaX && playerInput.cord2 == apTopo->partidaY)		/*Compara os valores do input com os valores da casa de partida de cada jogada*/
		{																						/*até que sejam iguais. Quando isso acontece, sabe que aquela é a jogada*/
			while(direcaoAtual <= 8)	/*Verifica direções enquanto não excede*/				/*selecionada pelo jogador e começa a avaliar parâmetros necessários.*/
			{							/*limite do vector de direções.*/

				/*A direção que está associada é verificada de modo a efetuar o algoritmo que lhe corresponde.*/
				if (apTopo->direction[direcaoAtual] == UP)
				{
					for(i = apTopo->partidaX; i != apTopo->VchegadaX[direcaoAtual]; i--)
					{
						j = apTopo->partidaY;							/*Percorre a direção selecionada enquanto a casa atual é dif da casa de chegada*/
						if (tabState[i][j] == otherPlayer->symbol)		/*associada à jogada e vira todas as peças do outro jogador de modo a passarem a ser*/
						{												/*peças do jogador que efetuou a jogada.*/
							tabState[i][j] = currentPlayer->symbol;		
							otherPlayer->nPecas--;						/*Cada peça virada é retirada do nº de peças do adversário*/
							currentPlayer->nPecas++;					/*e adicionada ao nº de peças do jogador.*/
						}
					}													/*Os restantes ifs e fors fazem exatamente o mesmo mas para as outras direções...*/
				}
				if (apTopo->direction[direcaoAtual] == DOWN)
				{
					for(i = apTopo->partidaX; i != apTopo->VchegadaX[direcaoAtual]; i++) 
					{
						j = apTopo->partidaY;
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == LEFT) 
				{
					for(j = apTopo->partidaY; j != apTopo->VchegadaY[direcaoAtual]; j--) 
					{
						i = apTopo->partidaX;
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == RIGHT) 
				{
					for(j = apTopo->partidaY; j != apTopo->VchegadaY[direcaoAtual]; j++) 
					{
						i = apTopo->partidaX;
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == R2TOP) 
				{
					for(i = apTopo->partidaX, j = apTopo->partidaY; i != apTopo->VchegadaX[direcaoAtual] && j != apTopo->VchegadaY[direcaoAtual]; i--, j--) 
					{
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == L2BOT) 
				{
					for(i = apTopo->partidaX, j = apTopo->partidaY; i != apTopo->VchegadaX[direcaoAtual] && j != apTopo->VchegadaY[direcaoAtual]; i++, j++) 
					{
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == R2BOT) 
				{
					for(i = apTopo->partidaX, j = apTopo->partidaY; i != apTopo->VchegadaX[direcaoAtual] && j != apTopo->VchegadaY[direcaoAtual]; i++, j--) 
					{
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				if (apTopo->direction[direcaoAtual] == L2TOP) 
				{
					for(i = apTopo->partidaX, j = apTopo->partidaY; i != apTopo->VchegadaX[direcaoAtual] && j != apTopo->VchegadaY[direcaoAtual]; i--, j++) 
					{
						if (tabState[i][j] == otherPlayer->symbol)
						{
							tabState[i][j] = currentPlayer->symbol;
							currentPlayer->nPecas++;
							otherPlayer->nPecas--;
						}
					}
				}
				direcaoAtual++;		/*Passamos à posição seguinte do vector de modo a verificar as várias direções de viragem associadas a uma jogada.*/
			}
		}
 
		apTopo = apTopo->prox;
		free(apAux);			/*Libertamos a memória das jogadas que já ñ são necessárias*/
		
	}while(apTopo != NULL);		/*Percorremos a pilha de jogadas até ao fim.*/
	
	return;
}

/*------------------------------------------------------------------------------
Nome: Add2Jogada
Argumentos: JOGADA* topo, int i, int j, int direcaoAtual, int possibleSwitches
Valor de Retorno: JOGADA*
Acção da função: Assiste a função "jogadasPossíveis" adicionando novas informa-
ções a uma jogada já existente.
------------------------------------------------------------------------------*/
JOGADA* Add2Jogada(JOGADA* topo, int i, int j, int direcaoAtual, int possibleSwitches) {

	/*Adicionada novos dados*/
	topo->VchegadaX[direcaoAtual] = i;
	topo->VchegadaY[direcaoAtual] = j;
	topo->direction[direcaoAtual] = direcaoAtual;
	topo->turnedPieces = topo->turnedPieces + possibleSwitches;

	return topo;	/*Retorna versão atualizada do topo da pilha de jogadas*/
}

/*------------------------------------------------------------------------------
Nome: novaJogada
Argumentos: JOGADA* topo, int pX, int pY, int i, int j, int direcaoAtual, int possibleSwitches
Valor de Retorno: JOGADA*
Acção da função: Assiste a função "jogadasPossíveis" na criação duma nova jogada.
------------------------------------------------------------------------------*/
JOGADA* novaJogada(JOGADA* topo, int pX, int pY, int i, int j, int direcaoAtual, int possibleSwitches) {

	JOGADA* jogadaNova = (JOGADA *) calloc(1, sizeof(JOGADA));		/*Cria estrutura de nova jogada alocando a memória necessária*/

	if (jogadaNova == NULL)			/*Verifica se a estrutura foi criada com sucesso*/
	{
		printf("\nErro na criação de nova jogada.\n");
		exit(0);
	}
	
	/*Adiciona os dados necessários à jogada*/
	jogadaNova->partidaX = pX;
	jogadaNova->partidaY = pY;
	jogadaNova->produtoDasCoordenadas = jogadaNova->partidaX * jogadaNova->partidaY;
	jogadaNova->VchegadaX[direcaoAtual] = i;
	jogadaNova->VchegadaY[direcaoAtual] = j;
	jogadaNova->direction[direcaoAtual] = direcaoAtual;
	jogadaNova->turnedPieces = possibleSwitches;
	jogadaNova->prox = topo;	/*Liga a nova jogada ao topo (estruturas ligadas)*/

	return jogadaNova;		/*Retorna o endereço da nova jogada para a mesma ser colocada no topo da pilha de jogadas*/
}

/*------------------------------------------------------------------------------
Nome: jogadasPossiveis
Argumentos: BOARD tabState, PLAYER currentPlayer, PLAYER otherPlayer, int* playable
Valor de Retorno: JOGADA*
Acção da função: Calcula todas as jogadas possíveis e insere numa pilha.
------------------------------------------------------------------------------*/
JOGADA* jogadasPossiveis (BOARD tabState, PLAYER currentPlayer, PLAYER otherPlayer, int* playable) {

    int l, c, i, j;

	/*Variávies que guardam valor das condições necessárias para uma jogada ser válida*/
    int switches = FALSE;
	int HasPiece = FALSE;

	int returnValue = FALSE; 	/*Guarda valor de retorno (se existem jogadas possíveis ou não)*/
	int finishedDirection = FALSE;		/*Indica se a direção atual já foi verificada ou ñ*/

	JOGADA* topo = NULL;	/*Topo da pilha que irá guardar todas as jogadas possíveis*/

	int direcaoAtual;		/*Indica qual a direção que está a ser verificada (as direções estão codificadas sob a forma de ints para serem mais fáceis de manipular)*/
	int possibleSwitches;	/*Regista o nº de peças que poderão ser viradas com cada jogada*/

    for (l = 1; l <= GRID_SIZE; l++)		/*Loop que vai casa a casa no tabuleiro de modo a verificar quais as casas que correspondem as jogadas possíveis*/
    {
        for (c = 1; c <= GRID_SIZE; c++)
        {
            if (tabState[l][c] == otherPlayer.symbol)  /*Caso seja detectada uma peça do adversário sabemos que pode ser criada (a partir duma posição adjacente)*/
            {										   /*uma linha contínua de peças correspondente a uma jogada válida.*/

                /*LINHA A LINHA*/

				possibleSwitches = 0;
                switches = FALSE;				/*Reset das condições e valores associados à direção*/
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = UP;
				
				/*Partindo da casa determinada na condição anterior, vão ser avaliadas todas as 8 direções sendo feitos alguns testes para verificar
				se correspondem a uma jogada válida. Se fôr este caso, funções auxiliares serão chamadas para criar estas jogadas e adicionar as mesmas à pilha.
				(Para percorrer uma direção basta somar ou subtrair 1 às linhas e/ou colunas. A soma ou subtração associada a cada direção está
				comentada no ficheiro "flipflop.h")*/
                for (i = l, j = c; i <= GRID_SIZE && i >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i--)
                {	/*O loop continua enquanto houveram peças, a direção ñ tiver sido já verificada e o limite do tabuleiro ñ fôr excedido.*/
				
                    if (tabState[i][j] == otherPlayer.symbol) /*Sempre que uma peça adversária fôr encontrada, deve ser somado 1 à contagem de peças a virar*/
                    {
                        switches = TRUE;		/*A condição: "Pelo menos uma peça é virada" é válida.*/
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)	/*Se ao longo da linha já tiver sido sido virada uma peça e fôr encontrada uma peça*/
					{														/*do jogador, sabemos que temos uma peça finalizadora da linha contínua necessária.*/
						HasPiece = TRUE;				
					}
                    if ((tabState[l+1][c] == VAZIO || tabState[l+1][c] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {	/*A casa adjacente à casa de partida na direção atual está vazia ou é já uma hipótese e as codnições necessárias estão satisfeitas => é uma jogada possível*/
                        tabState[l+1][c] = HIPOTESE;	/*A casa passa a ser uma hipótese.*/
                        returnValue = TRUE;				/*Existem jogadas possíveis.*/
						finishedDirection = TRUE;		/*A direção atual é dada por verificada.*/

						if (topo != NULL && topo->partidaX == l+1 && topo->partidaY == c)	/*Se já houver uma jogada criada com os mesmos valores de partida...*/
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);	/*É chamada uma função para adicionar os novos dados à jogada já existente.*/
						}
						else 	/*Caso contrário...*/
						{
							JOGADA* jogadaNova = NULL;														/*É criada uma nova jogada.*/
							jogadaNova = novaJogada(topo, l+1, c, i, j, direcaoAtual, possibleSwitches);	/*Guarda-se a informação necessária.*/
							topo = jogadaNova;																/*A jogada é colocada no topo da pilha.*/
						}
                    }
                }				/*O algortimo anterior repete-se para as outras direções...*/

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = DOWN;

                for (i = l, j = c; i <= GRID_SIZE && i >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i++)
                {

                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l-1][c] == VAZIO || tabState[l-1][c] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l-1][c] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l-1 && topo->partidaY == c) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l-1, c, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

                /*COLUNA A COLUNA*/

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = LEFT;

                for (j = c, i = l; j <= GRID_SIZE && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; j--)
                {

                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l][c+1] == VAZIO || tabState[l][c+1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l][c+1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;
						
						if (topo != NULL && topo->partidaX == l && topo->partidaY == c+1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l, c+1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = RIGHT;

                for (j = c, i = l; j <= GRID_SIZE && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; j++)
                {

                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l][c-1] == VAZIO || tabState[l][c-1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l][c-1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l && topo->partidaY == c-1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{						
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l, c-1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

                /*DIAGONALMENTE*/

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = R2TOP;

                for (i = l, j = c ; i <= GRID_SIZE && j <= GRID_SIZE && i >= 1 && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i--, j--)
                {
                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l+1][c+1] == VAZIO || tabState[l+1][c+1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l+1][c+1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l+1 && topo->partidaY == c+1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l+1, c+1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = L2BOT;

                for (i = l, j = c ; i <= GRID_SIZE && j <= GRID_SIZE && i >= 1 && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i++, j++)
                {
                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l-1][c-1] == VAZIO || tabState[l-1][c-1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l-1][c-1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l-1 && topo->partidaY == c-1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l-1, c-1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = R2BOT;

                for (i = l, j = c ; i <= GRID_SIZE && j <= GRID_SIZE && i >= 1 && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i++, j--)
                {
                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;				
					}
                    if ((tabState[l-1][c+1] == VAZIO || tabState[l-1][c+1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l-1][c+1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l-1 && topo->partidaY == c+1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l-1, c+1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }

				possibleSwitches = 0;
                switches = FALSE;
				HasPiece = FALSE;
				finishedDirection = FALSE;
				direcaoAtual = L2TOP;

                for (i = l, j = c ; i <= GRID_SIZE && j <= GRID_SIZE && i >= 1 && j >= 1 && tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && !finishedDirection; i--, j++)
                {
                    if (tabState[i][j] != VAZIO && tabState[i][j] != HIPOTESE && tabState[i][j] != currentPlayer.symbol)
                    {
                        switches = TRUE;
						possibleSwitches++;
                    }
					if (tabState[i][j] == currentPlayer.symbol && switches)
					{
						HasPiece = TRUE;			
					}
                    if ((tabState[l+1][c-1] == VAZIO || tabState[l+1][c-1] == HIPOTESE) && tabState[l][c] != currentPlayer.symbol && switches && HasPiece)
                    {
                        tabState[l+1][c-1] = HIPOTESE;
                        returnValue = TRUE;
						finishedDirection = TRUE;

						if (topo != NULL && topo->partidaX == l+1 && topo->partidaY == c-1) 
						{
							topo = Add2Jogada(topo, i, j, direcaoAtual, possibleSwitches);
						}
						else 
						{
							JOGADA* jogadaNova = NULL;
							jogadaNova = novaJogada(topo, l+1, c-1, i, j, direcaoAtual, possibleSwitches);
							topo = jogadaNova;
						}
                    }
                }        
            }
        }
    }
	
    *playable = returnValue;		/*O valor de playable é modificado indicando se é possível jogar ou ñ*/

	return topo;		/*O topo da pilha de jogadas é devolvido de forma a poder ser usado por outras funções*/
}

/*------------------------------------------------------------------------------
Nome: AI_algorithm
Argumentos: JOGADA* topoPilhaJogadas, BOARD tabState, PLAYER* jogadorAtual
Valor de Retorno: POSITION
Acção da função: Escolhe a melhor jogada (vira mais peças e tem coordenada inf).
------------------------------------------------------------------------------*/
POSITION AI_algorithm (JOGADA* topoPilhaJogadas, BOARD tabState, PLAYER* jogadorAtual) {

	POSITION bestPlay;					/*Variável que vai ser devolvida e contém as coordenadas da casa escolhida pela IA*/
	JOGADA* apTopo = topoPilhaJogadas;
	JOGADA* tempHolding = NULL;
	JOGADA* proxJogada = NULL;
	char razao[12] = "indefinido";		/*String que descreve a razão pela qual determinada jogada foi escolhida (tem valor default "indefinido" visto que*/
										/*que caso ambas as coordenadas ñ sejam inf e o resto seja igual ñ há critério definido para escolher.*/
										/*Nestas situações a IA acabará por escolher a que tiver sido a última a ser avaliada entre as jogadas que estão "empatadas").*/
	/*Guardar em temp o topo*/
	tempHolding = apTopo;
	proxJogada = apTopo->prox;

	if (proxJogada != NULL)
	{	
		while (proxJogada != NULL) {
			/*Compara o que está em temp com o que está em topo->prox*/
			if (tempHolding->turnedPieces < proxJogada->turnedPieces)
			{
				tempHolding = proxJogada; 		/*Se o número de peças viradas numa jogada for maior que a esolhida até aqui, substituir*/
				strcpy(razao, "mais peças");
			}
			else if (tempHolding->turnedPieces == proxJogada->turnedPieces	&& 
				tempHolding->partidaX > proxJogada->partidaX && tempHolding->partidaY > proxJogada->partidaY)
			{
				tempHolding = proxJogada;		/*Se o número de peças viradas fôr igual mas as coordenadas forem inf, substituir*/
				strcpy(razao, "coord inf");
			}
			else if (tempHolding->turnedPieces == proxJogada->turnedPieces && tempHolding->produtoDasCoordenadas > proxJogada->produtoDasCoordenadas) 
			{
				tempHolding = proxJogada;		/*Se o número de peças viradas fôr igual e as coordenadas não forem ambas inf, verificar qual dos prod é inf e substituir*/
				strcpy(razao, "prod inf");
			}
			
			apTopo = proxJogada;		
			proxJogada = apTopo->prox;		/*Passa à jogada seguinte*/
			
			/*Continua até que topo->prox == NULL*/
		}
	} 

	/*Coloca o que está em temp na bestPlay de modo a devolver a melhor jogada*/
	bestPlay.cord1 = tempHolding->partidaX;
	bestPlay.cord2 = tempHolding->partidaY;

	/*Coloca peça da IA na casa escolhida e acrescenta mais uma peça ao nº de peças da IA*/
	tabState[bestPlay.cord1][bestPlay.cord2] = jogadorAtual->symbol;
    jogadorAtual->nPecas++;

	/*Apresenta a jogada escolhida e a razão pela qual a mesma foi selecionada*/
	printf("\nMELHOR JOGADA: %d %d\nRAZÃO: %s\n", bestPlay.cord1, bestPlay.cord2, razao);
	fflush(stdout);
	
	return bestPlay;		/*Retorna a melhor jogada para que possa ser executada pela função "PieceSwitcher"*/
}

/*------------------------------------------------------------------------------
Nome: TabCleaner
Argumentos: BOARD tabState
Valor de Retorno: void
Acção da função: Apaga as jogadas possíveis do tabuleiro.
------------------------------------------------------------------------------*/
void TabCleaner (BOARD tabState) {

    int l, c;

    for (l = 1; l <= GRID_SIZE; l++)
    {
        for (c = 1; c <= GRID_SIZE; c++)        /*Verifica cada casa*/
        {                                       
            if (tabState[l][c] == HIPOTESE)     /*Determina se era uma hipótese*/
            {
                tabState[l][c] = VAZIO;         /*Caso seja, apaga de modo a preparar o tabuleiro*/
            }                                   /*para a próxima jogada (hipóteses de jogada diferentes serão inseridas)*/
        }
    }
	
    return;
}