---- Billets réservés
CREATE or REPLACE function nb_billets_reserve(	idVol_p VOL.idVol%TYPE,  
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
CREATE or REPLACE function nb_billets_achetes(	idVol_p VOL.idVol%TYPE,  
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

create or replace function nb_billets_restants(	idVol_p VOL.idVol%TYPE,
												idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN INTEGER
	IS
		nb_billets_restants_v INTEGER;
	
	BEGIN
		SELECT count(*) into nb_billets_restants_v
			FROM BILLET
			WHERE idVol = idVol_p and idCompagnie = idCompagnie_p and ( etatBillet not in ('A','R') or etatBillet is null);
		return nb_billets_restants_v;
END ;
/
SHOW ERRORS FUNCTION nb_billets_restants;

-- tests
--select nb_billets_reserve(1,1) from dual;
--select nb_billets_achetes(1,1) from dual;
--select nb_billets_restants(1,1) from dual;
