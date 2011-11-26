# Interpréteur : SPIM
# spim -notrap -file programme.s
# 
#
# convention : 
#	$s0 = pointeur vers le tableau représentant le plateau de jeu
#	$s1 = Numéro du joueur courant, 1 ou 2
#	$s2 = Numéro du gagnant
#	$s4 = nb lignes
#	$s5 = nb colonnes
#	$s6 = taille d'une case
#	$s7 = taille offset = nb octets séparants la même ligne de 2 colonnes

.data
str_choix_pvp_pvai:	.asciiz "Vous avez le choix : \n1) P VS P\n2) P VS AI\n3) Je veux sortir d'ici !!!\n"
str_init_array_loop: .asciiz "Loop init_array\n"
str_display_array_loop: .asciiz "Loop display_array\n"
str_display_array: .asciiz "Display Array !!! \n"
str_columns: .asciiz "\033[43m\033[31m1   2   3   4   5   6   7  \033[00m\n"
str_pvp:	.asciiz "\033[32mVous avez choisi le PVP, GOOD LUCK\033[00m\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_test:	.asciiz "Test d'écriture dans le tas\n"
str_wrong_choice: .asciiz "Mauvais choix, on recommence ! \n"
str_space_bar:	.asciiz " | "
str_endl:	.asciiz "\n"
str_fin:	.asciiz "Fin du programme\n"
str_demande_choix_1: .asciiz "Au joueur "
str_demande_choix_2: .asciiz " de jouer : "
str_win_0:	.asciiz "Le vainqueur est :\033[31m "
str_win_1:	.asciiz	" \033[00m"
player_1:	.word	1
player_2:	.word	2
taille_case: .word	4
lines:	.word	6
columns:	.word	7


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
	jal init_game				# création du tableau + initialisation variables
choix_pvp_loop:
	jal display_array			# affichage du tableau
	jal ask_player_choice
	jal add_val_array
	jal test_patterns
	jal changement_joueur
	beqz $s2, choix_pvp_loop
	jal print_win
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
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	la $a0, str_space_bar		# chargement de l'@ de str_space_bar
	jal write_string			# écriture de la chaîne
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

write_int:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
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

init_game:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $a0, 168					# taille du tableau : 6*7*4 octets
	jal malloc					# appel à la fonction d'allocation mémoire
	move $s0, $v0				# on sauvegarde le pointeur dans s0
	jal init_array				# on initialise toutes les cases à 0
	lw $s1, player_1			# on initialise $s1 à l'identifiant du premier joueur
	li $s2, 0					# s2 = 0 c'est le joueur qui a gagné
	lw $s4, lines				# s4 : nb de lignes
	lw $s5, columns				# s5 : nb de colonnes
	lw $s6, taille_case			# s6 : taille d'une case
	jal calcul_taille_offset	# calcul
	move $s7, $a0				# s7 : offset séparant même ligne de 2 col
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
	bgez $t2, display_array_loop# tant que t2 >= 0 : loop
	la $a0, str_columns
	jal write_string
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

display_choice_question:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	la $a0, str_demande_choix_1 # affichage du début de la question
	jal write_string			# faire l'affichage
	move $a0, $s1				# affichage du numéro de joueur
	jal write_int				# faire l'affichage
	la $a0, str_demande_choix_2 # affichage de la fin de la question
	jal write_string			# faire l'affichage
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

ask_player_choice:				# retourne le choix en a0
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	jal display_choice_question # affichage de la question
	jal get_int					# on récupère le choix
	move $a0, $v0				# on place le choix dans a0
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

add_val_array:					# a0 = choix colonne
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
add_val_array_loop_choice_0:
	bge $0, $a0, add_val_array_loop_choice_1 # si a0 <= 0
	bgt $a0, $s5, add_val_array_loop_choice_1# si a0 > nb de colonnes
	j add_val_array_loop_choice_end
add_val_array_loop_choice_1:
	jal ask_player_choice		# on redemande la colonne
	j add_val_array_loop_choice_0
add_val_array_loop_choice_end:	# La valeur est bonne, on l'ajoute
	li $t3, 0					# t3 = ligne courante
	move $t0, $s0				# chargement du pointeur de tableau dans t0
	sub $a0, 1					# on décrémente le numéro de colonne donné
	mul $t1, $s4, $a0			# t1 = incrément à ajouter au pointeur du tableau
	mul $t1, $s6, $t1			# t1 * taille d'une case
	addu $t0, $t0, $t1			# t0 += t1
add_val_array_loop_0:
	lw $t2, ($t0)				# t2 = valeur de la case courante
	beqz $t2, add_val_array_loop_end
	add $t3, 1
	add $t0, $t0, $s6
	bgt $s4, $t3, add_val_array_loop_0
	j add_val_array_loop_choice_1
add_val_array_loop_end:			# ajout de la valeur s1 à l'emplacement t0
	sw $s1, ($t0)
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

changement_joueur:
	lw $t0, player_1			# on charge l'identifiant du joueur 1
	lw $t1, player_2			# on charge l'identifiant du joueur 2
	beq $s1, $t0, changement_joueur_1	# si s1 est le joueur 1
	move $s1, $t0				# on place le joueur 1 dans s1
	j changement_joueur_end		# puis on sort de la fonction
changement_joueur_1:
	move $s1, $t1				# on place le joueur 2 dans s1
changement_joueur_end:
	j $ra

print_win:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	la $a0, str_win_0
	jal write_string
	move $a0, $s2
	jal write_int_nl
	la $a0, str_win_1
	jal write_string
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

# calcul la valeur à ajouter pour passer à la case de droite
calcul_taille_offset:			
	mul $a0, $s4, $s6			# lignes * taillecase = ajout pour passer à la colonne suivante, même ligne
	j $ra						# retour à l'instruction appelante

# t0 : pointeur case courante
# t1 : ligne à laquelle on arrête de chercher
# t2 : colonne à laquelle on arrête de chercher
# t4 : ligne courante
# t5 : colonne courante
# t6 : nb suite (1 à 4)
# t9 : offset passer à la colonne suivante, ligne courante + 1
pattern_detector_inc:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t1, 3
	sub $t1, $s4, $t1			# t1 = nblignes - 3 = ligne arrêt recherche
	li $t2, 3
	sub $t2, $s5, $t2			# t2 = nbcolonnes - 3 = colonne arrêt recherche
	li $t0, 0					# t0 : pointeur case courante
	li $t4, 0					# t4 : ligne courante
	li $t5, 0					# t5 : colonne courante
	li $t6, 0					# nb suite (1 à 4)
pattern_detector_inc_loop_ligne:
	mul $t9, $t4, $s6			# t9 = n°ligne * taillecase
	add $t0, $s0, $t9			# t0 = s0 + t9
	li $t5, 0
pattern_detector_inc_loop_col:
	li $t6, 0
pattern_detector_inc_test:
	lw $t3, ($t0)				# on charge ce qu'il y a à t0 dans t3
	bne $t3, $s1, pattern_detector_inc_test_end	# t3 != joueur courant, on sort
	add $t6, $t6, 1				# t6++
	li $t9, 4
	beq $t6, $t9, pattern_detector_inc_win	# t6 == 4 : win
	add $t0, $t0, $s6			# décallage en haut
	add $t0, $t0, $s7			# décallage à droite
	b pattern_detector_inc_test	# On recommence
pattern_detector_inc_test_end:
	add $t5, $t5, 1				# incrémentation colonne courante
	add $t0, $t0, $s7			# colonne de droite, même ligne
	bgt $t2, $t5, pattern_detector_inc_loop_col	# tant que t2 > t5
pattern_detector_inc_loop_col_end:
	li $t5, 0					# t5 : colonne courante
	add $t4, $t4, 1				# incrémentation ligne courante
	bgt $t1, $t4, pattern_detector_inc_loop_ligne # tant que t1 > t4
pattern_detector_inc_loop_ligne_end:
	b pattern_detector_inc_end	# saut à la fin du programme
pattern_detector_inc_win:
	move $s2, $s1
pattern_detector_inc_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

