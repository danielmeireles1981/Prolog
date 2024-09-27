//------- URCAMP - Universidade da Regiao da Campanha
//------- Centro de Ciencias da Economia e Informatica
//------- Curso de Informatica

//------------------------- Inteligencia Artificial -------------------------
//------------------------ Prof.  Alexsander da Rosa ------------------------

//------- Resolvedor de problemas
//------- (por busca em espa‡o de estados)
//------- Busca cega (sem heuristica) em profundidade

/* Problema das moedas
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------- estrutura geral do nodo
struct nodo
    {
    char posicao[6];
    struct nodo *pai, *irmao, *filho; // parte "geral"
    };
struct nodo *raiz; //raiz da arvore de busca
unsigned int solucoes = 0;
int debug = 0;

//------- definicao do estado final
char *EstadoFinal = "DD_NN";

//---------------------------------------------------------------------------
void Expande_Arvore ( struct nodo *atual )
{
char *pos, modificado[6];
int i, criou, ok;
struct nodo *novo, *anterior = NULL, *volta;
int sem_filhos = 1;

if ( debug ) //------- mostra todos os estados criados
    printf ( "[%s] ", atual->posicao );

//------- verifica se o estado final foi atingido
if ( strcmp(atual->posicao,EstadoFinal) == 0 )
    {
    if ( debug )
	printf ( "$\n" ); //----- indicador de nodo terminal (solucao)
    //------- percorre toda a arvore, voltando ateh o estado inicial
    volta = atual; // inicia no atual
    while ( volta != NULL ) // enquanto tem pai
	{
	//------- mostra estado por estado
	printf ( "(%s)%c", volta->posicao, 0x1b );
	volta = volta->pai;
	}
    printf ( "\n" );
    solucoes++;
    }

//------ "for" que percorre todos os estados possiveis
//------ Neste caso, das moedas, sao:
//     0: move o N
//     1: move o D
for ( i = 0; i < 2; i++ ) //------- nesse caso, sao 2
    {
    criou = 0;
    strcpy ( modificado, atual->posicao );
    switch ( i )
	{
	case 0:                      //---- move o N
	    pos = strstr(modificado,"N_");
	    if ( pos ) {
		*pos++ = '_';
		*pos = 'N';
		criou = 1;
		break; }
	    pos = strstr(modificado,"ND_");
	    if ( pos ) {
		*pos++ = '_';
		pos++;
		*pos = 'N';
		criou = 1;
		break; }
	    break;
	case 1:                      //---- move o D
	    pos = strstr(modificado,"_D");
	    if ( pos ) {
		*pos++ = 'D';
		*pos = '_';
		criou = 1;
		break; }
	    pos = strstr(modificado,"_ND");
	    if ( pos ) {
		*pos++ = 'D';
		pos++;
		*pos = '_';
		criou = 1;
		break; }
	    break;
	}

    if ( criou ) // se foi encontrado um "movimento" valido
	{
	//------- testa se jah existe um antepassado igual
	ok = 1;
	volta = atual; // inicia no atual
	while ( volta != NULL ) // enquanto ainda tem pai
	    {
	    if ( !strcmp(volta->posicao,modificado) )
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
	    strcpy(novo->posicao,modificado);
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
printf ( "MOEDAS - Resolvedor de problemas espec¡ficos\n" );
printf ( "Busca em espa‡o de estados - Busca Cega em profundidade\n" );
if ( argc != 4 )
    {
    printf ( "Sintaxe: MOEDAS <tipo> <EI> <EF>\n" );
    printf ( "  onde <tipo> pode ser 'n' (normal) ou 'd' (debug)\n" );
    return;
    }

if ( ( argv[1][0] | 0x20 ) == 'd' )
    {
    debug = 1;
    printf ( "Modo DEBUG ativado.\n" );
    }

if ( strlen(argv[2]) != 5 || strlen(argv[3]) != 5 )
    {
    printf ( "Estado invalido\n" );
    return;
    }

EstadoFinal = argv[3];

raiz = new (struct nodo);
strcpy ( raiz->posicao, argv[2] ); //------- seta o estado inicial ( 0, 0 )
raiz->pai = raiz->irmao = raiz->filho = NULL;

Expande_Arvore ( raiz ); // cria a arvore de busca

printf ( "Total: %u solu‡%s.\n", solucoes, solucoes == 1 ? "„o" : "”es" );
}
