# FOLHA DE VÍRGULA FLUTUANTE
 
# Questão 1- Escrever fragmentos de código assembly AArch64 que implementem o seguinte código C++: 
  
# a)   double B = 7.8 , M = 3.6 , N = 7.1;  
#	double P = -M * ( N + B );  


.data
VB: .double 7.8
VM: .double 3.6
VN: .double 7.1

.global max_word
.type max_word, "function"
.text

#d0: B
#d1: M
#d2: N

max_word: 		LDR d0, VB
			LDR d1, VM
			LDR d2, VN
			FADD d2,d2,d0
			FNMUL d0, d2, d1
			RET



#--------------------------------------------------------------------------------------------------------------------------

# b) int W = 7; double X = 7.1;  
# double Y = sqrt ( X ) + W ;  

.data
W: .int 7
X: .double 7.1

.global max_word
.type max_word, "function"
.text

max_word: 

		LDR w0, W
		LDR d0, X

		FSQRT d0, d0
		UCVTF d1, w0
		FADD d0, d0,d1
		
		RET 

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
# Questão 2 -  Escrever um programa para calcular:

#a)

.data
A: .double 1.5
B: .double 2.5
C: .double 2.0
D: .double 0.5
const: .double 3

.global max_word
.type max_word, "function"
.text

max_word:

		LDR d0, A
		LDR d1, B
		LDR d2, C
		LDR d3, D
		LDR d4, const

		FSUB d1, d0, d1
		FMUL d1, d2, d1
		FADD d0, d0, d3
		FSUB d0, d0, d4
		FDIV d0, d1, d0
RET

#--------------------------------------------------------------------------------------------------------------------------
# b) 

.data
pi:  3,141592653

.global max_word
.type max_word, "function"
.text

