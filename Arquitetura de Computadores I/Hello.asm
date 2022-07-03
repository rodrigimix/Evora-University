.globl main

	.data
A:	.string "Hello World!"

.text

upper_case:
	li t1, 97		#1
	li t2, 122		#1
CICLO:

	lbu t0, 0(a0)		#13
	beqz t0, SAI		#13
	blt t0, t1, SALTA	#12
	bgt t0, t2, SALTA	#8
	addi t0, t0, -32	#8
	sb t0, 0(a0)		#8

SALTA:
	addi a0, a0, 1		#12
	j CICLO			#12
	
SAI:
	ret

main:
	la a0, A		#1
	jal upper_case		#1

Tempo de instruções executadas = 89*0,5 = 44,5 ns