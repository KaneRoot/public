-- Supprime un vol
create or replace procedure annuler_vol(	idVol_p VOL.idVol%TYPE,
											idCompagnie_p COMPAGNIE.idCompagnie%TYPE)

IS
BEGIN
-- suppression des réservations
	delete from RESERVATION
	where idBillet in (
		select B.idBillet from BILLET B
		where B.idVol = idVol_p and B.idCompagnie = idCompagnie_p
	);

-- suppression des billets
	delete from BILLET
	where idVol = idVol_p and idCompagnie = idCompagnie_p;

-- suppression des escales
	delete from ESCALE
	where idVol = idVol_p and idCompagnie = idCompagnie_p;

-- suppression du vol
	delete from VOL
	where idVol = idVol_p and idCompagnie = idCompagnie_p;

END;
/
SHOW ERRORS procedure annuler_vol;