# t0 : pointeur case courante
# t1 : ligne à laquelle on arrête de chercher
# t2 : colonne à laquelle on arrête de chercher
# t4 : ligne courante
# t5 : colonne courante
# t6 : nb suite (1 à 4)
# t9 : offset passer à la colonne suivante, ligne courante + 1
pattern_detector_dec:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t1, 3					# t1 = 3 : ligne arrêt recherche
	li $t2, 3
	sub $t2, $s5, $t2			# t2 = nbcolonnes - 3 = colonne arrêt recherche
	move $t4, $s4				# t4 = s4 : ligne courante, début par la fin
	li $t5, 0					# t5 : colonne courante
	li $t6, 0					# nb suite (1 à 4)
pattern_detector_dec_loop_ligne:
	mul $t9, $t4, $s6			# t9 = n°ligne * taillecase
	sub $t9, $t9, $s6
	add $t0, $s0, $t9			# t0 = s0 + t9
	li $t5, 0
pattern_detector_dec_loop_col:
	li $t6, 0
pattern_detector_dec_test:
	lw $t3, ($t0)				# on charge ce qu'il y a à t0 dans t3
	bne $t3, $s1, pattern_detector_dec_test_end	# t3 != joueur courant, on sort
	add $t6, $t6, 1				# t6++
	li $t9, 4
	beq $t6, $t9, pattern_detector_dec_win	# t6 == 4 : win
	sub $t0, $t0, $s6			# décallage en bas
	add $t0, $t0, $s7			# décallage à droite
	b pattern_detector_dec_test	# On recommence
pattern_detector_dec_test_end:
	add $t5, $t5, 1				# incrémentation colonne courante
	add $t0, $t0, $s7			# colonne de droite, même ligne
	bgt $t2, $t5, pattern_detector_dec_loop_col	# tant que t2 > t5
pattern_detector_dec_loop_col_end:
	li $t5, 0					# t5 : colonne courante
	sub $t4, $t4, 1				# décrémentation ligne courante
	bgt $t4, $t1, pattern_detector_dec_loop_ligne # tant que t4 > t1
pattern_detector_dec_loop_ligne_end:
	b pattern_detector_dec_end	# saut à la fin du programme
pattern_detector_dec_win:
	move $s2, $s1				# joueur courant a gagné
pattern_detector_dec_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

pattern_detector_line:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	sub $t2, $s5, 3				# on s'arrête 3 colonnes avant la dernière
	li $t4, 0					# t4 = ligne courante
	move $t0, $s0				# t0 = s0
pattern_detector_line_ligne:
	li $t5, 0					# t5 = colonne courante
pattern_detector_line_colonne:
	li $t6, 0
	move $t8, $t0				# on sauvegarde t0 dans t8
pattern_detector_line_test:
	lw $t3, ($t0)				# on charge ce qu'il y a à t0 dans t3
	bne $t3, $s1, pattern_detector_line_test_end	# t3 != joueur courant, on sort
	add $t6, $t6, 1				# t6++
	li $t9, 4
	beq $t6, $t9, pattern_detector_line_win	# t6 == 4 : win
	add $t0, $t0, $s7			# décallage à droite
	b pattern_detector_line_test# On recommence
pattern_detector_line_test_end:
	move $t0, $t8				# on replace t8 dans t0
	add $t5, $t5, 1				# t5++
	add $t0, $t0, $s7			# t0 += offset 
	bgt $t2, $t5, pattern_detector_line_colonne
pattern_detector_line_colonne_end:
	add $t4, $t4, 1				# t4++
	mul $t1, $t4, $s6
	add $t0, $s0, $t1
	bgt $s4, $t4, pattern_detector_line_ligne
pattern_detector_line_ligne_end:
	b pattern_detector_line_end
pattern_detector_line_win:
	move $s2, $s1				# s1 victorieux
pattern_detector_line_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

test_patterns:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	jal pattern_detector_line	# test ligne
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
	jal pattern_detector_inc	# test diagonale croissante
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
	jal pattern_detector_dec	# test diagonale décroissante
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
test_patterns_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

