-- a. Mettre à jour le compteur des miles d'un client donné en prenant en compte l'option de réduction de 100€ pour l'achat du prochain billet(i.e nb_miles = 1000).
CREATE or REPLACE function maj_miles(	IN idClient_p CLIENT.id_client%TYPE, 
										IN idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	RETURN Boolean  -- renvoie vrai si on baisse le prix du billet
	IS
		miles_v carte_fidelie.miles%TYPE;
	BEGIN 
		SELECT miles INTO miles_v
			FROM CARTE_FIDELITE c
			WHERE c.idClient = idClient_p AND c.idCompagnie = idCompagnie_p;

		IF miles_v >= 1000 THEN    
			UPDATE carte_fidelite 
				set miles = miles_v - 900
				WHERE idClient = idClient_p and idCompagnie = idCompagnie_p;
			return TRUE ;
		END IF;

		UPDATE CARTE_FIDELITE 
			set miles = miles_v + 100
			WHERE idClient = idClient_p and idCompagnie = idCompagnie_p;
		return FALSE;
END;
/
SHOW ERRORS FUNCTION maj_miles;

-- test
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
select maj_miles(1, 1) from dual;
