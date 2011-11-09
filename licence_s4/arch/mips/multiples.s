# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	saisira:	.asciiz	"Entrez la valeur de a : "
	saisirb:	.asciiz	"Entrez la valeur de b : "
	str:	.asciiz	"Leur multiplication : "
	endl:	.asciiz "\n"

.text
.globl __start

__start:	li $v0, 4
			la $a0, saisira
			syscall
# On prend une valeur qu'on va afficher
			li $v0, 5
			syscall
			move $t0, $v0

# On réaffiche qu'on veut une valeur
			li $v0, 4
			la $a0, saisirb
			syscall
# On prend une autre valeur
			li $v0, 5
			syscall
			move $t1, $v0

# Charge les paramètres dans la pile
			sub $sp, 8
# On écrit les valeurs
			sw $t0, 0($sp)
			sw $t1, 4($sp)
			jal multiplication

fin:		li $v0, 10
			syscall

# Affiche ce qu'il y a en a0
writeval:	li $v0, 1
			syscall
			jal writenl
			jr $ra

writenl:	# Affichage d'une nouvelle ligne
			li $v0, 4
			la $a0, endl
			syscall
			jr $ra

multiplication:
			sub $sp, 8
			sw $ra, 8($sp)
			lw $t0, 0($sp)
			lw $t1, 4($sp)
			
			li $v0, 1
			move $a0,$t0
			syscall
#			move $a0, $t0
#			jal writeval
#			move $a0, $t1
#			jal writeval
#			mul $t2, $t1, $t0

#	On affiche la multiplication des 2 valeurs
			li $v0, 4
			la $a0, str
			syscall
			
			move $a0, $t2
			jal writeval

			lw $ra, 8($sp)
			add $sp, 8
			jr $ra
			
