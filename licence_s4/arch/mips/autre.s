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
			move $t0, $s0
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

			move $a0, $s0
			jal writeval

			la $a0, fini
			jal write_string

			j fin

fin:		li $v0, 10
			syscall

# affiche une valeur, fonction de type stem
writeval:	li $v0, 1
			syscall
			move $s4, $ra
			jal writenl
			move $ra, $s4
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
