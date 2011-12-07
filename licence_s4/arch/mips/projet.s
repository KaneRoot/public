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

####################### Choix
str_choix_pvp_pvai:	.asciiz "
	\033[31mVous avez le choix\033[00m :
	1) P VS P
	2) P VS AI
	3) Je veux sortir d'ici !!!
	4) Changer les paramètres (nombre de lignes et de colonnes)\n"
str_pvp:	.asciiz "\033[32mVous avez choisi le PVP, GOOD LUCK\033[00m\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_nb_lignes: .asciiz "Le nombre de lignes ( 99 > x >= 5) : "
str_nb_colonnes: .asciiz "Le nombre de colonnes ( 99 > x >= 5) : "
str_wrong_choice: .asciiz "\033[43m\033[31mMauvais choix, on recommence !\033[00m\n"
####################### Affichage des cases
str_space_bar:	.asciiz " | "
str_player_1:	.asciiz "\033[31m\033[44m x \033[00m"
str_player_2:	.asciiz "\033[31m\033[42m O \033[00m"
str_no_player:	.asciiz "___"
####################### Tests
str_column_full: .asciiz "COLUMN FULL\n"
str_column_not_full: .asciiz "NOT FULL\n"
str_p_d_line: .asciiz "\033[33mFin pattern detector line\033[00m\n"
str_p_d_column: .asciiz "\033[33mFin pattern detector column\033[00m\n"
str_p_d_inc: .asciiz "\033[33mFin pattern detector inc\033[00m\n"
str_p_d_dec: .asciiz "\033[33mFin pattern detector dec\033[00m\n"
####################### Divers
str_columns_0: .asciiz "\033[43m\033[31m "
str_columns_1: .asciiz "     "
str_columns_2: .asciiz "   \033[00m\n"
str_endl:	.asciiz "\n"
str_demande_choix_1: .asciiz "Au joueur "
str_demande_choix_2: .asciiz " de jouer : "
str_win_0:	.asciiz "\n\033[32mLe vainqueur est :\033[31m "
str_win_1:	.asciiz	"\033[00m"
str_fin:	.asciiz "Fin du programme\n"
####################### Paramètres
player_1:	.word	1
player_2:	.word	2
taille_case: .word	4
lines:	.word	6
columns:	.word	7
#######################

.text
.globl __start

__start:
	jal init_valeurs
menu_choix: # On affiche le choix qui peu être fait
	la $a0, str_choix_pvp_pvai	# charge l'adressse de la question
	jal write_string			# écriture de la chaîne
	jal get_int					# on lit un entier, retour sur a0
	beq $a0, 1, choix_pvp		# si a0 est à 1 => choix pvp
	beq $a0, 2, choix_pvai		# si a0 est à 2 => choix pvai
	beq $a0, 3, fin				# si a0 est à 3 => on quitte le programme
	beq $a0, 4, changer_param	# si a0 est à 4 => changement du nb lignes et col
	# On s'est trompé de choix
	la $a0, str_wrong_choice	# chargement de la chaîne "mauvais choix"
	jal write_string			# écriture de la chaîne
	j menu_choix				# retour en arrière

choix_pvp:	
	la $a0, str_pvp				# chaîne "choix pvp"
	jal write_string			# écriture de la chaîne
	jal init_game				# création du tableau + initialisation variables
choix_pvp_loop:
	jal display_array			# affichage du tableau
	jal ask_player_choice		# demande un numéro de colonne
	jal add_val_array			# ajout du jeton dans la colonne
	jal test_patterns			# est-ce que quelqu'un a gagné ?
	jal changement_joueur		# on change le numéro de joueur
	beqz $s2, choix_pvp_loop	# si un joueur a gagné, son numéro est dans s2
	jal print_win				# affichage du gagnant
	jal display_array			# affichage du tableau
	j fin						# jump au label 'fin'

choix_pvai:	
	la $a0, str_pvai			# chaîne "choix pvai"
	jal write_string			# écriture de la chaîne
	jal init_game				# création du tableau + initialisation variables
	jal changement_joueur		# c'est le bot qui commence les hostilités
choix_pvai_loop:
	li $t0, 2					# pour le test qui suit
	beq $t0, $s1, choix_pvai_ai	# si c'est au bot de jouer
	jal display_array			# affichage du tableau
	jal ask_player_choice		# demande de choix
	b choix_pvai_end			# sauter le choix de l'ai
choix_pvai_ai:
	jal ai_play					# choix de l'AI (renvoie dans a0)
choix_pvai_end:
	jal add_val_array			# a0 en param = colonne
#	jal test_patterns			# est-ce que quelqu'un a gagné ?
	jal test_full_array			# TODO
	move $s2, $a0
	jal changement_joueur		# changement du joueur courant
	beqz $s2, choix_pvai_loop	# fin de la partie si s2 est rempli (joueur gagnant)
	jal print_win				# affichage de qui a gagné
	jal display_array			# affichage du tableau
	j fin						# jump au label 'fin'

#
#	changer_param
#	change les valeurs par défaut (ligne et colonne)
#

changer_param:
	la $a0, str_nb_lignes		# @ de demande du choix du nb de lignes dans a0
	la $a1, str_wrong_choice
	li $a2, 5					# valeur minimale du nombre de lignes
	li $a3, 99					# valeur maximale du nombre de lignes
	jal get_int_intervale		# demande du nb de lignes
	move $s4, $a0
	la $a0, str_nb_colonnes		# @ de demande du choix du nb de colonnes dans a0
	la $a1, str_wrong_choice
	li $a2, 5					# valeur minimale du nombre de colonnes
	li $a3, 99					# valeur maximale du nombre de colonnes
	jal get_int_intervale		# demande du nb de colonnes
	move $s5, $a0
	jal calcul_taille_offset	# calcul
	move $s7, $a0				# s7 : offset séparant même ligne de 2 col
	j menu_choix				# retour au menu


#
#	get_int_intervale
#		paramètres : 
#	a0 : @ chaîne à afficher
#	a1 : @ chaîne d'erreur à afficher si on se trompe
#	a2 : valeur minimum acceptée
#	a3 : valeur maximale acceptée
#

get_int_intervale:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	move $t0, $a0
	b get_int_intervale_loop
get_int_intervale_err:
	move $a0, $a1
	jal write_string
get_int_intervale_loop:
	move $a0, $t0
	jal write_string
	jal get_int
	blt $a0, $a2, get_int_intervale_err
	bgt $a0, $a3, get_int_intervale_err
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra

#
#	init_valeurs
#	charge les valeurs par défaut dans les s* (cf convention)
#	

init_valeurs:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
# initialisation des variables globales
	lw $s1, player_1			# on initialise $s1 à l'identifiant du premier joueur
	li $s2, 0					# s2 = 0 c'est le joueur qui a gagné
	lw $s4, lines				# s4 : nb de lignes
	lw $s5, columns				# s5 : nb de colonnes
	lw $s6, taille_case			# s6 : taille d'une case
	jal calcul_taille_offset	# calcul
	move $s7, $a0				# s7 : offset séparant même ligne de 2 col
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra

# 
#	write_int_nl
#	affiche un entier a0 puis un retour à la ligne
#

write_int_nl:	
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	jal write_nl				# écriture d'un retour à la ligne
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	write_case
#	écrit une case du tableau (vide, joueur 1 ou 2)
#	on lui passe la valeur de la case en a0
#

write_case:	
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	lw $t8, player_1			# on charge l'identifiant du joueur 1 (1)
	lw $t9, player_2			# on charge l'identifiant du joueur 2 (2)
	beq $a0, $t8, write_case_then
	beq $a0, $t9, write_case_else
	b write_case_default		# sinon : case vide (___)
write_case_then:
	la $a0, str_player_1		# on charge la chaîne
	b write_case_fi				# go fin
write_case_else:
	la $a0, str_player_2		# on charge la chaîne
	b write_case_fi				# go fin
write_case_default:
	la $a0, str_no_player		# case vide (___)
write_case_fi:
	jal write_string			# écriture de la chaîne
	la $a0, str_space_bar		# chargement de l'@ de str_space_bar
	jal write_string			# écriture de la chaîne
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante


#
#	write_space_bar
#	écrit une barre + des espaces (pour un bel affichage)
#

write_space_bar:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	la $a0, str_space_bar
	jal write_string
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	init_game
#	initialise le plateau, demande l'allocation mémoire
#	puis son initialisation à 0 pour toutes ses cases
#

init_game:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
# initialisation du tableau
	mul $a0, $s4, $s5			# taille du tableau : 6*7*4 octets (partie normale)
	mul $a0, $a0, $s6
	jal malloc					# appel à la fonction d'allocation mémoire
	move $s0, $v0				# on sauvegarde le pointeur dans s0
	jal init_array				# on initialise toutes les cases à 0
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	init_array
#	initialise toutes les cases du tableau à 0
#	

init_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	mul $t0, $s4, $s5			# t0 = nombre de cases du tableau
init_array_loop:
	sub $t0, $t0, 1				# t0 = t0 - 1
	mul	$t1, $t0, $s6			# t0 * nb octets / case = @ relatif de la case
	add $t2, $t1, $s0			# @ de la case : t1 + @ 1ère case
	sw $0, ($t2)				# on écrit 0 dans la case
	bgt $t0, $0, init_array_loop# tant que t0 < 0 on continue la boucle
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	display_array
#	affiche un tableau ayant s4 lignes s5 colonnes et une taille de case de s6
#	

display_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	mul $t4, $s4, $s5			# t4 = nblignes * nbcolonnes
	mul $t4, $t4, $s6			# t4 = t4 * taillecase
	sub $t4, $t4, $s6			# t4 -= taillecase
	move $t0, $s0				# on met s0 dans t0
	mul $t2, $s4, $s6			# t2 = offset : nblignes * nb octets / case
	sub $t2, $t2, $s6			# t2 - taille d'une case
	add $t0, $t0, $t2			# t0 = t0 + offset (dernière ligne)
display_array_loop:
	lw $a0, ($t0)				# chargement de la valeur à l'@ t0
	jal write_case				# écriture de la valeur de a0
	add $t0, $t0, $s7			# ajout de la taille d'un offset à t0
	sub $t1, $t0, $s0			# t1 = t0 - s0
	bge $t4, $t1, display_array_loop	# ((t0-s0) < offsetmax) ? loop
	jal write_nl				# écriture d'un retour à la ligne
	sub $t2, $t2, $s6			# offset de ligne décrémenté de s6 octets (1L)
	add $t0, $s0, $t2			# t0 = pointeur de tableau + offset
	bgez $t2, display_array_loop# tant que t2 >= 0 : loop
	jal write_column_numbers	# écrit une ligne avec le numéro des colonnes
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

#
#	pattern_detector_inc
#	permet de détecter une suite de 4 * n. s1 en diagonale croissante
#

# t0 : pointeur case courante
# t1 : ligne à laquelle on arrête de chercher
# t2 : colonne à laquelle on arrête de chercher
# t4 : ligne courante
# t5 : colonne courante
# t6 : nb suite (1 à 4)
# t9 : offset pour passer à la colonne suivante avec ligne courante + 1

pattern_detector_inc:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t1, 3
	sub $t1, $s4, $t1			# t1 = nblignes - 3 = ligne arrêt recherche
	li $t2, 3
	sub $t2, $s5, $t2			# t2 = nbcolonnes - 3 = colonne arrêt recherche
	li $t4, 0					# t4 : ligne courante
	li $t6, 0					# nb suite (1 à 4)
	move $t0, $s0
