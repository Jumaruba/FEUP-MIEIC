#Questão 1 - Escreva um programa que leia 2 valores X e Y e que armazene num vetor m todos os valores entre eles cujo resto da divisão 
#dele por 5 for igual a 2 ou igual a 3. void div(long int x, long int y, long int *m).

#original from: https://www.urionlinejudge.com.br/judge/pt/problems/view/1133

#x4 quantidade de números a serem analisados 

.global div
.type div, "function" 
.text 

div: 	
        stp x29,x30,[sp,#-16]!
        sub x4, x1, x0
        sub x4,x4,1
        mov x5,#5

ciclo:	cbz x4, end
        add x0,x0,1

        sdiv x3,x0,x5	//x3 = quociente do número na divisão por 5
        mul x3,x3,x5	//x3 = quociente*5
        sub x3,x0,x3	//x3 = resto da divisão por 5

        cmp x3, 2
        beq adic

        cmp x3,3
        beq adic

        sub x4,x4,1
        b ciclo


adic:	str x0,[x2],#8
        sub x4,x4,1
        b ciclo
        
end: 	ret

//-------------------------------------------------------------------------------------------------------------------------
#Questão 02- Encontre o menor elemento de um vetor. O vetor *r tem tamanho n (que é multiplo de 4). Faça o exercicio com 
#programação paralela.

#float menor(float *r, int n) => x0,w1

#original from: https://www.urionlinejudge.com.br/judge/pt/problems/view/1180

.global menor 
.type menor, "function" 
.text 

#s1 : menor valor provisorio 
#s2 : menor valor de todo o vetor 
#x3 : posição do menor valor

menor: 
	stp x29,x30,[sp,#-16]!
        lsr w1,w1,#2

        ldr q0,[x0],#16
        sminv s1, v0.4s

        fmov s2, s1
        sub w1,w1,1

ciclo:  cbz w1, end
        ldr q0, [x0],#16
        sminv s1, v0.4s

        fcmp s2,s1
        fcsel s2,s2,s1,lt


cont:   sub w1,w1,1
        b ciclo

end:    fmov s0,s2
        ldp x29,x30,[sp],#16
        ret

//-------------------------------------------------------------------------------------------------------------------------
#Questão 03 - Dada uma frase "Eutocomfome", por exemplo, faça esta frase ser uma frase dançante: "EuToCoMfOmEi. É 
#fornecido o vector de chars com a frase e o tamanho da string. Considere que a string tem tamanho multiplo de 2
e contém apenas chars.


#void danca(char *p, long int n) => x0, x1

.global danca
.type danca,"function"
.text 

#w2: contém o que está na frase 
#x3: checa se x1 é par
#w4: w2+32

danca: 
	stp x29,x30,[sp,#-16]!

ciclo: 	cbz x1, end
	ldrb w2,[x0] 	//carrega a letra
	bl up		//transforma em maiuscula se for preciso
	strb w2,[x0],#1
	ldrb w2,[x0]
	sub x1,x1,1
	b ciclo


up:	stp x29,x30,[sp,#-16]! 	//funcao transforma em letra maiuscula
	and x3,x1,1
	cbnz x3, fim	//verifica se a posição é par
	
	sub w4,w2,32
	cmp w2, 'a'
	csel w2,w4,w2,ge
fim: 	ldp x29,x30,[sp],#16
	ret

end: 	ldp x29,x30,[sp],#16
	ret
	

	
	
	
	
