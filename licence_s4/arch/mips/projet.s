# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
str_choix_pvp_pvai:	.asciiz "Vous avez le choix : \n0) P VS P\n1)P VS AI\n2) Je veux sortir d'ici !!!\n"
str_pvp:	.asciiz "Vous avez choisi le PVP, GOOD LUCK\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_test:	.asciiz "Test d'écriture dans le tas\n"
str_wrong_choice: .asciiz "Mauvais choix, on recommence ! \n"
str_space:	.asciiz " | "
str_endl:	.asciiz "\n"
str_fin:	.asciiz "Fin du programme\n"

.text
.globl __start

__start:
wrong_choice: 
	# label utile d'un point de vue sémantique
	la $a0, str_choix_pvp_pvai	# demande de choix
	jal write_string			# écriture de la chaîne
	jal get_int					# on lit un entier, retour sur a0
	beq $0, $a0, choix_pvp		# si a0 est à 0 => choix pvp
	beq $a0, 1, choix_pvai		# si a0 est à 1 => choix pvai
	beq $a0, 2, fin				# si a0 est à 2 => on quitte le programme
	# On s'est trompé de choix
	la $a0, str_wrong_choice	# chargement de la chaîne "mauvais choix"
	jal write_string			# écriture de la chaîne
	j wrong_choice				# retour en arrière

choix_pvp:	
	la $a0, str_pvp				# chaîne "choix pvp"
	jal write_string			# écriture de la chaîne

	j fin						# jump au label 'fin'

choix_pvai:	
	la $a0, str_pvai			# chaîne "choix player vs ai"
	jal write_string			# écriture de la chaîne

	j fin						# jump au label 'fin'

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
	jal writenl					# écriture d'un retour à la ligne
	move $ra, $t4				# replacement de l'ancienne valeur de ra
	j $ra						# retour à l'instruction appelante
# écrit un retour à la ligne, fonction de type leaf
writenl:	
	li $v0, 4					# appel système n. 4
	la $a0, str_endl			# chargement d'une chaîne (\n)
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante
write_int_space:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	move $t4, $ra				# chargement de ra dans t4 pour sauvegarde
	jal writenl					# écriture d'un retour à la ligne
	move $ra, $t4				# replacement de l'ancienne valeur de ra
	j $ra						# retour à l'instruction appelante

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

malloc:							# procédure d'allocation dynamique
	li $v0, 9					# appel système n. 9 
	syscall						# alloue une taille a0 et
	j  $ra						# retourne le pointeur dans v0

create_array:
	li $a0, 168					# taille du tableau : 6*7*4 octets
	jal malloc					# appel à la fonction d'allocation mémoire
	move $s0, $v0				# on sauvegarde le pointeur dans s0
	move $t4, $ra				# sauvegarde de ra dans t4
	jal init_array				# on initialise toutes les cases à 0
	move $ra, $t4				# on replace la sauvegarde de ra dans ra
	j $ra						# retour à l'instruction appelante

get_int:
	li $v0, 5					# appel système n. 5
	syscall						# on lit un entier
	move $a0, $v0				# on met la réponse dans a0
	j $ra						# retour à l'instruction appelante
init_array:
	li $t0, 42					# t0 = nombre de cases du tableau
init_array_loop:
	sub $t0, $t0, 1				# t0 = t0 - 1
	mul	$t1, $t0, 4				# t0 * 4 = @ relatif de la case
	add $t2, $t1, $s0			# @ de la case : t1 + @ 1ère case
	sw $0, ($t2)					# on écrit 0 dans la case
	bne $0, $t0, init_array_loop# tant que t0 != 0 on continue la boucle
	j $ra						# retour à l'instruction appelante

display_array:

