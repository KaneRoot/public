-- recherche du prix minimal d'un billet disponible pour un vol

create or replace function prixmin(	idVol_p VOL.idVol%TYPE,
									idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
return NUMBER
IS
	prix_min_v NUMBER;
BEGIN
	select MIN(prix - promo) into prix_min_v
	FROM BILLET
	WHERE idVol = idVol_p and idCompagnie = idCompagnie_p and etatBillet is null;

	return prix_min_v;
END;
/
SHOW ERRORS function prixmin;
