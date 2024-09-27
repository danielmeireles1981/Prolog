predicates
	fatorial(integer,integer)
	
clauses
	fatorial(X,1):-X=0.
	fatorial(X,Y):-X>0,
	               W=X-1,
		       fatorial(W,Z),
		       Y=X*Z.
			