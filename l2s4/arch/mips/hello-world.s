# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	helloworld:	.asciiz	"Hello World !\n"

.text
.globl __start

__start:	li $v0, 4
			la $a0, helloworld
			syscall

fin:		li $v0, 10
			syscall
	
