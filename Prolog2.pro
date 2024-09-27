predicates
  gosta(symbol,symbol)	
  amado(symbol)
  ama(symbol)
  feliz(symbol)
  
clauses
  gosta(rai,lili).
  gosta(rai,hortencia).
  gosta(lili,jojo).
  gosta(maria,rai).
  gosta(lala,rai).
  gosta(hortencia,rai).

  amado(Alguem):-gosta(_,Alguem).
  ama(X):-gosta(X,_).
  feliz(X):-gosta(X,Y),
            gosta(X,X).
  
           