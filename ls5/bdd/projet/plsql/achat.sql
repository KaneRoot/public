-- Pour que ça marche !
set serveroutput on;

-- Procédure d'achat
create or REPLACE procedure achat(	idClient_p CLIENT.idClient%TYPE,
									idBillet_p BILLET.idBillet%TYPE)
IS
	idCompagnie_v COMPAGNIE.idCompagnie%TYPE;
	idVol_v COMPAGNIE.idCompagnie%TYPE;
	miles_v CARTE_FIDELITE.miles%TYPE;
	miles2_v CARTE_FIDELITE.miles%TYPE;
	etatBillet_v BILLET.etatBillet%TYPE;
	nbbilletsvendus_v NUMBER(2);

BEGIN

	dbms_output.enable(1000);
	select etatBillet into etatBillet_v 
	from BILLET 
	where idBillet = idBillet_p;

	if etatBillet_v = 'A'
	then
		-- test pour si le billet est déjà réservé
		dbms_output.put_line('PROCEDURE ACHAT : DÉJÀ ACHETÉ');
	elsif etatBillet_v = 'R'
	then
		-- si déjà réservé
		dbms_output.put_line('PROCEDURE ACHAT : DÉJÀ RÉSERVÉ');
	end if;

	-- on récupère l'idCompagnie et l'idVol
	select idCompagnie, idVol into idCompagnie_v, idVol_v
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

	-- on ajoute ce billet à la liste des billets vendus
	INSERT INTO BILLET_CLIENT VALUES(seq_billet_client.nextVal, idBillet_p, idClient_p, SYSDATE);

	-- suppression de la réservation si elle exite
	delete from RESERVATION where idBillet = idBillet_p and idClient = idClient_p;

	-- augmentation du prix
	BEGIN
		nbbilletsvendus_v := nb_billets_achetes(idVol_v, idCompagnie_v);

		if(nbbilletsvendus_v mod 10) = 0
		then
			update BILLET set prix=prix*1.03 where idCompagnie = idCompagnie_v and idVol = idVol_v and (promo is null or promo=0);
		end if;
	END ;

END;
/
SHOW ERRORS procedure achat;

