.globl main

.data
vetor: .word -1, 5, 1, 1, 1, 4
.text

begin:
	add t3, zero, zero

soma:
	lw t2, 0(a0)
	addi a0, a0, 4
	add t3, t3, t2
	addi t1, t1, 1
	blt t1, a1, soma
	mv a0, t3
	ret
	
main:
	la a0, vetor
	li a1, 6
	jal begin