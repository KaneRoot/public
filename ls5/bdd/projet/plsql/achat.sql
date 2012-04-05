create or REPLACE procedure achat(	idClient_p CLIENT.idClient%TYPE,
									idBillet_p BILLET.idBillet%TYPE)
IS
	idCompagnie_v COMPAGNIE.idCompagnie%TYPE;
	miles_v CARTE_FIDELITE.miles%TYPE;
	miles2_v CARTE_FIDELITE.miles%TYPE;
BEGIN
	-- on récupère l'idCompagnie
	select idCompagnie into idCompagnie_v
		from BILLET
		where idBillet = idBillet_p;

	-- s'il doit avoir une réduction de prix
	select miles into miles_v
		from CARTE_FIDELITE
		where idClient = idClient_p and idCompagnie = idCompagnie_v;
	
	-- on met à jour les miles
	majMiles(idClient_p,idCompagnie_v);

	-- nouveau nb de miles
	select miles into miles2_v
		from CARTE_FIDELITE
		where idClient = idClient_p and idCompagnie = idCompagnie_v;
	
	-- si nb miles actuels < ancien = 100€ de réduction
	if miles_v > miles2_v
	then
		UPDATE BILLET SET prix=prix-100 where idBillet = idBillet_p;
	end if;

	-- si on a une réservation	
	UPDATE BILLET SET etatBillet='A' WHERE idBillet = idBillet_p;

	INSERT INTO

END;
/
SHOW ERRORS procedure achat;

