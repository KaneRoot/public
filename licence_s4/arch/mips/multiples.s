# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	saisira:	.asciiz	"Entrez la valeur de a : "
	saisirb:	.asciiz	"Entrez la valeur de b : "
	str:	.asciiz	"Leur multiplication : "
	endl:	.asciiz "\n"
	fini:	.asciiz "On a fini\n"

.text
.globl __start

__start:	# Début du programme
			# Affichage d'une chaîne
			la $a0, saisira
			jal write_string

# On prend une valeur qu'on va afficher
			li $v0, 5
			syscall
			move $s0, $v0
			move $a0, $s0
			jal writeval

# On réaffiche qu'on veut une valeur
			la $a0, saisirb
			jal write_string
# On prend une autre valeur
			li $v0, 5
			syscall
			move $s1, $v0
			move $a0, $s1
			jal writeval

			la $a0, saisira
			jal write_string

			move $a0, $s0
			jal writeval

			la $a0, fini
			jal write_string


# Charge les paramètres dans la pile
			sub $sp, 8
# On écrit les valeurs
			sw $s0, 0($sp)
			sw $s1, 4($sp)
			jal multiplication

fin:		li $v0, 10
			syscall

# affiche une valeur, fonction de type stem
writeval:	li $v0, 1
			syscall
			move $s0, $ra
			jal writenl
			move $ra, $s0
			jr $ra
# écrit un retour à la ligne, fonction de type leaf
writenl:	li $v0, 4
			la $a0, endl
			syscall
			jr $ra

write_string:		
			li $v0, 4
			syscall
			jr $ra

multiplication:
			subu $sp, 8
			sw $ra, 8($sp)
			lw $s4, 0($sp)
			lw $s5, 4($sp)
			
			move $a0, $s4
			jal writeval

			move $a0, $s5
			jal writeval

			mul $s6, $s5, $s4

#	On affiche la multiplication des 2 valeurs
			la $a0, str
			jal write_string
			
			move $s0, $ra
			move $a0, $s6
			jal writeval
			move $ra, $s0

			lw $ra, 8($sp)
			add $sp, 8
			jr $ra
			
