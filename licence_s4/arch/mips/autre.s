# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	str_test:	.asciiz "Test d'écriture dans le tas\n"
	str:	.asciiz	"Leur multiplication : "
	endl:	.asciiz "\n"
	fini:	.asciiz "On a fini\n"

.text
.globl __start

__start:	
	# Début du programme
	# Affichage d'une chaîne
	la $a0, str_test
	jal write_string

	li $a0, 168
	jal malloc
	move $t0, $v0
	li $t1, 10
	sw $t1, 0($t0)
	li $t1, 15
	sw $t1, 4($t0)

	la $a0, str_test
	jal write_string
	lw $a0, ($t0)
	jal writeval
	add $t0, $t0, 4
	lw $a0, ($t0)
	jal writeval

	li $v0, 5
	syscall

	j fin

fin:		
	# fin du programme
	li $v0, 10 # appel système 10
	syscall 

# affiche une valeur, fonction de type stem
writeval:	
	li $v0, 1
	syscall
	move $s4, $ra
	jal writenl
	move $ra, $s4
	jr $ra
# écrit un retour à la ligne, fonction de type leaf
writenl:	
	li $v0, 4
	la $a0, endl
	syscall
	jr $ra

write_string:		
	li $v0, 4
	syscall
	jr $ra

malloc:			# procédure d'allocation dynamique
	li $v0, 9	# appel système n. 9 
	syscall     # alloue une taille a0 et
	j  $ra      # retourne le pointeur dans v0
write_p4line:	# affichage d'une ligne du puissance4
				# prend en paramètre a0 : numéro de ligne
