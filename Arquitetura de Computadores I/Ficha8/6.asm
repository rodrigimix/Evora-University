.globl main

.data
A: .word 1, 3, 5, 7, -9

.text


max: 
	bge a0, a1, sai_max #(a0 >= a1) (a0 < a1)
	mv a0, a1

sai_max: ret


array_max:	
	addi sp, sp, -16
	sw ra, 12(sp)
	  
	addi t1, zero, 1 #i = 1
	mv t2, a1	#t2 = sz

	mv t0, a0 # t0 tem o address do array
	
	lw a0, 0(t0)
	addi t0, t0, 4
	
	for: bge t1, t2, sai_array_max #t1 < t2 (i < sz)
		#a0 e a1 terão os valores a comparar
		lw a1, 0(t0)
		addi t0, t0, 4
		
		sw t0, 8(sp)
		sw t1, 4(sp)
		sw t2, 0(sp)
		
		jal max
		
		lw t0, 8(sp)
		lw t1, 4(sp)
		lw t2, 0(sp)
		
		addi t1, t1, 1
		j for	

sai_array_max:	lw ra, 12(sp)
		addi sp, sp, 16
		ret


main:
	la a0, A
	li, a1, 5
	jal array_max