pattern_detector_inc_loop_ligne:
	li $t5, 0					# t5 = ligne courante
pattern_detector_inc_loop_col:
	li $t6, 0					# t6 : nb suite (si == 4 : gagné)
	move $t8, $t0
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
	move $t0, $t8
	add $t5, $t5, 1				# incrémentation colonne courante
	add $t0, $t0, $s7			# colonne de droite, même ligne
	bgt $t2, $t5, pattern_detector_inc_loop_col	# tant que t2 > t5
pattern_detector_inc_loop_col_end:
	li $t5, 0					# t5 : colonne courante
	add $t4, $t4, 1				# incrémentation ligne courante
	mul $t9, $t4, $s6			# t9 = n°ligne * taillecase
	add $t0, $s0, $t9			# t0 = s0 + t9
	bgt $t1, $t4, pattern_detector_inc_loop_ligne # tant que t1 > t4
pattern_detector_inc_loop_ligne_end:
	b pattern_detector_inc_end	# saut à la fin du programme
pattern_detector_inc_win:
	move $s2, $s1
pattern_detector_inc_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante


#
#	pattern_detector_dec
#	détecte si on a une diagonale décroissante comportant 4 * n. s1 continus
#	

# t0 : pointeur case courante
# t1 : ligne à laquelle on arrête de chercher
# t2 : colonne à laquelle on arrête de chercher
# t4 : ligne courante
# t5 : colonne courante
# t6 : nb suite (1 à 4)
# t9 : offset pour passer à la colonne suivante avec ligne courante + 1

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
	sub $t9, $t9, $s6			# on commence à la fin
	add $t0, $s0, $t9			# t0 = s0 + t9
	li $t5, 0					# t5 : colonne courante
pattern_detector_dec_loop_col:
	li $t6, 0
	move $t8, $t0
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
	move $t0, $t8
	add $t5, $t5, 1				# incrémentation colonne courante
	add $t0, $t0, $s7			# colonne de droite, même ligne
	bgt $t2, $t5, pattern_detector_dec_loop_col	# tant que t2 > t5
pattern_detector_dec_loop_col_end:
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

#
#	pattern_detector_column
#	détecte si on a une colonne comportant 4 * n. s1 continus
#	

pattern_detector_column:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	sub $t1, $s4, 3				# on s'arrête 3 lignes avant la dernière
	li $t4, 0					# t4 = ligne courante
	move $t0, $s0				# t0 = s0
pattern_detector_column_ligne:
	li $t5, 0					# t5 = colonne courante
pattern_detector_column_colonne:
	li $t6, 0
	move $t8, $t0				# on sauvegarde t0 dans t8
pattern_detector_column_test:
	lw $t3, ($t0)				# on charge ce qu'il y a à t0 dans t3
	bne $t3, $s1, pattern_detector_column_test_end	# t3 != joueur courant, on sort
	add $t6, $t6, 1				# t6++
	li $t9, 4
	beq $t6, $t9, pattern_detector_column_win	# t6 == 4 : win
	add $t0, $t0, $s6			# on monte
	b pattern_detector_column_test# On recommence
pattern_detector_column_test_end:
	move $t0, $t8				# on replace t8 dans t0
	add $t5, $t5, 1				# t5++
	add $t0, $t0, $s7			# t0 += offset 
	bgt $s5, $t5, pattern_detector_column_colonne
pattern_detector_column_colonne_end:
	add $t4, $t4, 1				# t4++
	mul $t2, $t4, $s6			# t2 = n°col * taillecase
	add $t0, $s0, $t2			# t0 = s0 + t2
	bgt $t1, $t4, pattern_detector_column_ligne
pattern_detector_column_ligne_end:
	b pattern_detector_column_end
pattern_detector_column_win:
	move $s2, $s1				# s1 victorieux
