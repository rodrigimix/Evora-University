.globl main
.text
max:
	mv t0, a0
	mv t1, a1
	bge t0, t1, Primeiro
	add t2, t1, zero
	beq zero, zero, END 

Primeiro: 
	add t2, t0, zero

END:
	mv a0, t2
	ret

main:
	li a0, 3
	li a1, 1
	jal max