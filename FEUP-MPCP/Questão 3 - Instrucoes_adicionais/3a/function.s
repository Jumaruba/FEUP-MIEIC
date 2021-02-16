.global max_word;
.type max_word, %function
.text

			#w0 = vector
			#w1 = caracter atual
			#w2 = contador


max_word:
			mov w2, 0
inicio: 		ldrb w1, [x0]
			cmp w1, '0'
			beq fim
			add w0, w0, 1
			add w2, w2, 1
			b inicio

fim: 			mov w0, w2
			ret