max_word:

		STP x29, x30, [sp, #-16]!
		LDR d1, pi
		FMUL d0,d0,d0
		FMUL d0,d0,d1 
		LDP x29, x30, [sp], #16 
RET 
#--------------------------------------------------------------------------------------------------------------------------
# c)

.data
x1: .double 0
x2: .double 3
y1: .double 0
y2: .double 3

.global max_word
.type max_word, "function"
.text

max_word:

		LDR d0, x1
		LDR d1, x2
		LDR d2, y1
		LDR d3, y2

		FSUB d0, d0, d1
		FSUB d2, d2, d3
		FMUL d0,d0,d0
		FMUL d2,d2,d2
		FADD d0,d0,d2
		FSQRT d0,d0
RET


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#Questão 3 - Considere o polinómio p(x) = 1,5 x^3−12,5 x+ 7. Escreva a sub-rotina calc_poly_tab que calcula o
#polinómio para valores de x pertencentes a {0; 0,1; 0,2; · · · ; 9,9; 10} (ao todo são 101 valores). Assumir
#que para executar esta sub-rotina é chamada a função em C com o protótipo

#void calc_poly_tab(float *tab)

#em que tab é o vetor a ser preenchido com os valores p(0), p(0,1), · · · , p(9,9) e p(10).

.data
const_1.5: .float 1.5
const_12.5: .float 12.5
const_7: .float 7
const_0: .float 0
const_0.1: .float 0.1

.global calc_poly_tab
.type calc_poly_tab, "function"
.text

calc_poly_tab:
		stp x29,x30,[sp,#-16]!

		ldr s7, const_1.5
		ldr s8, const_12.5
		ldr s9, const_7
		ldr s10, const_0
		ldr s11, const_0.1
		mov x1, 101  //contador
		fmov s1, s10

begin:
		cbz x1, end
		fmul s2, s1, s1
		fmul s2, s2, s1 //calcula x^3
		fmul s2, s2, s7 //calcula 1.5*x^3
		fnmul s3, s1, s8 //calcula -12.5*x
		fadd s2, s2, s1
		fadd s2, s2, s9
		str s2, [x0]
		add x0, x0, #4
		fadd s1, s1, s11
		sub x1, x1, 1
		b begin
end: 		ldp x29, x30, [sp], #16

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 4 - double HORNER(double x, double *coefs, int n)

.global HORNER
.type HORNER, "function"
.text

HORNER:

		stp x29, x30, [sp, #16]! 
		ldr d1, [x0]  //d1: carrega os valores das constantes  
		fmul d2, d1, d0 
		add x0,x0,#8 
		ldr d1, [x0] 
		fadd d2, d2, d1
		sub w1, w1, 2
		add x0, x0, #8 

loop: 

		cbz w1, end 
		ldr d1, [x0] 
		fmul d2, d2, d0 
		sub w1, w1, 1
		add x0, x0, 8
		b loop 

end:		mov d0, d2
		ldp x29,x30, [sp], 16
		ret 
		

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 5 - double prodint(float *X, float *Y, int n). Calcular o produto vetorial:

.data

const_0: .double 0

.global prodint
.type prodint, "function"
.text

prodint: 		stp x29, x30, [sp, #-16]!
			ldr d0, const_0

loop:			cbz w2, end  //w2 = contador

			ldr s1, [x0] //carrega valor de x
			ldr s2, [x1] //carrega valor de y

			//convertendo tudo para double
			fcvt d1, s1
			fcvt d2, s2
			//operação
			fmul d3, d1, d2
			fadd d0, d3, d0
			 //fazendo update do contador
			sub w2,w2, 1
			add x0, x0, 4
			add x1, x1, 4
			b loop
end: 			ldp x29, x30, [sp], #16
			ret


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 6- long int conta_intervalo(float *V, long int n, float a, float b)

.global conta_intervalo
.type conta_intervalo, "function"
.text

conta_intervalo:
			stp x29, x30,[sp, #16]!
			mov x2, #0 		//x2 = contador
loop:
			cbz x1, end
			ldr s3, [x0]
			fcmp s3,s0
			b.lt proximo 	//caso s3 <a
			fcmp s3, s1
			b.gt proximo	//caso s3 >b
			add x2,x2,1	//caso esteja no intervalo
proximo:		add x0,x0,#4	//proximo elemento do vector
			sub x1,x1,#1	//atualiza o loop
			b loop

end:
			mov x0, x2
			ldp x29, x30, [sp], #16
			ret

#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#Questão 7 - double rotF(double x)

.data
pi: .double 3.141592653

.global rotF
.type rotF, "function"
.text

rotF:
		stp x29,x30,[sp,#-16]!
		fcmp d0, #0
		blt lessthan  //caso seja menor que zero
		
		ldr d1, pi
		fadd d0,d1,d0
		fmul d2, d0,d0
		fmul d2,d2,d0
		fsqrt d2,d2
end:	
		fmov d0,d2
		ldp x29,x30,[sp],#16
		ret

lessthan:
		mov x1, 4
		scvtf d1, x1
		fsub d0,d0,d1
		fneg d0,d0
		fsqrt d0,d0
		mov x1, 1
		scvtf d1,x1
		fdiv d0,d1,d0
		b end
		
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

# Questão 8 - double erfpos(double x)

.data

a1: .double 0.278393
a2: .double 0.230389
a3: .double 0.000972
a4: .double 0.078108

.global erfpos
.type erfpos, "function"
.text

#d1 = constantes
#d2 = resultado


erfpos:
	stp x29,x30,[sp,#-16]!
	ldr d1, a1
	fmov d2, #1
	fmul d1,d0,d1 //a1*x
	fadd d2, d1,d2 //1 + a1*x

	ldr d1, a2
	fmul d1, d1,d0	// a2*x
	fmul d1,d1,d0 	// a2*x^2
	fadd d2,d1,d2 	// 1 + a1*x + a2*x^2

	ldr d1, a3
	fmul d1,d1,d0	//a3*x
	fmul d1,d1,d0	//a3*x^2
	fmul d1,d1,d0	//a3*x^3
	fadd d2,d2,d1	// 1 + a1*x + a2*x^2 + a3*x^3

	ldr d1,a4
	mov x0, #4
loop:
	cbz x0, next_1
	fmul d1,d1,d0	//a4*x^4
	b loop
next:
	fadd d2,d1,d0 //// 1 + a1*x + a2*x^2 + a3*x^3 + a4*x^4

	fmul d3,d2,d2
	fmul d3,d2,d3
	fmul d3,d2,d3
	fmov d2,d3
	fmov d4,1
	fdiv d2,d4,d2
	fsub d0,d4,d2

	ldp x29,x30,[sp],#16
	ret

