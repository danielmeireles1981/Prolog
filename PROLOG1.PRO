predicates
	gosta(symbol,symbol)
	amado(symbol)
	ama(symbol)
	feliz(symbol)
	
clauses
	gosta(rai,lili).
	gosta(rai,hortencia).
	gosta(lili,jojo).
	gosta(mania,rai).
	gosta(lala,rai).
	gosta(hortencia,rai).
	/* Alguem eh amado se alguem gosta dele */
	amado(Alguem):-gosta(_,Alguem).
	/* Alguem ama se gosta de alguem */
	ama(X):-gosta(X,_).
	/* Alguem eh feliz se gosta de alguem que
	   gosta dele */
	feliz(X):-gosta(X,Y),
		  gosta(Y,X).
