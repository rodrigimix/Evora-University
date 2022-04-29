.globl main
.text

abs:
	mv t0, a0
	bge t0, zero, SAI
	addi t1, zero, -1
	mul t0, t0, t1
	
SAI:
	mv a0, t0
	ret
	

main:
	li a0, -20
	jal abs