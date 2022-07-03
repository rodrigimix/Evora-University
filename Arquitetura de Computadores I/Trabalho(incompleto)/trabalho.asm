.globl main

.data
rgb: .asciz "Lenna.rgb"
gray: .asciz "Lenna_final.gray"
Buffer: .space 786432 #512x512x3
Buffer2: .space 262144 #512x512
Buffer_C: .space 262144
B_SH: .space 262144
B_SV: .space 262144
s_h: .word -1, 0, 1, -2, 0, 2, -1, 0, 1
s_v: .word -1, -2, -1, 0, 0, 0, 1, 2, 1


.text

###################################################################################
#Função: read_rgb_image
#Descrição: Esta função lê os pixeis da imagem e copia esses pixeis para um buffer.
#Argumentos:
#	a0 - endereço da imagem
#	s6 - preserva o endereço a0
#	a7 - nº do serviço prestado para o system call
#	a1 - (1ªParte) - abre o ficheiro para ler; (2ªParte) - é o endereço do buffer onde vai clonar os pixeis da imagem
#	a2 - tamanho da imagem
#	sp - pilha, onde preserva s6
#Retorna:
#	a1 - Buffer da Imagem
###################################################################################
read_rgb_image:
	addi sp, sp, -4
	sw s6, 0(sp)
	li a7, 1024
	la a0, rgb
	li a1, 0
	ecall
	mv s6, a0
	
	
	li a7, 63
	mv a0, s6
	la a1, Buffer
	li a2, 786432
	ecall
	
	li a7, 57
	mv a0, s6
	ecall
	lw s6, 0(sp)
	addi sp, sp, 4
	ret

	
###################################################################################
#Função: write_gray_image
#Descrição: Esta função escreve para o ficheiro da imagem (tipo gray) a partir de um buffer.
#Argumentos:
#	a0 - endereço da imagem
#	s6 - preserva o endereço a0
#	a7 - nº do serviço prestado para o system call
#	a1 - (1ªParte) - abre o ficheiro para escrever; (2ªParte) - escreve o ficheiro a partir de um buffer
#	a2 - tamanho do buffer
#	sp - pilha, onde preserva s6
#Retorna:
#	a0 - Imagem final do Buffer_C
###################################################################################	
write_gray_image:
	addi sp, sp, -4
	sw s6, 0(sp)
	li a7, 1024
	la a0, gray
	li a1, 1
	ecall 
	mv s6, a0
	
	
	li a7, 64
	mv a0, s6
	la a1, Buffer_C
	li a2, 262144
	ecall
	
	li a7, 57
	mv a0, s6
	ecall
	lw s6, 0(sp)
	addi sp, sp, 4
	ret

###################################################################################
#Função: rgb_to_gray
#Descrição: Esta função converte um buffer com pixeis de rgb para formato gray.
#Argumentos:
#	t1 - nº indicado pela formula rgb -> gray para conveter o pixel R em gray
#	t2 - nº indicado pela formula rgb -> gray para conveter o pixel G em gray
#	t3 - nº indicado pela formula rgb -> gray para conveter o pixel B em gray
#	s0 - esse número permite transformar os numeros t1, t2, t3 em decimais
#	t0 - tamanho do Buffer 512x512
#	s1 - lê o nº do pixel da Imagem RGB
#	t4 - (R) - multipliação do s1 e t1 | soma com o t5 e t6 | guarda o valor da divisão com o s0 e guarda esse valor no Buffer
#	t5 - multipliação do s1 e t2
#	t6 - multipliação do s1 e t3
#	a0 - endereço da Imagem RGB
#	a1 - endereço do Buffer
#	sp - pilha, guarda e retorna os valores de s0 e s1
#Retorna:	
#	a1 - Buffer Gray
###################################################################################

rgb_to_gray:
	addi sp, sp, -8
	sw s1, 4(sp)
	sw s0, 0(sp)
	li t1, 30
	li t2, 59
	li t3, 11
	li s0, 100
	li t0, 262144
ciclo:
	#R
	lbu s1, 0(a0)
	mul t4, s1, t1
	addi a0, a0, 1
	#G
	lbu s1, 0(a0)
	mul t5, s1, t2
	addi a0, a0, 1
	#B
	lbu s1, 0(a0)
	mul t6, s1, t3
	addi a0, a0, 1
	#I
	add t4, t4, t5
	add t4, t4, t6
	div t4, t4, s0
	
	sb t4, 0(a1)
	addi t0, t0, -1
	addi a1, a1, 1
	bnez t0, ciclo
	lw s0, 0(sp)
	lw s1, 4(sp)
	addi sp, sp, 8
	ret

###################################################################################
#Função: convolution
#Descrição: Esta função calcula a convolução de um Buffer com um operador Sobel.
#Argumentos:
#	sp - pilha, guarda e retorna os valores de s0, s1, s2 e ra
# 	ra - return adress
# 	s2 - tamanho da imagem total - 512 - 1
#	s0 - tamanho total da imagem 512x512
#	s1 - constante
#	t0 - contador de posições
#	t4 - somatório e guarda o somatório no Buffer com Sobel alterado
#	t3 - contador regressivo de 512 a 0
#	a0 - endereço do Buffer Gray sem sobel
#	t5 - é uma variavel que guarda os calculos necessarios para localizar o pixel correto no buffer
#	t6 - lê  nº do pixel do Buffer e funciona também como operador de multiplicar entre o o numero do pixel do buffer e o operador sobel
#	t1 - lê o nº da posição do Buffer Sobel
#	a2 - endereço do Buffer com Sobel alterado
#Retorna:
#	a2 - Imagem do buffer com sobel
###################################################################################
convolution:
	addi sp, sp, -20
	sw ra, 16(sp)
	sw s0, 12(sp)
	sw s1, 8(sp)
	sw s2, 4(sp)
	li s2, 261631
	li s0, 262144
	li s1, 514
	li t0, 514
	li t4, 0
	li t3, 512
	li t2, 255
	sw a0, 0(sp)
	
