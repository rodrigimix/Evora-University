.globl main

.data
A: 	.word -1, 3, 5, -2, 4
.text

max:
	lw t0, 0(a0)
CICLO:	
	addi a1, a1, -1
	beqz a1, SAI
	addi a0, a0, 4
	lw t1, 0(a0)
	ble t1, t0, SALTA
	mv t0, t1

SALTA: j CICLO

SAI:	
	mv a0, t0
	ret						
main:
	la a0, A
	li a1, 5
	jal max