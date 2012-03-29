-- b. Alerter un client une heure avant l'expiration de sa réservation.
set serveroutput on;

CREATE or REPLACE function etat_reservation(	idBillet_p RESERVATION.idBillet%TYPE,
												idClient_p RESERVATION.idClient%TYPE)
	RETURN NUMBER
	IS
		date_vol_v DATE;
		date_reservation_v DATE;
		idVol_v	VOL.idVol%TYPE;
		idCompagnie_v COMPAGNIE.idCompagnie%TYPE;

	BEGIN 
		dbms_output.enable(1000);
		-- récupération des infos sur le vol (idVol + idCompagnie)
		SELECT idVol, idCompagnie INTO idVol_v, idCompagnie_v
			FROM BILLET
			WHERE idBillet = idBillet_p;

--		dbms_output.put_line('idVol ' || idVol_v || ' idCompagnie_p ' || idCompagnie_v);
--		dbms_output.put_line('idClient ' || idClient_p || ' idBillet_p ' || idBillet_p);

		-- récupération de la date de départ
		SELECT v.dateDepart INTO date_vol_v
			FROM VOL v
			WHERE v.idVol = idVol_v and v.idCompagnie = idCompagnie_v;

		-- récupération de la date de réservation
		SELECT bc.dateAchat INTO date_reservation_v 
			FROM BILLET_CLIENT bc
			WHERE bc.idBillet = idBillet_p and bc.idClient = idClient_p ;

		-- si date actuelle + 3 jours + 1h >= décollage de l'avion : alerte
		-- si date de réservation + 2 jours + 1h <= date actuelle : alerte
		IF (SYSDATE + 1/24 + 3) >= date_vol_v OR (date_reservation_v + 2 + 1/24) <= SYSDATE 
		THEN 
			RETURN 1;
		END IF;

		-- sinon pas d'alerte
		RETURN 0;
END ;
/
SHOW ERRORS FUNCTION etat_reservation;

-- test
-- idBillet idClient
select etat_reservation(3,1) from dual;
select etat_reservation(1,1) from dual;
