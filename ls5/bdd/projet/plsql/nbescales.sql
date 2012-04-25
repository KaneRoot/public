-- Nombre d'escales pour un vol

create or replace function nb_escales(	idVol_p VOL.idVol%TYPE,
								idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	return INTEGER
	IS
		nb_escales_v INTEGER;
	BEGIN
		SELECT count(*) into nb_escales_v
		FROM ESCALE
		WHERE idVol = idVol_p and idCompagnie = idCompagnie_p;
	
	return nb_escales_v;
END;
/
SHOW ERRORS FUNCTION nb_escales;
