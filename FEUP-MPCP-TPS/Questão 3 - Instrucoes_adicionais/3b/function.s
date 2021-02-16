.global max_word;
.type max_word, %function
.text

			#w0 = vector
			#w1 = letra a procurar
			#w2 = letra atual
			#w3 = contador


max_word:

			mov w3, 0
inicio: 	ldrb w2, [x0]
			cmp w2, w1
			beq soma
ciclo: 		cmp w2, '0'
			beq fim
			add w0,w0,1
			b inicio

fim: 		mov w0, w3
			ret

soma: 		add w3, w3, 1
			b ciclo

