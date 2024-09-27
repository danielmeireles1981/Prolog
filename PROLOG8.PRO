predicates 
	feliz(symbol)
	gosta(symbol,symbol)
	ganhou_na_sena(symbol)
	feliz_ou_nao(symbol)
	
clauses
	gosta(maria,joao).
	gosta(lili,pedro).
	ganhou_na_sena(nois).
	ganhou_na_sena(elas).
	feliz(X):-
		write(" 1 "),
		gosta(X,Y), write(" 2 "),
		gosta(Y,X), write(" 3 ").
		
	feliz(X):-
		write(" 4 "),
		ganhou_na_sena(X).
	feliz_ou_nao(Nome):-
		feliz(Nome),
		write(Nome,"Ç feliz").
	feliz_ou_nao(Nome):-
		write(Nome,"n∆o Ç feliz").
