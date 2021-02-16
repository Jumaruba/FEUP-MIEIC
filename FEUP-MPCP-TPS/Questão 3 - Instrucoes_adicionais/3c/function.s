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
			beq soma
			cmp w1, 'A'
			beq soma
			cmp w1, 'e'
			beq soma
			cmp w1, 'E'
			beq soma
			cmp w1, 'i'
			beq soma
			cmp w1, 'I'
			beq soma
			cmp w1, 'o'
			beq soma
			cmp w1, 'O'
			beq soma
			cmp w1, 'u'
			beq soma
			cmp w1, 'U'
			beq soma
jump: 		add w0, w0, 1
			cmp w1, '0'
			bne inicio
			mov w0, w2
			ret

soma: 		add w2, w2, 1
			b jump


