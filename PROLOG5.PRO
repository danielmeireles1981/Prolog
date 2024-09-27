/*Modulo*/
predicates
	modulo(integer,integer)
	
clauses
	modulo(X,Y):- X>=0, Y=X.
	modulo(X,Y):- X<0,  Y=-X.
	