patern_detector_line:
	sub $sp, $sp, 4				# soustrait 4 au pointeur de pile
	sw $ra, ($sp)				# sauvegarde ra dans la pile
	li $t0, $s0					# initialise le pointeur du tableau
	li $t1, 0					# initialise increment à 0
	li $t2, 0					# initialise valeur du tableau à 0
	li $t3, 0					# initialise numero ligne à 0
	li $t4, 4					# va servir pour le test increment != 4
	
patern_detector_line_loop:	
	lw $t2, ($t0)								# charge la valeur du tableau dans t2
	bne $t2, $s1, patern_detector_line_then		# test si t2 != numéro du joueur
	add $t1, $t1, 1								# t1 += 1
	bne $t1, $t4, patern_detector_line_loop		# test si increment != 4 
	move $s2, $t2								# si t1 = 4 alors on place le numéro du joueur ($t2) dans le numéro du gagnant ($s2)
	j patern_detector_line_end
patern_detector_line_then:
	add $t0, $t0, 1								# t0 += t0
	j patern_detector_line_end
	
	add $t3, $t3, 1								# t3 += 1
	bgt $s4, $t3, patern_detector_line_loop		# test si numero ligne > nb ligne
	j patern_detector_line_end
	
patern_detector_line_end:	
	lw $ra, ($sp)				# charge ra depuis la pile
	addu $sp, $sp, 4			# ajoute 4 au pointeur de pile
	j $ra						# retour à l'instruction appelante
