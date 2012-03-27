-- Billets réservés
CREATE or REPLACE function nb_billet_reserve(	IN idVol_p VOL.idVol%TYPE,  
												IN idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN INTEGER
	IS
		nb_billet_reserve_v INTEGER;

	BEGIN 
		SELECT count(*) INTO nb_billet_reserve_v
			FROM BILLET 
			WHERE idVol = idVol_p AND idCompagnie = idCompagnie_p AND etatBillet = 'R';
		RETURN nb_billet_reserve_v;
END ;

-- Billets achetés
CREATE or REPLACE function nb_billet_achetes(	IN idVol_p VOL.idVol%TYPE,  
												IN idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN INTEGER
	IS
		nb_billet_achete_v INTEGER;

	BEGIN 
		SELECT count(*) INTO nb_billet_achete_v
			FROM BILLET 
			WHERE idVol = idVol_p AND idCompagnie = idCompagnie_p AND etatBillet = 'A';
		RETURN nb_billet_achete_v;
END ;
