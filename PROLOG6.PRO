trace
predicates
	mae(symbol,symbol)
	antepassado(symbol,symbol)
	
clauses
	mae(julia,maria).
	mae(dalia,julia).
	mae(iris,dalia).
	mae(jorge,iris).
	antepassado(X,Y):-mae(X,Y).
	antepassado(X,Y):-mae(Z,Y), antepassado(X,Z).