inicio:
	lw a0, 0(sp)
	
	sub t5,t0,s1
	sub t5,s0,t5
	sub t5,s0,t5
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 0(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_cc:
	lw a0, 0(sp)
	
	sub t5,t0,s1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5, t5, 1
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 4(a1)
	mul t6, t6, t1
	add t4, t4, t6

s_cd:
	lw a0, 0(sp)
	
	sub t5,t0,s1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5, t5, 2
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 8(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_e:
	lw a0, 0(sp)
	
	addi t5,s1,-1
	sub t5,s0,t5
	sub t5,s0,t5
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 12(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_c:
	lw a0, 0(sp)
	
	addi t5,s1,-1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5,t5,1
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 16(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_d:
	lw a0, 0(sp)
	
	addi t5,s1,-1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5,t5,2
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 20(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_be:
	lw a0, 0(sp)
	
	addi s1,s1,-2
	
	add t5,t0,s1
	addi t5,t5,-1
	sub t5,s0,t5
	sub t5,s0,t5
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 24(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_bc:
	lw a0, 0(sp)
	
	add t5,t0,s1
	addi t5,t5,-1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5,t5,1
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 28(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
s_bd:
	lw a0, 0(sp)
	
	add t5,t0,s1
	addi t5,t5,-1
	sub t5,s0,t5
	sub t5,s0,t5
	addi t5,t5,2
	
	add a0, a0, t5
	lbu t6, 0(a0)
	lw t1, 32(a1)
	mul t6, t6, t1
	add t4, t4, t6
	
	ble t4, t2, condition
	add t4, zero, t2
	
condition:
	sb t4, 0(a2)
	addi a2, a2, 1
	addi t3, t3, -1
	beq t0, s2, sai
	beqz t3, troca
	addi t0, t0, 1
	addi s1, s1, 2
	li t4, 0
	j inicio
	
troca:
	addi t0, t0, 3
	li t3, 512
	li t4, 0
	j inicio
	
sai:
	lw ra, 16(sp)
	lw s0, 12(sp)
	lw s1, 8(sp)
	lw s2, 4(sp)
	addi sp, sp, 20
	ret
	

###################################################################################
#Função: contour
#Descrição: Esta função calcula a imagem final combinando as duas imagens convolvidas
#Argumentos:
#	t0 - (1ªParte) representa o 25 com o objetivo de torna-la 0.25 | (2ªParte) lê o numero guardado no Buffer a0
#	t1 - (1ªParte)  representa o 100 com o objetivo de torna-la 0.25 | (2ªParte) lê o numero guardado no Buffer a1
#	t4 - tamanho do buffer dos sobeis
#	t5 - (1ªParte) contador que controla o calculos do sobel (Bv e Bh) | (2ªParte)  representa o 2 com o objetivo de dividir a soma dos dois sobeis e dividir com este numero
#	t2 - lê o numero guardado no Buffer a0
#	a0 - Endereço: (1ªParte) - B_SH | (2ªParte) - B_SV | (3ªParte) - B_SH 
#	a1 - Endereço do B_SV
#	a2 - Endereço do Buffer_C
#	t6 - representa o 255 com o objetivo de ter uma intensidade alta
#Retorna:
#	a2 - Imagem do buffer com os contornos
###################################################################################				
contour:
	li t0, 25
	li t1, 100
	li t4, 262144
	li t5, 2
ciclo2:
	lbu t2, 0(a0)
	not t2,t2
	addi t2, t2,1
ciclo3:
	mul t2, t2, t0
	div t2, t2, t1
	sb t2, 0(a0)
	addi a0, a0, 1
	addi t4, t4, -1

	bnez t4, ciclo2
	beqz t5, c_matriz
	
	addi t5, t5, -1
	mv a0, a1
	li t4, 262144
	j ciclo2
	
c_matriz:
	li t2, 513
	li t6, 255
	li t4, 262144
	la a0, B_SH
	beq zero, zero, ciclo4
ciclo4_1:
	li t2, 2
ciclo4:
	sb zero, 0(a2)
	addi a2, a2, 1
	addi t2, t2, -1
	bnez t2, ciclo4
	li t2, 511
ciclo5:
	lbu t0, 0(a0)
	lbu t1, 0(a1)
	add t0, t0, t1
	div t0, t0, t5
	sub t0, t6, t0
	sb t0, 0(a2)
	addi a2, a2, 1
	addi a0, a0, 1
	addi a1, a1, 1
	addi t4, t4, -1
	addi t2, t2, -1
	
	beqz t4, final
	beqz t2, ciclo4_1
	j ciclo5

	
final:
	li t2, 513	
ciclo6:
	sb zero, 0(a2)
	addi a2, a2, 1
	addi t2, t2, -1
	bnez t2, ciclo6
	
	ret

main:
	jal read_rgb_image
	
	la a0, Buffer
	la a1, Buffer2
	jal rgb_to_gray
	
	la a0, Buffer2
	la a1, s_h
	la a2, B_SH
	jal convolution
	
	la a0, Buffer2
	la a1, s_v
	la a2, B_SV
	jal convolution
	
	la a0, B_SH
	la a1, B_SV
	la a2, Buffer_C
	jal contour
	jal write_gray_image
	
