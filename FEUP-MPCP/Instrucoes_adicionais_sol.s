
# 2. Escrever e testar programas que permitam calcular:
# a) o valor máximo de um vetor com dados do tipo word .
# b) o valor mínimo de um vetor com dados do tipo doubleword .
# c) o valor máximo de um vetor com dados do tipo halfword .
# d) o valor médio de um vetor com dados de 64 bits.
# e) o número de valores de um vetor que pertencem ao intervalo [a; b].

#LETTER A 

	# x0 = vector 
	# x1 = dimension 
	# x2 = actual value
	# x3 = result

	MAX: 	MOV w3, #0

	CICLO: 	CBZ w1, END		;case length.vector = NULL
		LDRSW w2, [x0]		;loading the actual value
		CMP w3, w2		
		CSEL w3, w2, w3, GT	;check if the the actual value is greater than the greatest value until now
		ADD w0, w0, #4		;next element in the vector
		SUB w1, w1, #1		;update the counter
		B CICLO
	END:	MOV w0, w3		

#LETTER B
	  
	# x0 = vector 
	# x1 = dimension 
	# x2 = actual value
	# x3 = result
	
	MIN: 	MOV x3, #0
	CICLO: 	CBZ x1, END
		LDR x2, [x0] 
		CMP x2, w3
		CSEL x3, x2, x3, LT
		ADD x0, x0, #8
		SUB x1, x1, #1
		B CICLO 
	END: 	MOV x0, x3
		RET 

#LETTER C
		 
	# x0 = vector 
	# x1 = dimension 
	# x2 = actual value
	# x3 = result

	MAX: 	MOV w3, #0

	CICLO: 	CBZ w1, END
		LDRSH w2, [x0]
		CMP w3, w2
		CSEL w3, w2, w3, GT
		ADD w0, w0, #4
		SUB w1, w1, #1
		B CICLO
	END:	MOV w0, w3


#LETTER D

	#x0 = vector
	#x1 = dimension
	#x2 = actual value
	#x3 = sum
	#x4 = dimension (immutable)
	
	MAX: 	MOV x3, #0
		MOV x4, x1
	CICLO:	CBZ x1, END
		LDR x2, [x0] 
		ADD x3, x3, x2
		ADD x0, x0, #8
		SUB x1, x1, #1
		B CICLO
	END: 	SDIV x0, x3, x4
		RET 

#LETTER E

	#x0 = vector
	#x1 = dimension 
	#x2 = interval floor
	#x3 = max element of the interval 
	#x4 = acutal value 
	#x5 = counter

	ROT:	MOV x5, #0
	CICLO: 	CBZ x1, END
		lDR x4, [x0]
		CMP x4, x2
		B.GE COMP
	CONT: 	ADD x, x0, #8
		SUB x1, x1 #1
		B CICLO

	COMP: 	CMP x4, x3 
		B.GT CONT
		ADD x5, x5, #1
		B CONT

	END:	MOV x0, x5
		RET 

#--------------------------------------------------------------------------------------------------------------------------------------
# 3. Pretende-se escrever programas que executam tarefas envolvendo uma cadeia de carateres terminada
# por zero ( ’\0’ ).
# a) Determinar o comprimento de uma cadeia de carateres.
# b) Determinar o número de ocorrências de um caráter numa cadeia de carateres.
# c) Determinar o número de vogais de uma cadeia de carateres.
# d) Determinar o número de letras maiúsculas de uma cadeia de carateres.
# e) Palíndromo é uma palavra, grupo de palavras ou verso em que o sentido é o mesmo, quer se
# leia da esquerda para a direita quer da direita para a esquerda (ex.: "ANOTARAM A DATA DA
# MARATONA").
# Implementar um programa que determine se uma cadeia de carateres é palíndromo. Assumir
# que a cadeia de carateres não inclui espaços nem sinais de pontuação e que é indiferente o uso
# de letras maiúsculas e minúsculas. A sub-rotina devolve 1 em caso afirmativo ou 0 no caso
# contrário.
# f) Contar quantas palavras tem uma cadeia de carateres, assumindo que há um único espaço entre
# palavras consecutivas.


#--------------------------------------------------------------------------------------------------------------------------------------
# 4. Implementar e testar programas que realizem as seguintes tarefas:
# a) Copiar um vetor com valores (sem sinal) do tipo byte para um vetor com valores do tipo doubleword .
# b) Copiar um vetor com valores (com sinal) do tipo word para um vetor com valores do tipo
# doubleword .

#LETTER A 

	#x0 = vector font
	#x1 = arrival vector
	#x2 = vector font size
	#x3 = actual value

	FUNC: 	
	CICLO:	CBZ x2, END
		LDRB w3, [x0] 
		UXTB x3, w3
		STR w3, [x2] 
		ADD x0, x0, #1
		ADD x1, x1, #8	
		SUB x2, x2, #1
		B CICLO
	END: 	RET 

# LETTER B

	#C CODE
	
	#include <stdio.h>
	extern void extend(int* n2, long int* n, int dim);

	int main(void)
	{
		int vetor1[] = {1,2,-3,-4,-5,0};
		long int vetor2[6];

		extend(vetor1, vetor2, 6);

		for (int i = 0; i< 6; i++){
			printf("v[%d] = %lld\n", i, vetor2[i]);
		}
		return 0;

	}

	#ASSEMBLY CODE

	.global extend;
	.type extend, %function
	.text

	extend:

	#x0 = vector font
	#x1 = arrival vector
	#x2 = vector font size
	#x3 = actual value

 
	CICLO: 	CBZ x2, END
		LDRSW x3, [x0]	
		SXTW x3, w3 
		STR x3, [x1]
		ADD x0, x0, #4
		ADD x1, x1, #8
		SUB x2, x2, #1
		B CICLO
	END:	RET 

