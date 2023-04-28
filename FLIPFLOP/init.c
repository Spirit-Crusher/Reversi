/*Ficheiro que contém as funções responsáveis por estabelecer as condições iniciais
do jogo tendo em conta os parâmetros estabelecidos pelo jogador através do terminal.
Autores: RODRIGO CALDEIRA 106963
		 HENRIQUE NOGUEIRA 107561
*/

#include "types.h"
#include "flipflop.h"

/*------------------------------------------------------------------------------
Nome: tabInit
Argumentos: BOARD
Valor de Retorno: void
Acção da função: Inicializa a matriz do tabuleiro atribuindo os valores
corretos a cada casa.
------------------------------------------------------------------------------*/
void tabInit (BOARD tabuleiroInicial) {

    int l = 0, c = 0;
    tabuleiroInicial[0][0] = ' ';               /*Espaço que separa a numeração das linhas e das colunas no canto sup esquerdo.*/

    for (l = 1, c = 1; l < BOARDDIM || c < BOARDDIM; l++, c++)
    {
        tabuleiroInicial[0][c] = c+'0';     /*Coloca a numeração das linhas e colunas nas casas correspondentes*/
        tabuleiroInicial[l][0] = l+'0';     /*através da conversão do índice do loop num char de modo a poder ser colocada na matriz.*/
    }

    for (l = 1; l < BOARDDIM; l++)
    {
        for (c = 1; c < BOARDDIM; c++)
        {
            tabuleiroInicial[l][c] = VAZIO;   /*Coloca o correspondente a "vazio" em todas as outras casas*/
        }                                     /*(o tabuleiro inicialmente está vazio tirando algumas peças na região central que serão inseridas no passo seguinte).*/
    }

    tabuleiroInicial[4][4] = BOLA;
    tabuleiroInicial[4][5] = CRUZ;          /*Colocação das peças inicias de cada jogador*/
    tabuleiroInicial[5][5] = BOLA;          /*nas 4 posições centrais do tabuleiro (como referido anteriormente).*/
    tabuleiroInicial[5][4] = CRUZ;
    
    return;
}


/*------------------------------------------------------------------------------
Nome: playerInit
Argumentos: PLAYER* jogador1, PLAYER* jogador2
Valor de Retorno: void
Acção da função: Inicializa os dois jogadores definindo parâmetros associados
a cada um deles.
------------------------------------------------------------------------------*/
void playerInit (PLAYER* jogador1, PLAYER* jogador2, char* symbolArg) {

	jogador1->nJogador = 1;         /*Associa os números de jogador a cada um dos jogadores*/
    jogador2->nJogador = 2;
	jogador1->playerType = HUMANO;  /*Estabelece o tipo de jogador de cada um*/
	jogador2->playerType = AI;
    jogador1->nPecas = 2;           /*Define o nº de peças dos jogadores (2 para cada)*/
    jogador2->nPecas = 2;
    jogador1->symbol = *symbolArg;  /*Define o símbolo associado ao jogador humano dependendo do que foi escolhido pelo mesmo no terminal*/

    /*Lógica responsável por atribuir o símbolo que resta ao jogador IA*/
    if (jogador1->symbol == CRUZ) 
    {
        jogador2->symbol = BOLA;
    }
    else if (jogador1->symbol == BOLA)
    {
        jogador2->symbol = CRUZ;
    }
    else 
    {
        fprintf(stderr, "ERRO: SÍMBOLO INTRODUZIDO Ñ É VÁLIDO.\n");
        exit(0);
	}
    return;
}

/*------------------------------------------------------------------------------
Nome: argumentReader
Argumentos: char* argv[], int argc, GAMESTATE* estadoDoJogo, FILE* Ficheiro
Valor de Retorno: FILE*
Acção da função: Responsável por verificar todos os argumentos enviados pelo
terminal e passar cada um para as devidas funções.
------------------------------------------------------------------------------*/
FILE* argumentReader (char* argv[], int argc, GAMESTATE* estadoDoJogo, FILE* Ficheiro) {

	int argument;

	for(argument = 0; argument < argc; argument++)      /*Para cada argumento de arv verifica as diversas opções disponíveis e mostra informação correspondente no ecrã.*/
	{
		if (!strcmp(argv[argument], "-p"))              /*Lê opção correspondente a símbolo do jogador*/
		{
            printf("-> Símbolo escolhido: %s\n", argv[argument+1]);
			playerInit(&estadoDoJogo->jogador1, &estadoDoJogo->jogador2, argv[argument+1]);
		}
		else if (!strcmp(argv[argument], "-u"))        /*Lê opção correspondente a ativação da opção "undo"*/
		{
            printf("-> Undo activo\n");
			estadoDoJogo->undoActive = TRUE;
		}
		else if (!strcmp(argv[argument], "-f"))        /*Lê opção correspondente a resgito do jogo no ficheiro fornecido*/
		{
            printf("-> Ficheiro de escrita: %s\n", argv[argument+1]);
			Ficheiro = fopen(argv[argument+1], "w");
			if (Ficheiro == NULL) 
			{
				printf("Erro na abertura/criação do ficheiro.\n");
				exit(0);
			}
		}
	}

	return Ficheiro;
}