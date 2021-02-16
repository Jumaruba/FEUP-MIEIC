.global max_word;
.type max_word, %function
.text

			#w0 = vector
			#w1 = letra atual
			#w2 = contador


max_word:
			mov w2, 0
inicio: 	ldrb w1, [x0]
			cmp w1, 'a'
			bge compara
jump: 		add w0, w0, 1
			cmp w1, '0'
			bne inicio
			mov w0, w2
			ret

compara: 	cmp w1, 'z'
			bgt jump
			add w2, w2, 1
			b jump


