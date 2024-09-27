//------- URCAMP - Universidade da Regiao da Campanha
//------- Centro de Ciencias da Economia e Informatica
//------- Curso de Informatica

//------------------------- Inteligencia Artificial -------------------------
//------------------------ Prof.  Alexsander da Rosa ------------------------

//------- Resolvedor de problemas
//------- (por busca em espa‡o de estados)
//------- Busca cega (sem heuristica) em profundidade

/* Problema dos Baldes:

    "Dispondo de uma fonte de  gua e de dois recipientes com capacidades
    para 4 e 3 litros, respectivamente, obtenha exatamente 2 litros no
    recipiente com capacidade para 3 litros" [BITT96]

    ou

    "Vocˆ tem duas jarras, uma de 4 litros e outra de 3 litros. Nenhuma
    delas tem qualquer marca‡„o de medidas. H  uma bomba que pode ser
    usada para encher as jarras com  gua. Como ‚ que vocˆ consegue colocar
    exatamente 2 litros de  gua na jarra de 4 litros?" [RICH94]
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

//------- estrutura geral do nodo
struct nodo
    {
    int balde4, balde3; //parte "especifica": problema dos baldes
    struct nodo *pai, *irmao, *filho; // parte "geral"
    };
struct nodo *raiz; //raiz da arvore de busca
unsigned int solucoes = 0;
int debug = 0;

//------- definicao do estado final
int EstadoFinal4 = 2,
    EstadoFinal3 = 0;

//---------------------------------------------------------------------------
void Expande_Arvore ( struct nodo *atual )
{
int b4, b3, transf;
int i, criou, ok;
struct nodo *novo, *anterior = NULL, *volta;
int sem_filhos = 1;

if ( debug ) //------- mostra todos os estados criados
    printf ( "[%d %d] ", atual->balde4, atual->balde3 );

//------- verifica se o estado final foi atingido
if ( atual->balde4 == EstadoFinal4 && atual->balde3 == EstadoFinal3 )
    {
    if ( debug )
	printf ( "$\n" ); //----- indicador de nodo terminal (solucao)
    //------- percorre toda a arvore, voltando ateh o estado inicial
    volta = atual; // inicia no atual
    while ( volta != NULL ) // enquanto tem pai
	{
	//------- mostra estado por estado
	printf ( "(%d,%d)%c", volta->balde4, volta->balde3, 0x1b );
	volta = volta->pai;
	}
    printf ( "\n" );
    solucoes++;
    }

//------ "for" que percorre todos os estados possiveis
//------ Neste caso, dos baldes, sao:
//     0: enche o balde de 4 litros
//     1: enche o balde de 3 litros
//     2: transfere agua do balde de 4 litros para o balde de 3 litros
//     3: transfere agua do balde de 3 litros para o balde de 4 litros
//     4: esvazia o balde de 4 litros
//     5: esvazia o balde de 3 litros
for ( i = 0; i < 6; i++ ) //------- nesse caso, sao 6
    {
    criou = 0;
    switch ( i )
	{
	case 0:                      //---- enche o b4
	    if ( atual->balde4 < 4 ) // se o b4 nao estah cheio
		{
		b4 = 4;
		b3 = atual->balde3;
		criou = 1;
		}
	    break;
	case 1:                      //---- enche o b3
	    if ( atual->balde3 < 3 ) // se o b3 nao estah cheio
		{
		b4 = atual->balde4;
		b3 = 3;
		criou = 1;
		}
	    break;
	case 2:                       //---- passa do b4 pro b3
	    if ( atual->balde3 < 3 && // se o b3 nao estah cheio
		atual->balde4 > 0 ) // e o b4 nao estah vazio
		{
		transf = 3 - ( atual->balde3 ); // cabe 3 - o que tem no b3
		if ( transf > atual->balde4 ) // se couber + do que tem no b4
		    transf = atual->balde4; // entao tranfere todo o b4
		b4 = atual->balde4 - transf;
		b3 = atual->balde3 + transf;
		criou = 1;
		}
	    break;
	case 3:                       //---- passa do b3 pro b4
	    if ( atual->balde4 < 4 && // se o b4 nao estah cheio
		atual->balde3 > 0 ) // e o b3 nao estah vazio
		{
		transf = 4 - ( atual->balde4 ); // cabe 4 - o que tem no b4
		if ( transf > atual->balde3 ) // se couber + do que tem no b3
		    transf = atual->balde3; // entao tranfere todo o b3
		b4 = atual->balde4 + transf;
		b3 = atual->balde3 - transf;
		criou = 1;
		}
	    break;
	case 4:                      //---- esvazia o b4
	    if ( atual->balde4 > 0 ) // se o b4 nao estah vazio
		{
		b4 = 0;
		b3 = atual->balde3;
		criou = 1;
		}
	    break;
	case 5:                      //---- esvazia o b3
	    if ( atual->balde3 > 0 ) // se o b4 nao estah vazio
		{
		b4 = atual->balde4;
		b3 = 0;
		criou = 1;
		}
	    break;
	}

    if ( criou ) // se foi encontrado um "movimento" valido
	{
	//------- testa se jah existe um antepassado igual
	ok = 1;
	volta = atual; // inicia no atual
	while ( volta != NULL ) // enquanto ainda tem pai
	    {
	    if ( volta->balde4 == b4 && volta->balde3 == b3 )
		{ ok = 0; break; } // se jah existe, ok=0
	    volta = volta->pai; // volta para o pai
	    }

	if ( ok ) //------- se tudo Ok (nao existe ainda)
	    {
	    //------- cria o novo nodo
	    novo = new (struct nodo);
	    if ( novo == NULL )
		{
		printf ( "Sem mem¢ria dispon¡vel!\n" );
		exit ( EXIT_FAILURE ); //----- aborta em caso de erro fatal
		}
	    novo->balde4 = b4;
	    novo->balde3 = b3;
	    novo->pai = atual; //aponta para o pai
	    novo->irmao = NULL;
	    novo->filho = NULL;

	    if ( atual->filho == NULL ) //se eh o primogenito
		atual->filho = novo; // entao o pai aponta pra ele
	    else
		anterior->irmao = novo; // senao o irmao aponta pra ele


	    Expande_Arvore ( novo ); //------- busca em PROFUNDIDADE

	    anterior = novo; // move o "anterior"

	    if ( debug ) //---- somente para debug
		sem_filhos = 0;
	    }
	}
    }

if ( debug && sem_filhos ) // se for um nodo terminal mas nao for solucao
    printf ( "#\n" ); //----- indicador de nodo terminal (nao solucao)

return;
}

//---------------------------------------------------------------------------
void main ( int argc, char *argv[] )
{
printf ( "BALDES - Resolvedor de problemas espec¡ficos\n" );
printf ( "Busca em espa‡o de estados - Busca Cega em profundidade\n" );
if ( argc != 4 )
    {
    printf ( "Sintaxe: BALDES <tipo> <b4> <b3>\n" );
    printf ( "  onde <tipo> pode ser 'n' (normal) ou 'd' (debug)\n" );
    printf ( "  e <b4> <b3> indicam o estado final.\n" );
    return;
    }

if ( ( argv[1][0] | 0x20 ) == 'd' )
    {
    debug = 1;
    printf ( "Modo DEBUG ativado.\n" );
    }

EstadoFinal4 = atoi ( argv[2] );
EstadoFinal3 = atoi ( argv[3] );

raiz = new (struct nodo);
raiz->balde4 = 0; //------- seta o estado inicial ( 0, 0 )
raiz->balde3 = 0;
raiz->pai = raiz->irmao = raiz->filho = NULL;

Expande_Arvore ( raiz ); // cria a arvore de busca

printf ( "Total: %u solu‡%s.\n", solucoes, solucoes == 1 ? "„o" : "”es" );
getche();
}

