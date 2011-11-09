# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	strval:	.asciiz	"Entrez la valeur : "
	str:	.asciiz	"La valeur passée en paramètre : "
	endl:	.asciiz "\n"

.text
.globl __start

__start:	li $v0, 4
			la $a0, strval
			syscall
# On prend une valeur qu'on va afficher
			li $v0, 5
			syscall
			move $a0, $v0
# Appel de la fonction
			jal writeln

# On réaffiche qu'on veut une valeur
			li $v0, 4
			la $a0, strval
			syscall
# On prend une autre valeur
			li $v0, 5
			syscall
			move $a0, $v0
# Appel de la fonction
			jal writeln

fin:		li $v0, 10
			syscall

writeln:	addu $sp, $sp, -4
			sw $ra, 4($sp)
			move $t0, $a0
			# Affichage 
			li $v0, 4
			la $a0, str
			syscall
			li $v0, 1
			move $a0, $t0
			syscall
			li $v0, 4
			la $a0, endl
			syscall
			
			lw $ra, 4($sp)
			add $sp, 4
			jr $ra
