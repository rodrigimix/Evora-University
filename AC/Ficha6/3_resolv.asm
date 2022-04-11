.globl main
.text

sum:
	mv t0, a0
	li a0, 0
	bgt t0, a1, END
	
SOMA:
	add a0, a0, t0
	addi t0, t0, 1
	ble t0, a1, SOMA
	
END:
	ret

#Numero de instruções executadas 32
#Tempo de execução 1 inst = 2 ns
# 0.000065 ms

main:
	li a0, 1
	li a1, 3
	jal sum