pattern_detector_column_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante


#
#	test_patterns
#	teste les 4 patterns (ligne, colonne, diag montante et descendante)
#	écrit une chaîne de debug (à décommenter)
#

test_patterns:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	###################
	jal pattern_detector_line	# test ligne
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
#	la $a0, str_p_d_line
#	jal write_string
	###################
	jal pattern_detector_column	# test colonne
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
#	la $a0, str_p_d_column
#	jal write_string
	###################
	jal pattern_detector_inc	# test diagonale croissante
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
#	la $a0, str_p_d_inc
#	jal write_string
	###################
	jal pattern_detector_dec	# test diagonale décroissante
	bnez $s2, test_patterns_end	# Pas besoin de faire plus de tests si gagné
#	la $a0, str_p_d_dec
#	jal write_string
	###################
test_patterns_end:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	test_full_array
#	Fait un test pour savoir si toutes les colonnes sont pleines
#	retourne 1 en a0 si le plateau est plein, 0 sinon
#

test_full_array:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t0, 0					# t0 : numéro de colonne à tester
	sub $sp, $sp, 4				# on stocke la valeur dans la pile
	sw $0, ($sp)				# on écrit le numéro de la colonne à tester dans la pile
	lw $t0, ($sp)
test_full_array_loop:
	move $a0, $t0				# on place le n. de col. dans a0 pr le passer en param.
	jal test_full_column		# teste la colonne
	beq $a1, 0, test_full_array_not_full	# retour a1 = 0 : colonne non remplie
	lw $t0, ($sp)				# on charge le n. de colonne dans t0
	add $t0, $t0, 1				# on incrémente le n. de colonne
	sw $t0, ($sp)				# on le réécrit dans la pile
	blt $t0, $s5, test_full_array_loop	# tq n. colonne < nb colonnes
	li $a0, 1					# retour a0 = 1 : plein
	b test_full_array_end
test_full_array_not_full:
	li $a0, 0					# retour a0 = 0 : pas plein
test_full_array_end:
	lw $ra, 4($sp)				# charge ra depuis la pile
	addu $sp, $sp, 8			# désalloue 8 octets de la pile
	j $ra						# retour à l'instruction appelante


#
#	ai_play
#	programme du bot, est vraiment stupide pour le moment.
#	Ne fait que remplir colonne par colonne le tableau
#

ai_play:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	sub $sp, $sp, 4				# je vais stocker un compteur dans la pile
	sw $0, ($sp)				# le compteur est à 0
ai_play_loop:
	lw $a0, ($sp)
	jal test_full_column
	beq $a1, $0, ai_play_trouve	# récupère dans a1 la valeur
	lw $t0, ($sp)				# on récupère le numéro de ligne courante
	add $t0, $t0, 1				# incrémentation du numéro de la ligne
	sw $t0, ($sp)				# on écrit l'incrément dans la pile
	bne $t0, $s5, ai_play_loop	# tq num col courant != num max
	b ai_play_fin				# fin : toutes colonnes remplies
ai_play_trouve:
	lw $a0, ($sp)				# on lit le num de col dans la pile
	add $a0, $a0, 1				# num colonne commençant à 1 non à 0
ai_play_fin:
	add $sp, $sp, 4				# on désalloue de la pile
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

#
#	test_full_column
#	teste si une colonne a0 est pleine
#	retourne a1 = 1 si remplie, 0 sinon
#

test_full_column:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	move $t0, $s0				# t0 = s0 = copie du pointeur
	mul $t1, $a0, $s7			# t1: case courante, a0: colonne voulue, s7: nbl*nboctets
	add $t0, $t1, $t0			# t0 = t0 + offset calculé (cf num de colonne)
	li $t2, 0					# t2: numéro ligne courante
