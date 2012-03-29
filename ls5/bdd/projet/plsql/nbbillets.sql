---- Billets réservés
CREATE or REPLACE function nb_billet_reserve(	idVol_p VOL.idVol%TYPE,  
												idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN INTEGER
	IS
		nb_billet_reserve_v INTEGER;

	BEGIN 
		SELECT count(*) INTO nb_billet_reserve_v
			FROM BILLET 
			WHERE idVol = idVol_p AND idCompagnie = idCompagnie_p AND etatBillet = 'R';
		RETURN nb_billet_reserve_v;
END;
/
SHOW ERRORS FUNCTION nb_billet_reserve;

---- procedure 
---- Billets achetés
CREATE or REPLACE function nb_billet_achetes(	idVol_p VOL.idVol%TYPE,  
												idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN INTEGER
	IS
		nb_billet_achete_v INTEGER;

	BEGIN 
		SELECT count(*) INTO nb_billet_achete_v
			FROM BILLET 
			WHERE idVol = idVol_p AND idCompagnie = idCompagnie_p AND etatBillet = 'A';
		RETURN nb_billet_achete_v;
END ;
/
SHOW ERRORS FUNCTION nb_billet_achetes;

-- tests
select nb_billet_reserve(1,1) from dual;
select nb_billet_achetes(1,1) from dual;
