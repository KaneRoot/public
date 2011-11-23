# Interpréteur : SPIM
# spim -notrap -file programme.s
.data
str_endl:	.asciiz "\n"
str_fin:	.asciiz "Fin du programme\n"
str_nombre_cases: .asciiz "Nombre de cases du tableau à allouer : "
str_get_value: .asciiz "Entrez une valeur : "
str_give_value: .asciiz "Valeur entrée : "
taille_case: .word	4
lines:	.word	6
columns:	.word	7


.text
.globl __start

__start:
	la $a0, str_nombre_cases
	jal write_string
	jal get_int
	move $s0, $a0
	jal allocation_pile
	jal entrer_valeurs
	jal display_array
	jal desallocation_pile
	j fin						# jump inconditionnel au label 'fin'

fin:	
	la $a0, str_fin				# chargement de la chaîne str_fin
	jal write_string			# écriture de 'fin du programme'
	li $v0, 10					# appel système n. 10
	syscall						# fin du programme

# affiche une valeur, fonction de type stem
write_int_nl:	
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	jal write_nl				# écriture d'un retour à la ligne
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

# écrit un retour à la ligne, fonction de type leaf
write_nl:	
	li $v0, 4					# appel système n. 4
	la $a0, str_endl			# chargement d'une chaîne (\n)
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

write_int:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	j $ra						# retour à l'instruction appelante

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

malloc:							# procédure d'allocation dynamique
	li $v0, 9					# appel système n. 9 
	syscall						# alloue une taille a0 et
	j  $ra						# retourne le pointeur dans v0


get_int:
	li $v0, 5					# appel système n. 5
	syscall						# on lit un entier
	move $a0, $v0				# on met la réponse dans a0
	j $ra						# retour à l'instruction appelante


desallocation_pile:
	move $t0, $s0				# s0 = n
	li $t1, -4
	mul $t0, $t0, $t1
	sub $sp, $sp, $t0
	j $ra						# retour à l'instruction appelante

allocation_pile:
	move $t0, $s0				# s0 = n
	li $t1, -4
	mul $t0, $t0, $t1
	add $sp, $sp, $t0
	j $ra						# retour à l'instruction appelante

display_array:
	move $t0, $s0				# s0 = n
	li $t3, 4
display_array_loop:
	mul $t2, $t0, $t3			# t2 = nbcases * 4
	sub $t2, $t2, $t3			# t2 = t2 - 4
	move $t1, $sp
	add $t1, $t1, $t2
	la $a0, str_give_value
	li $v0, 4
	syscall
	lw $a0, ($t1)
	li $v0, 1
	syscall
	la $a0, str_endl
	li $v0, 4
	syscall
	sub $t0, $t0, 1
	bgtz $t0, display_array_loop
	j $ra						# retour à l'instruction appelante

entrer_valeurs:
	move $t0, $s0
	move $s1, $ra
	li $t3, 4
entrer_valeurs_loop:
	mul $t2, $t0, $t3			# t2 = nbcases * 4
	sub $t2, $t2, $t3			# t2 = t2 - 4
	move $t1, $sp
	add $t1, $t1, $t2
	la $a0, str_get_value
	li $v0, 4
	syscall
	li $v0, 5
	syscall
	sw $v0, ($t1)
	sub $t0, $t0, 1
	bgtz $t0, entrer_valeurs_loop

	move $ra, $s1
	j $ra

# t6 = min
# t4 = t[i] ; t5 = t[j]
tri:
	move $s1, $ra
	li $t0, 0					# t0 = i, t1 = j
	li $t3, 4
tri_loop_i:
	mul $t4, $t0, $t3			# t4 = i * 4
	add $t4, $t4, $s0
	lw $t6, ($t4)
	add $t1, $t0, 1
tri_loop_j:
	mul $t5, $t1, $t3			# 
	add $t5, $t5, $s0
	lw $t7, ($t5)
	add $t1, $t1, 1
	bgt $t6, $t7, tri_min
tri_retour:
	bgt $s0, $t1, tri_loop_j
tri_loop_j_end:
tri_echange:
	
tri_echange_end:
	add $t0, $t0, 1
	bgt $s0, $t0, tri_loop_i
tri_loop_i_end:
	move $ra, $s1
	j $ra
