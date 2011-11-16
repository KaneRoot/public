# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
str_choix_pvp_pvai:	.asciiz "Vous avez le choix : \n1) P VS P\n2) P VS AI\n3) Je veux sortir d'ici !!!\n"
str_init_array_loop: .asciiz "Loop init_array\n"
str_display_array_loop: .asciiz "Loop display_array\n"
str_display_array: .asciiz "Display Array !!! \n"
str_pvp:	.asciiz "Vous avez choisi le PVP, GOOD LUCK\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_test:	.asciiz "Test d'écriture dans le tas\n"
str_wrong_choice: .asciiz "Mauvais choix, on recommence ! \n"
str_space_bar:	.asciiz " | "
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
	beq $a0, 1, choix_pvp		# si a0 est à 0 => choix pvp
	beq $a0, 2, choix_pvai		# si a0 est à 1 => choix pvai
	beq $a0, 3, fin				# si a0 est à 2 => on quitte le programme
	# On s'est trompé de choix
	la $a0, str_wrong_choice	# chargement de la chaîne "mauvais choix"
	jal write_string			# écriture de la chaîne
	j wrong_choice				# retour en arrière

choix_pvp:	
	la $a0, str_pvp				# chaîne "choix pvp"
	jal write_string			# écriture de la chaîne
	jal create_array			# création du tableau
	jal display_array			# affichage du tableau

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

write_int_space:	
	sub $sp, $sp, 4
	sw $ra, ($sp)
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	la $a0, str_space_bar		# chargement de l'@ de str_space_bar
	jal write_string			# écriture de la chaîne
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

write_space_bar:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	la $a0, str_space_bar
	jal write_string
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

malloc:							# procédure d'allocation dynamique
	li $v0, 9					# appel système n. 9 
	syscall						# alloue une taille a0 et
	j  $ra						# retourne le pointeur dans v0

create_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $a0, 168					# taille du tableau : 6*7*4 octets
	jal malloc					# appel à la fonction d'allocation mémoire
	move $s0, $v0				# on sauvegarde le pointeur dans s0
	jal init_array				# on initialise toutes les cases à 0
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

get_int:
	li $v0, 5					# appel système n. 5
	syscall						# on lit un entier
	move $a0, $v0				# on met la réponse dans a0
	j $ra						# retour à l'instruction appelante

init_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t0, 42					# t0 = nombre de cases du tableau
init_array_loop:
	sub $t0, $t0, 1				# t0 = t0 - 1
	mul	$t1, $t0, 4				# t0 * 4 = @ relatif de la case
	add $t2, $t1, $s0			# @ de la case : t1 + @ 1ère case
	sw $0, ($t2)				# on écrit 0 dans la case
	bgt $t0, $0, init_array_loop# tant que t0 != 0 on continue la boucle
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

display_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t3, 24					# 24 = nb octets pour changement de colonne
	li $t4, 164					# 164 = offset max tableau
	move $t0, $s0				# on met s0 dans t0
	li $t2, 20					# t2 = offset
	add $t0, $t0, $t2			# t0 = t0 + offset (dernière ligne)
display_array_loop:
	lw $a0, ($t0)				# chargement de la valeur à l'@ t0
	jal write_int_space			# écriture de la valeur de a0
	add $t0, $t0, $t3			# ajout de la taille d'un offset à t0
	sub $t1, $t0, $s0			# t1 = t0 - s0
	bge $t4, $t1, display_array_loop	# ((t0-s0) < offsetmax) ? loop
	jal write_nl				# écriture d'un retour à la ligne
	sub $t2, $t2, 4				# offset de ligne décrémenté de 4 octets (1L)
	add $t0, $s0, $t2			# t0 = pointeur de tableau + offset
	bge $t2, $0, display_array_loop	# tant que t2 >= 0 : loop
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante
