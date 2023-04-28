/*Ficheiro principal
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "flipflop.h"
#include "types.h"

void tabInit (BOARD tabuleiroInicial);
void playerInit (PLAYER* jogador1, PLAYER* jogador2, char* symbolArg);
FILE* argumentReader (char* argv[], int argc, GAMESTATE* estadoDoJogo, FILE* Ficheiro);
void tabPrint (BOARD tabState);
void displayPlayerInfo (PLAYER currentPlayer);
POSITION playerInput (BOARD tabState, GAMESTATE* topoEstados, int undoActive);
void PieceSwitcher (BOARD tabState, PLAYER* currentPlayer, PLAYER* otherPlayer, POSITION playerInput, JOGADA* TopoPilhaJogadas);
JOGADA* jogadasPossiveis (BOARD tabState, PLAYER currentPlayer, PLAYER otherPlayer, int* playable);
POSITION AI_algorithm (JOGADA* topoPilhaJogadas, BOARD tabState, PLAYER* jogadorAtual);
void TabCleaner (BOARD tabState);
void score (PLAYER player1, PLAYER player2);
void winner (PLAYER jogador1, PLAYER jogador2);
GAMESTATE* stateStorer (GAMESTATE* apPilha, GAMESTATE estadoDoJogo);
GAMESTATE* undo (GAMESTATE* apPilha, GAMESTATE* estadoDoJogo);
int GameIsOver (GAMESTATE estadoDoJogo);
void tabPrintFicheiro (BOARD tabState, FILE* Ficheiro);
void displayPlayerInfoFicheiro (PLAYER currentPlayer, FILE* Ficheiro);
void scoreFicheiro (PLAYER player1, PLAYER player2, FILE* Ficheiro);
void endingFicheiro (PLAYER jogador1, PLAYER jogador2, FILE* Ficheiro);
void Ledger (GAMESTATE estadoDoJogo, PLAYER currentPlayer, FILE* Ficheiro);

/*------------------------------------------------------------------------------
Nome: exitMessage
Argumentos: void
Valor de Retorno: void
Acção da função: Função que apresenta uma mensagem quando o programa termina
usando funcionalidade atexit do stdlib.
------------------------------------------------------------------------------*/
void exitMessage (void) {
    
    printf("\n########################\n");
	printf("#                      #\n");
    printf("#  PROGRAMA TERMINADO  #\n");
	printf("#                      #");
    printf("\n########################\n");
}


int main (int argc, char* argv[]) {

	GAMESTATE estadoDoJogo;		/*Criação de variável que guarda o estado do jogo em cada momento.*/
	POSITION casaSelecionada;	/*Variável que será utilizada para selecionar a casa escolhida por cada um dos jogadores em cada jogada.*/
	int undone;					/*Indica se, naquela jogada, foi utilizado o undo.*/

	FILE* Ficheiro = NULL;				/*Criação de variável que guardará o endereço do ficheiro em que vai ser feito o registo.*/
	GAMESTATE* apPilhaEstados = NULL;	/*Variáveis que guardam o endereço do topo de duas pilhas:*/
	JOGADA* topoPilhaJogadas = NULL;	/*Pilha dos estados do jogo e pilha de jogadas possíveis, respectivamente.*/
	estadoDoJogo.undoActive = FALSE;	/*Por default, a opção undo ñ está activa. Deve ser o utilizador a ativar a mesma através do terminal.*/
	estadoDoJogo.nJogadas = 1;			/*Inicia o contador de jogadas a 1*/
	
	atexit(exitMessage);		/*Estabelece qual é a função que será executada quando o programar terminar.*/

	system("clear");		/*Antes do jogo começar, limpa o terminal para que este só apresente informação relacionada com o jogo.*/
	printf("\nWELCOME TO FLIP-FLOP!\n\n");		/*Mensagem de boas vindas*/

    tabInit(estadoDoJogo.tabuleiro);	/*Inicialização do tabuleiro*/

	Ficheiro = argumentReader(argv, argc, &estadoDoJogo, Ficheiro);		/*Definição de ficheiro onde será tudo registado*/

	/*Testes de verificação do estabelecimento correcto das condições iniciais*/
	if (estadoDoJogo.jogador1.symbol != BOLA && estadoDoJogo.jogador1.symbol != CRUZ) 
	{
		printf("\nERRO! TENTE NOVAMENTE INTRODUZINDO \"-p\" COM UM SÍMBOLO VÁLIDO (X ou O).\n");
		exit(0);
	}

	if (Ficheiro == NULL) 
	{
		printf("Por favor declare o nome do ficheiro nos argumentos após \"-f\".\n");
		exit(0);
	}
	
	/*Loop correspondente ao jogo*/
    do
    {
		printf("\nJogada nº %d\n", estadoDoJogo.nJogadas);	/*Apresentação do nº da jogada atual*/
        topoPilhaJogadas = jogadasPossiveis(estadoDoJogo.tabuleiro, estadoDoJogo.jogador1, estadoDoJogo.jogador2, &estadoDoJogo.playable1);	/*Verif. jogadas poss. para 1º jogador*/
        /*Apresentação do tabuleiro e informações adicionais no ecrã*/
		tabPrint(estadoDoJogo.tabuleiro);
        displayPlayerInfo(estadoDoJogo.jogador1);
		score(estadoDoJogo.jogador1, estadoDoJogo.jogador2);
		/*Registo no ficheiro*/
		fprintf(Ficheiro, "\n    Jogada nº %d\n", estadoDoJogo.nJogadas);
		Ledger(estadoDoJogo, estadoDoJogo.jogador1, Ficheiro);
		
        if (estadoDoJogo.playable1) /*Verificação da possibilidade de jogar*/
        {
			undone = FALSE;
            casaSelecionada = playerInput(estadoDoJogo.tabuleiro, apPilhaEstados, estadoDoJogo.undoActive); /*Jogador seleciona casa*/
			
			if (casaSelecionada.cord1 == UNDO && casaSelecionada.cord2 == UNDO) 	/*Caso seja escolhida opção undo...*/
			{				
				apPilhaEstados = undo(apPilhaEstados, &estadoDoJogo);	/*Executar undo*/
				undone = TRUE;														/*Indicar que undo foi feito*/
				fprintf(Ficheiro, "\n        |\n        |  UNDO!\n        V\n");	/*Representar isso no ficheiro*/
			}
			else 	/*Caso contrário, jogar normalmente...*/
			{
			apPilhaEstados = stateStorer(apPilhaEstados, estadoDoJogo);		/*Guardar o estado antes de aplicar jogada*/
			estadoDoJogo.tabuleiro[casaSelecionada.cord1][casaSelecionada.cord2] = estadoDoJogo.jogador1.symbol;	/*Colocar peça do jogador na casa selecionada*/
        	estadoDoJogo.jogador1.nPecas++;		/*Adicionar uma peça ao nº de peças do jogador*/
			PieceSwitcher(estadoDoJogo.tabuleiro, &estadoDoJogo.jogador1, &estadoDoJogo.jogador2, casaSelecionada, topoPilhaJogadas);	/*Virar peças necessárias*/
			fprintf(Ficheiro, "\n        |\n        |  (%d, %d)\n        V\n", casaSelecionada.cord1, casaSelecionada.cord2);	/*Representar jogada no ficheiro*/
			}
        }
        else printf("\nNÃO HÁ JOGADA POSSÍVEL!\n");

        if (undone == FALSE)	/*O IA só joga se ñ tiver sido ativado undo. Isto pois caso o jogador faça undo, este deve jogar novamente.*/
		{
			TabCleaner(estadoDoJogo.tabuleiro);		/*Retirar jogadas possíveis anteriores do tabuleiro*/
        	topoPilhaJogadas = jogadasPossiveis(estadoDoJogo.tabuleiro, estadoDoJogo.jogador2, estadoDoJogo.jogador1, &estadoDoJogo.playable2);	/*Verif. jogadas poss. para jogador2*/
        	tabPrint(estadoDoJogo.tabuleiro);
        	displayPlayerInfo(estadoDoJogo.jogador2);
			score(estadoDoJogo.jogador1, estadoDoJogo.jogador2);
			Ledger(estadoDoJogo, estadoDoJogo.jogador2, Ficheiro);
        	if (estadoDoJogo.playable2)
        	{
            	casaSelecionada = AI_algorithm(topoPilhaJogadas, estadoDoJogo.tabuleiro, &estadoDoJogo.jogador2);	/*Desta vez será usado o algoritmo do IA para jogar e não o input do jogador*/
				PieceSwitcher(estadoDoJogo.tabuleiro, &estadoDoJogo.jogador2, &estadoDoJogo.jogador1, casaSelecionada, topoPilhaJogadas);
				fprintf(Ficheiro, "\n        |\n        |  (%d, %d)\n        V\n", casaSelecionada.cord1, casaSelecionada.cord2);
        	}
			else
			{
				printf("\nNÃO HÁ JOGADA POSSÍVEL!\n");
			}
			estadoDoJogo.nJogadas++;	/*Atualizar contador de jogadas*/
		}
		
        TabCleaner(estadoDoJogo.tabuleiro);	/*Limpar jogadas possivéis do tabuleiro*/
        
    } while (GameIsOver(estadoDoJogo) == FALSE);	/*Verifica no fim de cada "jogada" se o jogo acabou ou ñ. Se retornar falso, o jogo pode continuar.*/

	score(estadoDoJogo.jogador1, estadoDoJogo.jogador2);	/*O jogo acabou e deste modo, devem ser apresentados os resultados finais*/
	winner(estadoDoJogo.jogador1, estadoDoJogo.jogador2);	/*tal como o vencedor.*/

	endingFicheiro(estadoDoJogo.jogador1, estadoDoJogo.jogador2, Ficheiro);		/*Regista o resultado do jogo no ficheiro*/
	
	fclose(Ficheiro);		/*O jogo está concluído logo o ficheiro pode ser fechado*/
	
	exit(0);
}