# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
str_choix_pvp_pvai:	.asciiz "Vous avez le choix : \n0) P VS P\n1)P VS AI\n2) Je veux sortir d'ici !!!\n"
str_pvp:	.asciiz "Vous avez choisi le PVP, GOOD LUCK\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_test:	.asciiz "Test d'écriture dans le tas\n"
str_wrong_choice: .asciiz "Mauvais choix, on recommence ! \n"
endl:	.asciiz "\n"
fini:	.asciiz "Fin du programme\n"

.text
.globl __start

__start:
wrong_choice: 
	# label utile d'un point de vue sémantique
	la $a0, str_choix_pvp_pvai	# demande de choix
	jal write_string			# écriture de la chaîne
	li $v0, 5
	syscall
	move $t0, $v0
	beq $0, $t0, choix_pvp
	beq $t0, 1, choix_pvai
	beq $t0, 2, fin
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
	li $v0, 10
	syscall

# affiche une valeur, fonction de type stem
writeval:	
	li $v0, 1					# appel système n. 1
	syscall						# lit un entier dans a0
	move $t4, $ra				# chargement de ra dans t4 pour sauvegarde
	jal writenl					# écriture d'un retour à la ligne
	move $ra, $t4				# replacement de l'ancienne valeur de ra
	j $ra						# retour à l'instruction appelante
# écrit un retour à la ligne, fonction de type leaf
writenl:	
	li $v0, 4					# appel système n. 4
	la $a0, endl				# chargement d'une chaîne (\n)
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

write_string:		
	li $v0, 4					# appel système n. 4
	syscall						# écriture de la chaîne
	j $ra						# retour à l'instruction appelante

malloc:							# procédure d'allocation dynamique
	li $v0, 9					# appel système n. 9 
	syscall						# alloue une taille a0 et
	j  $ra						# retourne le pointeur dans v0

init_tableau:
	li $a0, 168					# taille du tableau : 6*7*4octets
	jal malloc					# appel à la fonction d'allocation mémoire
	move $s0, $v0				# on sauvegarde le pointeur dans s0
	j $ra						# retour à l'instruction appelante

