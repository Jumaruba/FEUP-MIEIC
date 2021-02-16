#FOLHA DE PROCESSAMENTO PARALELO 
#Atenção: atualmente o arm não faz soma horizontal em float, mas podemos adicionar pares (addp)

# Questão 01 - 

#a) void somaV (float *p, float *q, float *r, int n) - x0, x1, x2 & x3. Como é float, usaremos S que contém 4bytes cada. 

.text 
.global somaV
.type somaV, "function" 

somaV:  
        stp x29,x30,[sp, #-16]!
        lsr x3, x3, 2  //estamos fazendo 4 operações em um ciclo 
ciclo:  
        cbz x3, end
        ldr q0, [x0], #16
        ldr q1, [x1], #16
        
        fadd v2.4s, v1.4s, v0.4s  // somando 4 números em paralelo
        
        str q2, [x2], #16 //armazenando o resultado 
        sub x3, x3, #1  //atualizando o contador
        b ciclo
        
end:
        ldp x29,x30,[sp],#16
        ret 

#------------------------------------------------------------------------------------------------------------------------

#b) void altV(float *P, int n, float k) - x0, x1, s0

.text
.global altV
.type altV, "function" 

altV:   
	stp x29,x30,[sp,#-16]!
        lsr x1, x1, 2
ciclo:
        cbz x1, end
        ldr q1, [x0]
        fmul v1.4s, v1.4s, v0.s[0] //v0.s0 é o valor de k, já que os registos S e V são o mesmo
        str q1, [x0], #16
        sub x1, x1, #1
        b ciclo

end:    ldp x29,x30,[sp],#16
        ret
	
#------------------------------------------------------------------------------------------------------------------------
#c) void msubV(float *P, float *Q, float *R, int n, float k) - fazer P − k × Q

.global msubV
.type msubV, "function"
.text

msubV: 
	stp x29,x30,[sp,#-16]!
        lsr x3, x3, 2
ciclo:

	cbz x3,end
	ldr q1,[x0],#16
	ldr q2,[x1],#16

	fmul v3.4s, v2.4s, v0.s[0]  //k*Q
	fsub v3.4s,v1.4s, v3.4s	 //P -k*Q
	
	str q3,[x2],#16	//armazenando o resultado no vetor 
	sub x3,x3,#1	//atualizando o contador 
	b ciclo

end: 	ldp x29,x30,[sp],#16
	ret

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 2 - long int prodintV(int *R, int *S, int n)

.global prodintV
.type prodintV, "function"
.text

prodintV:
	stp x29,x30,[sp,#-16]!
        lsr x2,x2,#2
        mov x4,#0	//contador

ciclo: 	cbz x2, end
	ldr q1,[x0],#16
	ldr q2,[x1],#16

	mul v1.4s,v1.4s,v2.4s
	addv s3,v1.4s

	smov x3, v3.s[0] 

	add x4,x3,x4
	sub x2,x2,#1
	b ciclo

end: 	mov x0,x4
	ldp x29,x30,[sp],#16
	ret
	
#sem usar processamento paralelo 

.global prodintV
.type prodintV, "function"
.text

prodintV: 
	stp x29,x30,[sp,#-16]!
	mov x5, #0	//soma
ciclo: 	
	cbz x2, fim
	ldr w3,[x0],#4
	ldr w4,[x1],#4
	smaddl x5,x4,x3,x5 //produto interno 
	sub x2,x2,#1
	b ciclo
end:
	mov x0,x5
	ldp x29,x30,[sp],#16
	ret 

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#Questão 3- long int conta_ocorr(char *V, long int n, char val) -> x0,x1,x2

#x5: número de ocorrências 
#x6: soma do número de ocorrencias de uma interação 
#v1: vetor duplicado de val


.global conta_ocorr
.type conta_ocorr, "function"
.text

conta_ocorr:
	stp x29,x30,[sp,#-16]!
	lsr x1,x1,#4
	dup v1.16b, w2		//vetor duplicado de val
	mov x5,#0		//contador

ciclo:
	cbz x1,end
	ldr q0,[x0],#16

	cmeq v2.16b, v1.16b, v0.16b //comparações multiplas
	abs v2.16b, v2.16b	//podemos fazer assim ou podemos fazer abs no valor de x6. 

	addv b3,v2.16b	//fazer a soma dos 1's
	smov x6,v3.b[0]
	
	add x5,x5,x6
	sub x1,x1,#1
	b ciclo

end:
	mov x0,x5
	ldp x29,x30,[sp],#16
	ret


	
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#Questão 4- void incsatV(int *Z, int n, int x) - x0,x1,x2

.global incsatV
.type incsatV, "function"
.text

incsatV:

	stp x29,x30,[sp,#-16]!
	lsr x1,x1,#2
	dup v2.4s,w2	//criando um vetor, onde cada posição assume o valor x
	
ciclo:	cbz x1,end
	ldr q0,[x0]
	
	addsq v0.4s,v0.4s,v2.4s	  //soma SATURADA
	
	str q0,[x0],#16
	sub x1,x1,1
	b ciclo

end:	ldp x29,x30,[sp],#16
	ret 
	
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#Questão 5 - void mirrorSeq(float *pt, int n) - x0,w1

.global mirrorSeq
.type mirrorSeq,"function"
.text

mirrorSeq: 
	stp x29,x30,[sp,#-16]! 
	lsr w1,w1,#1	# n é o número de pares

ciclo:	
	cbz w1,end
	ldr q1,[x0]
	
	//trocando a posição das variaveis
	ins v0.s[0], v1.s[1]
	ins v0.s[1], v1.s[0]
	ins v0.s[2], v1.s[3]
	ins v0.s[3], v1.s[2] 

	str q0,[x0],#16
	sub w1,w1,1
	b ciclo

end:	ldp x29,x30,[sp],#16
	ret
	
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
#Questão 6 - double normV(double *ptV, long int n) => x0, x1 
#ATENÇÃO: ADDV NÃO FUNCIONA PARA DOUBLES

#x9: guarda n para ser usado na soma (x1)
#x10: guarda o endereço do primeiro elemento do vetor para ser usado na soma (x0)
#d4: soma total 

.global normV
.type normV, "function" 
.text 

normV: 

//primeiro vamos fazer v^2 para todos os componentes 

	stp x29,x30,[sp,#-16]!

	mov x9, x1
	mov x10, x0

	mov x3, #0	//atribuindo d4 = 0
	scvtf d4,x3

	lsr x1,x1,#1	//dimensão do vetor é multipla de 2


ciclo: 	cbz x1,soma

	ldr q0, [x0]		//terá formato v0.2d
	fmul v0.2d,v0.2d,v0.2d 	//eleva ao quadrado
	str q0,[x0],#16 	//guarda o resultado

	sub x1,x1,1
	b ciclo

//Agora fazendo a soma de todos os componentes, já que não há uma função que faça isso com doubles (não funciona com addv)

soma: 	cbz x9, end 		

	ldr d1, [x10],#8
	fadd d4,d4,d1
	sub x9,x9,1

	b soma

end: 	fsqrt d4,d4
	fmov d0,d4
	ret


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
#Questão 7 - long int conta_inf(float *V, long int n, float lim) - x0,x1,s0

#s1: vector em questão
#s2: vector duplicado de lim
#s3: vector de comparação
#s4: soma do atual vector
#x5: contador 
#x4: soma do atual vector

.global conta_if
.type conta_inf, "function"
.text

conta_inf:
	stp x29,x30,[sp,#-16]!
	mov x5,#0		//contador
	dup v2.4s, v0.s[0]	//vector duplicado de lim. Atenção à sintax!
	lsr x1,x1,#2

ciclo:
	cbz x1, end
	ldr q1,[x0],#16

	cmgt v3.4s,v2.4s,v1.4s	//Não existe cmlt (compare less than)
	addv s4, v3.4s
	smov x4, v4.s[0]

	neg x4,x4
	add x5,x4,x5

	sub x1,x1,1
	b ciclo

end:
	mov x0,x5
	stp x29,x30,[sp],#16
	ret
	
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 8 - void ajuste ( float *X , float *Y , int n , float da )

x0,x1,w2,s0

.global codigo 
.type codigo, "function" 
.text 

codigo: 
	stp x29,x30,[sp,#-16]!
	lsr w2,w2,#2 
	
ciclo: 	cbz w2, end 
	
	ldr q1, [x0]
	ldr q2, [x1],#16  

	fabs v1.4s, v1.4s  	// fazendo abs(x[i])
	dup v0.4s, v0.s[0]	  	
	
	fmul v0.4s, v0.4s, v1.4s
	fsub v2.4s, v2.4s, v0.4s

	sub w2,w2,1

	str q2, [x1], #16 
	
	b ciclo

end:	ldp x29,x30,[sp],#16
	ret

	

