.globl main
.text
max:
	mv t0, a0
	mv t1, a1
	bge t0, t1, Primeiro
	mv t2, t1
	beq zero, zero, END 
	ret

abs:
	addi sp, sp, -4
	sw ra, 0(sp)
	mv t0, a0
	addi t1, zero, -1
	mul t2, t0, t1
	mv a1, t2
	jal max
	lw ra, 0(sp)
	addi sp, sp, 4
	ret

Primeiro: 
	mv t2, t0

END:
	mv a2, t2
	ret

main:
	li a0, 10
	jal abs