
# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
	val1:	.asciiz	"Entrez la valeur 1 : "
	val2:	.asciiz	"Entrez la valeur 2 : "
	str_space_bar:	.asciiz " | "
	res:	.asciiz "Le résultat est : "
	str_fin:	.asciiz "Fin du programme\n"
	str_endl:	.asciiz "\n"

.text
.globl __start

__start:	li $v0, 4
			la $a0, val1
			syscall
			
			jal get_int
			move $t0, $a0

label2:		li $v0, 4
			la $a0, val2
			syscall

			jal get_int
			move $t1, $a0
			jal write_int_space

afficheres:	li $v0, 4
			la $a0, res
			syscall
			add $t2, $t1,$t0
			li $v0, 1
			move $a0, $t2
			syscall
			li $v0, 4
			la $a0, str_endl
			syscall
			jal truc
fin:	
	la $a0, str_fin				# chargement de la chaîne str_fin
	jal write_string			# écriture de 'fin du programme'
	li $v0, 10					# appel système n. 10
	syscall						# fin du programme

# affiche une valeur, fonction de type stem
write_int_nl:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	move $t4, $ra				# chargement de ra dans t4 pour sauvegarde
	jal write_nl				# écriture d'un retour à la ligne
	move $ra, $t4				# replacement de l'ancienne valeur de ra
	j $ra						# retour à l'instruction appelante

# écrit un retour à la ligne, fonction de type leaf
write_nl:	
	li $v0, 4					# appel système n. 4
	la $a0, str_endl			# chargement d'une chaîne (\n)
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

write_int_space:	
	sub $sp, $sp, 4
	sw $ra, ($sp)
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	la $a0, str_space_bar		# chargement de l'@ de str_space_bar
	jal write_string			# écriture de la chaîne
	lw $ra, ($sp)
	addu $sp, $sp, 4
	j $ra						# retour à l'instruction appelante

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

write_space_bar:
	sub $sp, $sp, 4
	sw $ra, ($sp)
	la $a0, str_space_bar
	jal write_string
	lw $ra, ($sp)
	addu $sp, $sp, 4
	j $ra
truc:
	sub $sp, $sp, 4
	sw $ra, ($sp)
	jal truc2
	lw $ra, ($sp)
	add $sp, 4
	j $ra
truc2:
	sub $sp, $sp, 4
	sw $ra, ($sp)
	jal truc3
	lw $ra, ($sp)
	add $sp, 4
	j $ra

truc3:
	sub $sp, $sp, 4
	sw $ra, ($sp)
	li $a0, 15
	jal write_int_nl
	lw $ra, ($sp)
	add $sp, 4
	j $ra

get_int:
	sub $sp, $sp, 4
	sw $ra, ($sp)
	li $v0, 5					# appel système n. 5
	syscall						# on lit un entier
	move $a0, $v0				# on met la réponse dans a0
	lw $ra, ($sp)
	addu $sp, $sp, 4
	j $ra						# retour à l'instruction appelante
