# 4. Utilizando a pilha, escrever um programa que:
# a) imprime uma cadeia de carateres por ordem inversa.

# b) verica se uma sequência de carateres tem parêntesis curvos, parêntesis retos e chavetas corre-
# tamente emparelhadas.

#LETTER A 

# x0 = cadeia de caracteres (preservado)
# x1 = dimensão da cadeia (preservado)

	#x0 = vector 1
	#x1 = tamanho da sequencia 1
	#x2 = vector 2
	#x3 = tamanho da sequencia 2


	#x20 = tamanho da sequencia 1
	#x21 = tamanho da sequencia 2
	#x22 = media do vector 1



max_word: 		stp x29, x30, [sp, #-16]!
			mov x29, sp
			mov x20, x0
			mov x21, x1

CICLO:			cbz w1, PROX
			ldrb w2, [x0]
			str w2, [SP, #-16]!
			add w0, w0, #1
			sub w1, w1, #1
			b CICLO

PROX: 			mov x0, x20
			mov x1, x21

CICLO2:			cbz w1, END
			ldr w2, [sp], #16
			strb w2, [x0]
			add w0, w0, #1
			sub w1, w1, #1
			b CICLO2

END:			mov sp, x29
			ldp x29, x30, [sp], #16
			ret


		
#-------------------------------------------------------------------------------------------------------------------------
# 5. Escrever e testar as seguintes sub-rotinas:
# a) SOMA – calcula a soma dos elementos de um vetor.
# b) MEDIA – calcula a média dos elementos de um vetor utilizando a sub-rotina SOMA .
# c) MAXMED – calcula a média dos elementos de dois vetores e retorna a maior das duas médias.

# respecting the sinxtax of registers

.global max_word;
.type max_word, %function

.data


.text

	#x0 = vector 1
	#x1 = tamanho da sequencia 1
	#x2 = vector 2
	#x3 = tamanho da sequencia 2


	#x20 = tamanho da sequencia 1
	#x21 = tamanho da sequencia 2
	#x22 = media do vector 1



max_word:

	#x10 = valor atual
	#x11 = soma
	#altera registro x0 e x1 é preservado

MAXMED: 	stp x29, x30, [sp, #-16]!
		mov x29, sp

		mov x20, x1
		mov x21, x3
		bl MEDIA
		mov x22, x0

		mov x0, x2
		mov x1, x3
		bl MEDIA
		mov x23, x0

		CMP x22, x23
		CSEL x0, x22, x23, GT

		mov sp, x29
		ldp x29, x30, [sp], #16
		ret


MEDIA: 		stp x29, x30, [sp, #-16]!
		mov x29, sp

CICLO1: 	BL SOMA
		sdiv x0, x0, x1

		mov sp, x29
		ldp x29, x30, [sp], #16
		RET



SOMA: 		stp x29, x30, [sp, #-16]!
		mov x29, sp
		str x1, [sp, #-16]!
		mov x11, #0

CICLO: 		cbz x1, END
		ldr x10, [x0]
		add x11, x11, x10
		add x0, x0, #8
		sub x1, x1, #1
		b CICLO

END: 		ldr x1, [sp], #16
		mov sp, x29
		ldp x29, x30, [sp], #16
		mov x0, x11
		RET




