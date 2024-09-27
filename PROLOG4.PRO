predicates
	nota(symbol,integer)
	idade(symbol,integer)
	jovem(symbol)
	adulto(symbol)
	nao_velho(symbol)
	velho(symbol)
clauses
	nota(miriam,1).
	nota(carla,7).
	nota(lili,3).
	nota(maria,10).
	idade(miriam,45).
	idade(carla,18).
	idade(lili,13).
	idade(maria,22).
	jovem(X):-idade(X,Y), Y<25.
	adulto(X):-idade(X,Y), Y>25, Y<60.	
	nao_velho(X):-jovem(X);adulto(X).
	velho(X):-idade(X,Y), Y>60.
	