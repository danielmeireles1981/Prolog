% Prepara-se aqui o problema das fichas para que ele
% seja resolvido pelos vários métodos de busca

operacao(deslisa)	transforma	[i,A,B,C,D] em [A,i,B,C,D].
operacao(salta)		transforma	[i,A,B,C,D] em [B,A,i,C,D].
operacao(deslisa)	transforma	[A,i,B,C,D] em [A,B,i,C,D].
operacao(deslisa)	transforma	[A,i,B,C,D] em [i,A,B,C,D].
operacao(salta)		transforma	[A,i,B,C,D] em [A,C,B,i,D].
operacao(deslisa)	transforma	[A,B,i,C,D] em [A,i,B,C,D].
operacao(deslisa)	transforma	[A,B,i,C,D] em [A,B,C,i,D].
operacao(salta)		transforma	[A,B,i,C,D] em [i,B,A,C,D].
operacao(salta)		transforma	[A,B,i,C,D] em [A,B,D,C,i].
operacao(deslisa)	transforma	[A,B,C,i,D] em [A,B,i,C,D].
operacao(salta)		transforma	[A,B,C,i,D] em [A,i,C,B,D].
operacao(deslisa)	transforma	[A,B,C,i,D] em [A,B,C,D,i].
operacao(deslisa)	transforma	[A,B,C,D,i] em [A,B,C,i,D].
operacao(salta)		transforma	[A,B,C,D,i] em [A,B,i,D,C].

estado_inicial([o,o,i,*,*]).
[o,*,*,o,i] eh_a_meta.