#--------------------------------------------------------------------------------------------------------------------------------------
#5. Escrever e testar sub-rotinas considerando os respetivos protótipos da função a invocar em C.
# a) Determinar a posição do bit 1 mais significativo da representação binária de um número.
# int POS1msb(long int n);

# b) Verificar se uma cadeia de 8 carateres (tamanho de uma doubleword) é palíndromo. A resposta
# será 1 em caso afirmativo e 0 no caso contrário.
# int PAL8(char *s);

# c) Verificar se a representação binária de um número é capicua (número palíndromo). A resposta
# será 1 em caso afirmativo e 0 no caso contrário.
# int NCAP(int n);

#LETTER A 

	POS1msb:
		
	clz x2, x0  ; counting leading zeros by left
	mov x3, 63
	sub x0, 63
	sub x0, x3, x2
	ret

#LETTER B 

	# x0 = char
	# x1 = reversed char
	# x2 = palindrom or not
	
	PAL8:
	
	REV x1, x0
	CMP x1, x0
	CSET x2, EQ
	MOV x0, x2
	RET 

#LETTER C
	
	#x0 = int
	#x1 = reversed number
	#x2 = capicua or not
	
	NCAP:
	RBIT w1, w0
	CMP w1, w0
	CSET x2, EQ
	MOV x0, x2
	RET 

#--------------------------------------------------------------------------------------------------------------------------------------
	
# 6.Implementar as instruções seguintes com base em instruções de manipulação ou extração de bits.

#LETTER A

 LSL x10, x12, #8 
 
 # We may use `UBFIZ` _(unsignal bit field insert in zero)_ as alternative:  
   
 UBFIZ x10, x12, #8, #56
 
#LETTER B 

 ASR x10, x12, #8 
   
 # We may use  SBFX (signal bit field extract) as alternative:   
   
SBFX x10, x12, #8, #56

#LETTER C

ROR w13, w14, #3 

# this is the instruction rotate right  
  
ubfiz w13, w14, #3, #29
bfi w13, w14, #3, #29

#--------------------------------------------------------------------------------------------------------------------------------------
# 8. Determinar o valor de W0 após a execução de cada fragmento de código.
# a) 
	MOV W0, #0x66666666  	; W0 = 0110 0110 0110 0110 0110 0110 0110 0110 
	MOV W1, #0xF000000F	; W1 = 1111 0000 0000 0000 0000 0000 0000 1111
	AND W0, W0, W1		; W0 = 0110 0000 0000 0000 0000 0000 0000 0110 
	EOR W0, W0, W1		; W0 = 1001 0000 0000 0000 0000 0000 0000 1001
	ORR W0, W0, #0x66666666	; W0 = 1111 0110 0110 0110 0110 0110 0110 1111
	
# b) 

	MOV W0, #0x0000BEEF		;W0 = 0000 0000 0000 0000 1011 1110 1110 1111
	ADDS W0, W0, #0x00008000	;W0 = 0000 0000 0000 0001 0011 1110 1110 1111	
	MOV W1, #0x00003EEE		;W1 = 0000 0000 0000 0000 0011 1110 1110 1110
	SBC W0, W0, W1			;(W0 - W1 - 1) W0 = 0000 0000 0000 0001 0000 0000 0000 0000
	ADC W0, W0, W0			;W0 = 0000 0000 0000 0010 0000 0000 0000 0000
	
#--------------------------------------------------------------------------------------------------------------------------------------
# 9.Considerar que o valor inicial de `W0 é 0x12345678`. Determinar o valor de W1 (ou X1) após a execução
# de cada fragmento de código.
  

# letter a 
    # w0 = 0001 0010 0011 0100 0101 0110 0111 1000
    
    MOV W1, #0xABCD0000  ;w1 = 1010 1011 1100 1101 0000 0000 0000 0000  
    UBFX W2, W0, #24, #8 ;w2 = 0000 0000 0000 0000 0000 0000 0001 0010
    BFI W1, W2, #16, #8  ;w1 = 1010 1011 0001 0010 0000 0000 0000 0000
 

# letter b
  
    # w0 = 0001 0010 0011 0100 0101 0110 0111 1000
    
    REV W1, W0                ;w1 = 0x78564312   w1 = 0111 1000 0101 0110 0011 0100 0001 0010
    AND W1, W1, W1, ASR #16   ;w1' = 1000 0000 0000 0000 0111 1000 0101 0110 -- W1, ASR #16
                              ;w1 =  0111 1000 0101 0110 0011 0100 0001 0010
                              ;w1 =  0000 0000 0000 0000 0011 0000 0001 0010 -- NEW W1 = 0X78564012
    REV W1, W1                ;w1 =  0001 0010 0011 0000 0000 0000 0000 0000
    SUB W1, W0, W1            ;w0 =  0001 0010 0011 0100 0101 0110 0111 1000
                              ;w0 =  0000 0000 0000 0100 0101 0110 0111 1000                                     
    
 
    
    
# letter c 

    # w0 = 0001 0010 0011 0100 0101 0110 0111 1000
    
    EON X1, X1, X1                ;x1 = 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 1111 
    ADD X1, X1, W0, SXTB #4       ;w0 = 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111 1000 0000
                                  ;x1 = 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0111 0111 1111



  
