ano(honda, 1997).  
ano(uno, 1998). 

comprou(joao, honda).
comprou(joao, uno). 

valor(honda, 20000).
valor(uno, 7000).  

pode_vender(Pessoa, Marca, Ano_Actual):- 
	comprou(Pessoa, Marca), 
	valor(Marca, Preco),  
	ano(Marca, Ano), 
	Preco < 10000, 
	Ano_Actual > Ano - 10. 
