# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	val1:	.asciiz	"Entrez la valeur 1 : "
	val2:	.asciiz	"Entrez la valeur 2 : "
	res:	.asciiz "Le résultat est : "
	endl:	.asciiz "\n"

.text
.globl __start

__start:	li $v0, 4
			la $a0, val1
			syscall
label1:		li $v0, 5
			syscall
			move $t0,$v0
label2:		li $v0, 4
			la $a0, val2
			syscall
			li $v0, 5
			syscall
			move $t1,$v0
afficheres:	li $v0, 4
			la $a0, res
			syscall
			add $t2, $t1,$t0
			li $v0, 1
			move $a0, $t2
			syscall
			li $v0, 4
			la $a0, endl
			syscall
fin:		li $v0, 10
			syscall
	
