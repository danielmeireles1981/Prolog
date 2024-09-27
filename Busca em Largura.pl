% Busca em largura

% Digitar 'resolva' para executar.

/* d1, d2, d3, ..., s�o nomes dados a defini��es
	para futuras refer�ncias
*/
% 6
:- op(900,fy,not).
:- op(35,xf,eh_a_meta).
:- op(35,xf,atinge_a_meta).
:- op(35,xfx,transforma).
:- op(35,xfx,nao_produz_circulos_em).
:- op(30,xfx,a).
:- op(30,xfx,em).
% 13
% Programas auxiliares
% 15
/* d1: ===============================================================
	ap concatena duas listas. Isto significa que a pergunta abaixo
	� respondida conforme mostrado:

	?- ap([b,c,d],[f,g],L).
	L = [b, c, d, f, g]
	Yes
*/

ap([],X,X) :- !.
ap([X|Y],Z,[X|W]) :- ap(Y,Z,W).
% 27
/* d2: ===============================================================
	membro verifica se um elemento est� em uma lista. Exemplo:

	?- membro(v,[b,c,v,m]).
	Yes
*/

membro(X,[X|_]) :- !.
membro(X,[_|Y]) :- membro(X,Y).

%% Se o programa n�o funcionar como esperado, experimente
%% substituir "bagof" por "findall" na defini��o abaixo.

ache_todos(X,Y,Z) :- bagof(X,Y,Z), !.
ache_todos(_,_,[]).
% 43
/* d3: =================================================================
	O programa auxiliar seguinte serve para imprimir uma trajet�ria.
	A trajet�ria � representada por uma lista de estruturas do
	tipo r(R, Nodo), onde R � o ramo que liga Nodo ao pai dele.
	Seja, por exemplo, a �rvore que segue:

				b
				/\
			       /  \
			     [1]  [2]
			     /      \
			    /        \
			   c          d
			  /\          /\
			 /  \        /  \
		       [3]  [4]    [5]  [6]
		       /      \    /      \
		      f        g  h        k

	A trajet�ria que come�a em 'b', passa por 'c' e termina em 'g'
	� representada por [r([4],g), r([1],c), r(raiz,b)].

	A impress�o come�a com o caso em que a trajet�ria s� tem raiz:
*/

imprima([r(raiz,Raiz)]) :- !,
	write('Estado Inicial: '),
	write(Raiz), write('.').

/* Quando h� mais de um par ramo-nodo na trajet�ria, imprime-se
	aqueles que seguem ao primeiro e, depois, imprime-se o primeiro.
	Deve-se imprimir o primeiro por �ltimo porque a trajet�ria �
	constru�da de tr�s para diante.
*/

imprima([r(Ramo,Nodo)|R]) :- imprima(R), nl,
	write(Ramo), write(' e, portanto, temos: '), nl,
	write(Nodo), write('.').
% 82
/* d4: =====================================================================
	'resolva' vai chamar o programa que faz a busca em largura.
	Inicialmente, a Fila cont�m a mini-trajet�ria [[r(raiz,E)]],
	a qual come�a e acaba na raiz.
*/

resolva :- estado_inicial(E),
	busca([[r(raiz,E)]],Solucao),
	imprima(Solucao), nl.
% 92
/* d5: =====================================================================
	Realiza a busca em largura.
	Solu��o � uma trajet�ria que leva da raiz � meta.
	T � o primeiro elemento de uma lista de trajet�rias candidatas
	a ser Solu��o. Se o predicado 'atinge_a_meta' verificar que
	T est� levando � meta, o problema foi resolvido e basta fazer
	Solu��o ser igual a T.
*/

busca([T|_],Solucao) :- T atinge_a_meta, !, Solucao = T.
/*    \___/
        ^
	|
	|_____ Lista de candidatas a ser solu��o.

	Tem-se agora o caso em que T ainda n�o chegou at� a solu��o.
	Note que T � uma lista de n�dulos. Deve-se, neste caso, estender T de
	modo a incluir um dos filhos de seu primeiro n�dulo. A lista das
	extens�es poss�veis � colocada na vari�vel Extens�es.
*/

busca([T|Fila],Solucao) :-
	ache_todos(ExtensaoAteUmFilho,
		estende_ate_filho(T,ExtensaoAteUmFilho), Extensoes),
	/* Conforme vimos, Extens�es s�o colocadas no fim da Fila
		pelo predicado "ap(...,...,...)". Obt�m-se, desta forma, a
		FilaEstendida. */
	ap(Fila, Extensoes, FilaEstendida),
	busca(FilaEstendida,Solucao).
	/* E a busca continua pela FilaEstendida. */
% 123
/* d6: ======================================================================
	Agora Trajet�ria � estendida de r(Ramo,Nodo) at� um Filho
	do n�dulo N. O Filho de N � gerado por uma opera��o Op.
*/

estende_ate_filho([r(Ramo,N)|Trajetoria],
		[r(Op,Filho),r(Ramo,N)|Trajetoria]) :-
	operacao(Op) transforma N em Filho,
	Filho nao_produz_circulos_em Trajetoria.
% 133
/* d7: ======================================================================
*/

 Estado nao_produz_circulos_em Trajetoria :- not membro(r(Operacao,Estado),Trajetoria).

% 139
/* d8: ======================================================================
	A trajet�ria que fornece a solu��o atinge a meta.
*/

[r(Ramo,M)|_] atinge_a_meta :- M eh_a_meta.
% 145