test_full_column_loop:
	add $t2, $t2, 1				# incrément t2: numéro ligne courante
	lw $t3, ($t0)				# Valeur de la case dans t3
	beq $0, $t3, test_full_column_non_rempli	# case libre : colonne non pleine
	add $t0, $s6, $t0				# ajout nb octets à t0
	bne $t2, $s4, test_full_column_loop	# tant que ligne courante != nb lignes
test_full_column_loop_end:
	li $a1, 1					# colonne pleine = a1: retour fonction = 1
	b test_full_column_fin		# on sort
test_full_column_non_rempli:
	li $a1, 0					# a1: retour fonction, 0 = on peut mettre une case
test_full_column_fin:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante
	

#
#	write_column_numbers
#	écrit le numéro des colonnes de façon dynamique (en fonction de leur nombre)
#

write_column_numbers:
	sub $sp, $sp, 8				# soustrait 8 au pointeur de pile
	sw $ra, 4($sp)				# sauvegarde ra dans la pile
	la $a0, str_columns_0
	jal write_string
	sw $0, ($sp)				# première colonne commence à 1 (voir loop)
write_column_numbers_loop:
	lw $t0, ($sp)
	add $t0, $t0, 1
	sw $t0, ($sp)				# écriture du n. de col dans la pile
	move $a0, $t0
	jal write_int
	lw $t0, ($sp)
	beq $t0, $s5, write_column_numbers_loop_end	# espace plus petit à la fin
	la $a0, str_columns_1		# écriture d'un espace sur la ligne de commande
	jal write_string
	lw $t0, ($sp)
	blt $t0, $s5, write_column_numbers_loop	# tq n. col. < nb col.
write_column_numbers_loop_end:
	la $a0, str_columns_2		# on supprime les couleurs
	jal write_string
	lw $ra, 4($sp)				# charge ra depuis la pile
	addu $sp, $sp, 8			# ajoute 8 au pointeur de pile
	j $ra						# retour à l'instruction appelante


##### Fonctions de test
test_test_full_column:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $a0, 0					# test colonne 0
	jal test_full_column
	beq $a0, $0, test_test_full_column_not_full
	la $a0, str_column_full
	jal write_string
	b test_test_full_column_fin
test_test_full_column_not_full:
	la $a0, str_column_not_full
	jal write_string
test_test_full_column_fin:
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante

###	Fonctions de type LEAF

#
#	write_nl
#	écrit un retour à la ligne
#

write_nl:	
	li $v0, 4					# appel système n. 4
	la $a0, str_endl			# chargement d'une chaîne (\n)
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

#
#	write_int
#	écrit un entier passé en a0
#

write_int:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	j $ra						# retour à l'instruction appelante

#
#	write_string
#	écrit une chaîne passée en a0
#

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

#
#	get_int
#	demande un entier en ligne de commande
#

get_int:
	li $v0, 5					# appel système n. 5
	syscall						# on lit un entier
	move $a0, $v0				# on met la réponse dans a0
	j $ra						# retour à l'instruction appelante

#
#	malloc
#	se charge de l'allocation dynamique de mémoire
#

malloc:							# procédure d'allocation dynamique
	li $v0, 9					# appel système n. 9 
	syscall						# alloue une taille a0 et
	j  $ra						# retourne le pointeur dans v0

#
#	changement_joueur
#	switch entre les valeurs player_1 et 2 dans s1
#

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

#
#	calcul_taille_offset
#	calcul la valeur à ajouter pour passer à la case de droite
#	résultat dans a0
#

calcul_taille_offset:			
# lignes * taillecase = ajout pour passer à la colonne suivante, même ligne
	mul $a0, $s4, $s6			
	j $ra						# retour à l'instruction appelante

#
#	fin
#	fin de la partie, quitte le programme
#

fin:	
	la $a0, str_fin				# chargement de la chaîne str_fin
	jal write_string			# écriture de 'fin du programme'
	li $v0, 10					# appel système n. 10
	syscall						# fin du programme
