-- Pour que ça marche ! Probablement lié à une spécificité du SGBD oracle
set serveroutput on;

-- Généralement pour le nom des variables j'adopte cette convention :
-- je suffixe par "_p" si c'est une variable passée en paramètre et
-- je suffixe par "_v" si c'est une variable créée dans la fonction

-- Procédure d'achat
-- on crée ou on remplace si la procédure existait déjà
-- une procédure nommée "achat" qui prend en paramètre 2 valeurs :
-- une variable nommée "idClient_p" du même type que 
-- idClient de la table CLIENT
-- et pareillement pour idBillet_p qui est du même type que idBillet dans BILLET
create or REPLACE procedure achat(	idClient_p CLIENT.idClient%TYPE,
									idBillet_p BILLET.idBillet%TYPE)
IS	-- équivalent à une accolade
	idCompagnie_v COMPAGNIE.idCompagnie%TYPE;
	idVol_v COMPAGNIE.idCompagnie%TYPE;
	miles_v CARTE_FIDELITE.miles%TYPE;
	miles2_v CARTE_FIDELITE.miles%TYPE;
	etatBillet_v BILLET.etatBillet%TYPE;
	nbbilletsvendus_v NUMBER(2);

BEGIN

	-- on active la possibilité d'écrire 1000 lignes de debug, 
	-- probablement lié à Oracle
	dbms_output.enable(1000);

	-- on démarre un ensemble d'instructions, 
	-- qui peuvent aboutir à une exception
	BEGIN
		-- on va chercher l'état du billet dont l'identifiant a été passé en
		-- paramètre de la fonction, et on le place dans la variable 
		-- "etatBillet_v"
		select etatBillet into etatBillet_v from BILLET where idBillet = idBillet_p;

		-- Exception si on ne trouve pas de données ALORS on indique une erreur
		EXCEPTION
			when NO_DATA_FOUND THEN
				dbms_output.put_line('PAS TROUVE ETAT');
	end ;

	-- si le billet est déjà acheté
	if etatBillet_v = 'A'
	then
		-- test pour si le billet est déjà réservé
		dbms_output.put_line('PROCEDURE ACHAT : DÉJÀ ACHETÉ');
		raise_application_error(-20000, 'DEJA ACHETE');
	elsif etatBillet_v = 'R'	-- si le billet est réservé
	then
		-- si déjà réservé
		dbms_output.put_line('PROCEDURE ACHAT : DÉJÀ RÉSERVÉ');
	end if;

	-- on récupère l'idCompagnie et l'idVol
	BEGIN
		-- on sélectionne deux éléments de la table BILLET qu'on place dans
		-- les variables idCompagnie_v et idVol_v
		select idCompagnie, idVol into idCompagnie_v, idVol_v
			from BILLET
			where idBillet = idBillet_p;
		EXCEPTION
			when NO_DATA_FOUND THEN
				dbms_output.put_line('PAS TROUVE IDCOMPAGNIE NI OU IDVOL');
	end ;

	-- s'il doit avoir une réduction de prix
	begin
		select miles into miles_v
			from CARTE_FIDELITE
			where idClient = idClient_p and idCompagnie = idCompagnie_v;
		EXCEPTION
			when NO_DATA_FOUND THEN
				INSERT INTO CARTE_FIDELITE VALUES(idCompagnie_v, idClient_p, 0);
	end ;

	
	-- on met à jour les miles
	-- on réutilise une fonction faite dans un autre fichier et que
	-- nous aurons déjà chargé dans le SGBD
	majMiles(idClient_p,idCompagnie_v);

	-- nouveau nb de miles
	begin
		select miles into miles2_v
			from CARTE_FIDELITE
			where idClient = idClient_p and idCompagnie = idCompagnie_v;
		EXCEPTION
			when NO_DATA_FOUND THEN
				dbms_output.put_line('PAS TROUVE MILES');
	end ;

	-- si nb miles actuels < ancien = 100€ de réduction
	if miles_v > miles2_v then
		UPDATE BILLET SET prix = greatest(prix-100, 1) where idBillet = idBillet_p;
	end if;

	-- si on a une réservation	
	UPDATE BILLET SET etatBillet='A' WHERE idBillet = idBillet_p;

	-- on ajoute ce billet à la liste des billets vendus
	INSERT INTO BILLET_CLIENT VALUES(seq_billet_client.nextVal, idBillet_p, idClient_p, SYSDATE);

	-- suppression de la réservation si elle existe
	delete from RESERVATION where idBillet = idBillet_p and idClient = idClient_p;

	-- augmentation du prix
	BEGIN
		-- on récupère le nombre de billets vendus en réutilisant une fonction 
		-- définie dans un autre fichier et qu'on aura chargé dans notre 
		-- SGBD plus tôt
		nbbilletsvendus_v := nb_billets_achetes(idVol_v, idCompagnie_v);

		-- si le nombre de billets modulo 10 est égal à 0 (à chaque fois qu'on en vend 10)
		-- solution fonctionne que si on ne rembourse pas un achat d'un billet
		-- et par bonheur, ce n'était pas dans le cahier des charges
		if(nbbilletsvendus_v mod 10) = 0
		then
			update BILLET set prix=prix*1.03 where idCompagnie = idCompagnie_v and idVol = idVol_v and (promo is null or promo=0) and etatBillet is null;
		end if;
	END ;
END;	-- fin de la procédure
/
SHOW ERRORS procedure achat; 
-- Une option pour afficher les éventuelles erreurs dans la procédure
