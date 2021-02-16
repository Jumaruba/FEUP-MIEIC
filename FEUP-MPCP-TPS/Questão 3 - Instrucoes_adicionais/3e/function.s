.global max_word;
.type max_word, %function
.text

			#w0 = vector
			#w1 = letra atual/ valor da atual da sequencia reversa
			#w2 = contador de caracteres
			#w3 = diferenca entre letras maiusculas e minusculas na tabela ascii/ valor atual da sequencia uniforme
			#w4 = contagem sequencial
			#w5 = 1 se a sequencia é palindrome
			#estrategia = contar o numero de palavras e, ao mesmo tempo, converter letras minusculas para maiusculas. Depois percorrer o vetor

max_word:

			mov w2, -1
			mov w4, 0
			mov w3, #32
inicio: 		add w2, w2, 1
			ldrb w1, [x0, x2]
			cmp w1, '0'
			beq diminui
			cmp w1, 'a'
			bge soma
			b inicio


soma: 			sub w1, w1, w3
			strb w1, [x0, x2]
			b inicio

diminui: 		sub w2,w2,1
proximo:		cmp w2, #-1
			beq end
			ldrb w1, [x0, x2]
			ldrb w3, [x0, x4]
			cmp w1, w3
			bne n_palindrome
			add w4, w4, 1
			sub w2, w2, 1
			b proximo
end:			mov w0, #1
			ret

n_palindrome: 		mov w0, #0
			ret


