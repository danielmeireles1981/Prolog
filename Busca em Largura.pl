% Busca em largura

% Digitar 'resolva' para executar.

/* d1, d2, d3, ..., são nomes dados a definições
	para futuras referências
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
	é respondida conforme mostrado:

	?- ap([b,c,d],[f,g],L).
	L = [b, c, d, f, g]
	Yes
*/

ap([],X,X) :- !.
ap([X|Y],Z,[X|W]) :- ap(Y,Z,W).
% 27
/* d2: ===============================================================
	membro verifica se um elemento está em uma lista. Exemplo:

	?- membro(v,[b,c,v,m]).
	Yes
*/

membro(X,[X|_]) :- !.
membro(X,[_|Y]) :- membro(X,Y).

%% Se o programa não funcionar como esperado, experimente
%% substituir "bagof" por "findall" na definição abaixo.

ache_todos(X,Y,Z) :- bagof(X,Y,Z), !.
ache_todos(_,_,[]).
% 43
/* d3: =================================================================
	O programa auxiliar seguinte serve para imprimir uma trajetória.
	A trajetória é representada por uma lista de estruturas do
	tipo r(R, Nodo), onde R é o ramo que liga Nodo ao pai dele.
	Seja, por exemplo, a árvore que segue:

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

	A trajetória que começa em 'b', passa por 'c' e termina em 'g'
	é representada por [r([4],g), r([1],c), r(raiz,b)].

	A impressão começa com o caso em que a trajetória só tem raiz:
*/

imprima([r(raiz,Raiz)]) :- !,
	write('Estado Inicial: '),
	write(Raiz), write('.').

/* Quando há mais de um par ramo-nodo na trajetória, imprime-se
	aqueles que seguem ao primeiro e, depois, imprime-se o primeiro.
	Deve-se imprimir o primeiro por último porque a trajetória é
	construída de trás para diante.
*/

imprima([r(Ramo,Nodo)|R]) :- imprima(R), nl,
	write(Ramo), write(' e, portanto, temos: '), nl,
	write(Nodo), write('.').
% 82
/* d4: =====================================================================
	'resolva' vai chamar o programa que faz a busca em largura.
	Inicialmente, a Fila contém a mini-trajetória [[r(raiz,E)]],
	a qual começa e acaba na raiz.
*/

resolva :- estado_inicial(E),
	busca([[r(raiz,E)]],Solucao),
	imprima(Solucao), nl.
% 92
/* d5: =====================================================================
	Realiza a busca em largura.
	Solução é uma trajetória que leva da raiz à meta.
	T é o primeiro elemento de uma lista de trajetórias candidatas
	a ser Solução. Se o predicado 'atinge_a_meta' verificar que
	T está levando à meta, o problema foi resolvido e basta fazer
	Solução ser igual a T.
*/

busca([T|_],Solucao) :- T atinge_a_meta, !, Solucao = T.
/*    \___/
        ^
	|
	|_____ Lista de candidatas a ser solução.

	Tem-se agora o caso em que T ainda não chegou até a solução.
	Note que T é uma lista de nódulos. Deve-se, neste caso, estender T de
	modo a incluir um dos filhos de seu primeiro nódulo. A lista das
	extensões possíveis é colocada na variável Extensões.
*/

busca([T|Fila],Solucao) :-
	ache_todos(ExtensaoAteUmFilho,
		estende_ate_filho(T,ExtensaoAteUmFilho), Extensoes),
	/* Conforme vimos, Extensões são colocadas no fim da Fila
		pelo predicado "ap(...,...,...)". Obtém-se, desta forma, a
		FilaEstendida. */
	ap(Fila, Extensoes, FilaEstendida),
	busca(FilaEstendida,Solucao).
	/* E a busca continua pela FilaEstendida. */
% 123
/* d6: ======================================================================
	Agora Trajetória é estendida de r(Ramo,Nodo) até um Filho
	do nódulo N. O Filho de N é gerado por uma operação Op.
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
	A trajetória que fornece a solução atinge a meta.
*/

[r(Ramo,M)|_] atinge_a_meta :- M eh_a_meta.
% 145

