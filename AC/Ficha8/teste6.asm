.globl main

.data
vetor: .word -1, 5, 1, 1, 1, 10
.text

begin:
	addi sp, sp, -4
	sw ra, 0(sp)
	lw t0, 0(a0)
	addi t2, zero, 1

max:
	addi a0, a0, 4
	lw t1, 0(a0)
	bge t0, t1, verify
	mv t0, t1
	j verify

for:
	addi t2, t2, 1
	j max

verify:
	bge t2, a1, sair
	j for

sair:
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a0, t0
	ret
	
main:
	la a0, vetor
	li a1, 6
	jal begin
	
	
	