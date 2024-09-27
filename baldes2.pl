\\baldes:-
\\        objectivo(Ef), inicio(Ei),
\\        pprof( Ei, Ef, [Ei], Sol ), 
\\        nl, escreve(Sol).
inicio( b(0,0) ).
objectivo( b(2,0) ).

sucessor( b(X,Y), b(4,Y), 'encher o 1. balde' ):- X<4.
sucessor( b(X,Y), b(X,3), 'encher o 2. balde' ):- Y<3.
sucessor( b(X,Y), b(0,Y), 'esvaziar o 1. balde' ):- X>0.
sucessor( b(X,Y), b(X,0), 'esvaziar o 2. balde' ):- Y>0.
sucessor( b(X,Y), b(4,Y1), 'despejar do 2. para o 1. ate encher o 1.' ):- X+Y>=4, Y>0, Y1 is Y-(4-X).
sucessor( b(X,Y), b(X1,3), 'despejar do 1. para o 2. ate encher o 2.' ):- X+Y>=3, X>0, X1 is X-(3-Y).
sucessor( b(X,Y), b(X1,0), 'despejar do 2. para o 1. ate esvaziar o 1.' ):- X+Y<4, Y>0, X1 is X+Y.
sucessor( b(X,Y), b(0,Y1), 'despejar do 1. para o 2. ate esvaziar o 2.' ):- X+Y<3, X>0, Y1 is X+Y.
 
pprof( E, E, _, [] ):- !.
pprof( E, Ef, EAnts, [(ESeg,Accao)|L] ):-
        sucessor(E, ESeg, Accao),
        not member(ESeg, EAnts),
        pprof( ESeg, Ef, [ESeg|EAnts], L ).
 
escreve( [] ):- !.
escreve( [(E,Accao)|R] ):-
        write(Accao), write(' : '), write(E), nl,
        escreve(R).
