-- a. Mettre à jour le compteur des miles d'un client donné en prenant en compte l'option de réduction de 100€ pour l'achat du prochain billet(i.e nb_miles = 1000).
CREATE or REPLACE procedure majMiles(	idClient_p CLIENT.idClient%TYPE, 
										idCompagnie_p COMPAGNIE.idCompagnie%TYPE)
	IS
		miles_v CARTE_FIDELITE.miles%TYPE;

	BEGIN 
		SELECT miles INTO miles_v
			FROM CARTE_FIDELITE c
			WHERE c.idClient = idClient_p AND c.idCompagnie = idCompagnie_p;

		miles_v := miles_v + 100;

		IF miles_v >= 1000 
		THEN    
			miles_v := miles_v - 1000;
		END IF;

		UPDATE CARTE_FIDELITE 
			set miles = miles_v
			WHERE idClient = idClient_p and idCompagnie = idCompagnie_p;
END;
/
SHOW ERRORS procedure majMiles;


-- test
execute majMiles(1,1);
