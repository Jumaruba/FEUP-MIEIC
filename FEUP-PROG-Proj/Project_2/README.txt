---------------------------------------------------------------------------------------------------------------------------
						~REPORT/ENGLISH~
---------------------------------------------------------------------------------------------------------------------------
  
README-PROJECT 2-Allan Borges (201800149) & Juliane Marubayashi (201800175)

Warning: Do not enter names with accented characters(Due to default english development)
All features were successfully implemented:

.Read and store agency,client and packages information.
.Edit,remove and create new client and packages. (Besides there's a function called "remove" for package, it don't actually removes the pack, it just changes its availability) 
.Visualize a client information.
.Visualize all clients.
.Visualize all packages,between two dates,to a specific location,between two dates and a specific location.
.Visualize all sold packages to a client and to all clients.
.Purchasing a pack as a client.
Calculate and visualize the number and total profit of sold packages.
.Most visited locations in order.
.Generate which package a client should buy that include a most visited place that has not been visited yet.
The code is spread throughout multiple files.

.About the most visited places: the number of times that a place was visited is !the sum of the reserved seats for each package that contais this place!. 
	However, the number of times that a package has been sold is not the sum of the reserved seats! We've considered that one person buys a package for all the family, which means that if just one person buys a package,  the number of times that this package has been sold is one (no matter how large his family is). 
	
All lines of code necessary to understand the code have been commented in english.

*A client can buy the same package more than once*
*When attempting to visualize the N most visited places,the client chooses the number N*

--IMPROVEMENTS 

-The program checks if the day given by the user, for dates, is consistent with the month 
and year, analysing if it's a leap year how many days there're at this year and specific month.

-The program does a safe file saving: first saves the information in provisory files. 
When the process is done, the original files are deleted and the provisory files are 
renamed to the original files. 

-the program recognizes if the operational system is windows or linux and implements a function 
cleanScreen to clean the screen whichever the operational system is. 

-------------------------------------------------------------------------------------------------------------------------
						~REPORT/PORTUGUESE~
-------------------------------------------------------------------------------------------------------------------------
  
README-PROJECT 2-Allan Borges (201800149) & Juliane Marubayashi (201800175)

Alerta: Não insira letras acentuadas, visto que este programa é baseada na escrita inglesa. 
Todas as competencias foram implementadas com sucesso:

.Ler e guardar informações sobre clientes e pacotes.
.Editar, "remover" clientes e pacotes. (Apesar dos pacotes terem uma função chamada "remove", na verdade ela não remove o pacote, apenas muda a sua disponibilidade). 
.Visualiza a informação de um cliente.
.Visualiza todos os clientes.
.Visualiza um pacote entre duas datas, para um lugar especifico e entre duas datas e um lugar especifico. 
.Visualiza todos os pacotes vendidos para todos os clientes e para um cliente específico. 
.Compra de um pacote para um cliente. 
.Calcula e visualiza o numero total e o lucro total de pacotes vendidos. 
.Os locais mais visitados em ordem decrescente. 
.Gera que pacote um cliente deveria comprar que inclui o lugar mais visitado que o cliente ainda não visitou. 
.O código esta separado em multiplos arquivos. 

.Sobre os lugares mais visitados: o número de vezes que um lugar foi visitado é a soma dos lugares reservados para cada pacote que contem o lugar. 
	Por outro lado, o número de vezes que um pacote foi vendido não é a soma dos lugares reservados. Nós consideramos que uma pessoa compra o pacote para a família toda, o que significa que se apenas uma pessoa compra o pacote, o número de vezes que esse pacote foi vendido é apenas um (não importa o quão grande seja a família).

	
All lines of code necessary to understand the code have been commented in english.
Todas as linhas to código foram comentadas em inglês. 

*Um cliente pode comprar um pacote mais de uma vez*
*Quando se tenta visualizar os N lugares mais visitados, é necessário que o cliente insira N*


--MELHORIAS 

-O programa chega se o número de dias dados pelo usuário, para datas, é consistente com o mês e ano, analisando é um ano bissexto e quantos dias tem nem no ano e mês específico

-O programa faz um salvamento seguro dos arquivos: primeiro salva informação em arquivos provisórios. Quando o processo é terminado, os arquivos originais são deletados e os arquivos provisórios são renomeados para os nomes dos arquivos originais. 

-Este programa reconhece se o sistema operacional é windows ou linux e implementa um função chamada cleanScreen que limpa a terminal qualquer que seja o sistema. 


