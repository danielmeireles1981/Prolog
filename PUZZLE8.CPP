//------- URCAMP - Universidade da Regiao da Campanha
//------- Centro de Ciencias da Economia e Informatica
//------- Curso de Informatica

//------------------------- Inteligencia Artificial -------------------------
//------------------------ Prof.  Alexsander da Rosa ------------------------

//------- Resolvedor de problemas
//------- (por busca em espa‡o de estados)
//------- Busca heuristica

/* Puzzle (quebra-cabecas) de 8
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//------- estrutura geral do nodo
struct nodo
    {
    char puzzle[10];
    int score;
    struct nodo *pai, *irmao, *filho; // parte "geral"
    };
struct nodo *raiz; //raiz da arvore de busca

//------- definicao do estado final
char *EstadoFinal = "1238_4765";

//---------------------------------------------------------------------------
int heuristica ( char *puzz )
{
int i, j, valor = 0, dist, dh, dv;

for ( i = 0; i < 9; i++ )
    {
    if ( EstadoFinal[i] != puzz[i] )
       {
       for ( j = 0; j < 9; j++ )
	   if ( EstadoFinal[i] == puzz[j] ) break;
       if ( j > 8 )
	  {
	  printf("Erro XXX!\n");
	  exit (1);
	  }
       dist = (j<i) ? (i-j) : (j-i);
       dh = dist%3;
       dv = dist/3;
       valor += (dh+dv);
       }
    }
printf ( "%2d ", valor );
return valor;
}

//---------------------------------------------------------------------------
void Expande_Arvore ( struct nodo *atual )
{
char modificado[10], o_melhor[10];
int i, criou, ok, ndx, melhor, h, movim,
  repete[4] = { 0, 0, 0, 0 }, tentativas;
struct nodo *novo, *anterior = NULL, *volta;
int sem_filhos = 1;

//------- mostra todos os estados criados
printf ( "\n" );
printf ( "Ú%c%c%c¿\n",atual->puzzle[0],atual->puzzle[1],atual->puzzle[2]);
printf ( "³%c%c%c³\n",atual->puzzle[3],atual->puzzle[4],atual->puzzle[5]);
printf ( "À%c%c%cÙ ", atual->puzzle[6],atual->puzzle[7],atual->puzzle[8]);

//------- verifica se o estado final foi atingido
if ( strcmp(atual->puzzle,EstadoFinal) == 0 )
    {
    printf ( "OK\n" ); //----- indicador de nodo terminal (solucao)
    //------- percorre toda a arvore, voltando ateh o estado inicial
    printf ( "\n" );
    exit (0);
    }

TentaDeNovo:
//------ "for" que percorre todos os estados possiveis
//------ Neste caso, do puzzle, sao:
//     0: move para esquerda
//     1: move para direita
//     2: move para cima
//     3: move para baixo
tentativas = 0;
melhor = 9999;
criou = 0;
strcpy ( modificado, atual->puzzle );
ndx = 0;
while ( ndx < 9 )
   {
   if ( modificado[ndx] == '_' ) break;
   ndx++;
   }
for ( i = 0; i < 4; i++ ) //------- nesse caso, sao 4
    {
    strcpy ( modificado, atual->puzzle );
    //---- "12345678_"  |012|
    //      012345678   |345|
    //                  |678|
    if ( repete[i] )
	{
	tentativas++;
	continue;
	}
    switch ( i )
	{
	case 0:                      //---- move para esquerda
	    if ( ndx%3 != 2 ) //---- ou seja, todos menos 2, 5 e 8
		{
		modificado[ndx] = modificado[ndx+1];
		modificado[ndx+1] = '_';
		}
	    else break;
	    printf ( " <-:" );
	    h = heuristica ( modificado );
	    if ( h < melhor )
		{
		movim = i;
		melhor = h;
		strcpy ( o_melhor, modificado );
		criou = 1;
		}
	    break;
	case 1:                      //---- move para direita
	    if ( ndx%3 != 0 ) //---- ou seja, todos menos 0, 3 e 6
		{
		modificado[ndx] = modificado[ndx-1];
		modificado[ndx-1] = '_';
		}
	    else break;
	    printf ( " ->:" );
	    h = heuristica ( modificado );
	    if ( h < melhor )
		{
		movim = i;
		melhor = h;
		strcpy ( o_melhor, modificado );
		criou = 1;
		}
	    break;
	case 2:                      //---- move para cima
	    if ( ndx < 6 ) //---- ou seja, todos menos 6, 7 e 8
		{
		modificado[ndx] = modificado[ndx+3];
		modificado[ndx+3] = '_';
		}
	    else break;
	    printf ( "  %c:", 24 );
	    h = heuristica ( modificado );
	    if ( h < melhor )
		{
		movim = i;
		melhor = h;
		strcpy ( o_melhor, modificado );
		criou = 1;
		}
	    break;
	case 3:                      //---- move para baixo
	    if ( ndx > 2 ) //---- ou seja, todos menos 0, 1 e 2
		{
		modificado[ndx] = modificado[ndx-3];
		modificado[ndx-3] = '_';
		}
	    else break;
	    printf ( "  %c:", 25 );
	    h = heuristica ( modificado );
	    if ( h < melhor )
		{
		movim = i;
		melhor = h;
		strcpy ( o_melhor, modificado );
		criou = 1;
		}
	    break;
	}
    }

if ( tentativas == 4 ) //---- tentou todos e nao deu
    return;

if ( criou ) // se foi encontrado um "movimento" valido
    {
    //------- testa se jah existe um antepassado igual
    ok = 1;
    volta = atual; // inicia no atual
    while ( volta != NULL ) // enquanto ainda tem pai
	{
	if ( !strcmp(volta->puzzle,o_melhor) )
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
	strcpy(novo->puzzle,o_melhor);
	novo->score = h;
	novo->pai = atual; //aponta para o pai
	novo->irmao = NULL;
	novo->filho = NULL;

	if ( atual->filho == NULL ) //se eh o primogenito
	    atual->filho = novo; // entao o pai aponta pra ele
	else
	    anterior->irmao = novo; // senao o irmao aponta pra ele

	Expande_Arvore ( novo ); //------- busca em PROFUNDIDADE
	anterior = novo; // move o "anterior"

	sem_filhos = 0;
	}
    else //----- repetiu?
	{
	repete[movim] = 1;
	printf ( "  **** " );
	goto TentaDeNovo;
	}

    }

if ( sem_filhos ) // se for um nodo terminal mas nao for solucao
    printf ( "#\n" ); //----- indicador de nodo terminal (nao solucao)

return;
}

//---------------------------------------------------------------------------
void main ( int argc, char *argv[] )
{
printf ( "PUZZLE8 - Resolvedor de problemas espec¡ficos\n" );
printf ( "Busca em espa‡o de estados - HEURISTICA\n" );
if ( argc != 3 )
    {
    printf ( "Sintaxe: PUZZLE8 <EI> <EF>\n" );
    return;
    }

if ( strlen(argv[1]) != 9 || strlen(argv[2]) != 9 )
    {
    printf ( "Estado invalido\n" );
    return;
    }

EstadoFinal = argv[2];

raiz = new (struct nodo);
strcpy ( raiz->puzzle, argv[1] ); //------- seta o estado inicial ( 0, 0 )
raiz->pai = raiz->irmao = raiz->filho = NULL;
raiz->score = heuristica(raiz->puzzle);
Expande_Arvore ( raiz ); // cria a arvore de busca
}
