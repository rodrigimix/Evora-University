.globl main
.text
max:
	bge a0, a1, END
	mv a0, a1
	
END: 	ret

max3:
	addi sp, sp, -8
	sw ra, 4(sp)
	sw a0, 0(sp)
	
	jal max #a0 = max(a0, a1)
	
	lw a1, 0(sp)
	jal max #a0 = max(max(a0,a1), a2)
	
	lw ra, 4(sp)
	addi sp, sp, 8
	ret
	
main:
	li a0, 3
	li a1, 5
	li a2, 4
	jal max3
