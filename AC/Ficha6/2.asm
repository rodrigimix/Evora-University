.globl main
.text

While: 	blt a1, t0, End2
	add a0, a0, t0
	addi t0, t0, 1
	beq zero, zero, While
End2:	ret

Sum:
	addi sp, sp, -4
	sw ra, 0(sp)
	mv t0, a0
	li a0, 0
	blt a1, t0, END
	jal While
	lw ra, 0(sp)
	addi sp, sp 4
	ret

		
END: 	add a0, zero, zero
	ret
	
	
main:
	li a0, 5
	li a1, 3
	jal Sum
