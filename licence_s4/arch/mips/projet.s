# Programme en MIPS

# Interpréteur : SPIM
# spim -notrap -file programme.s

.data
str_choix_pvp_pvai:	.asciiz "Vous avez le choix : \n0) P VS P\n1)P VS AI\n2) Je veux sortir d'ici !!!\n"
str_pvp:	.asciiz "Vous avez choisi le PVP, GOOD LUCK\n"
str_pvai:	.asciiz "Vous avez choisi le PVAI, GOOD LUCK\n"
str_wrong_choice: .asciiz "Mauvais choix, on recommence ! \n"
endl:	.asciiz "\n"
fini:	.asciiz "Fin du programme\n"

.text
.globl __start

__start:
wrong_choice: # Utile d'un point de vue sémantique
			la $a0, str_choix_pvp_pvai
			jal write_string
			li $v0, 5
			syscall
			move $t0, $v0
			beq $0, $t0, choix_pvp
			beq $t0, 1, choix_pvai
			beq $t0, 2, fin
			# On s'est trompé de choix
			la $a0, str_wrong_choice
			jal write_string
			j wrong_choice
			

choix_pvp:	la $a0, str_pvp
			jal write_string

			j fin

choix_pvai:	la $a0, str_pvai
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
