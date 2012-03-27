-- b. Alerter un client une heure avant l'expiration de sa réservation.
CREATE or REPLACE function etat_reservation(	IN idBillet_p RESERVATION.idBillet%TYPE,
												IN idClient_p RESERVATION.idClient%TYPE)
	RETURN BOOLEAN;
	IS
		date_vol_v DATE;
		date_reservation_v DATE;
		idVol_v	VOL.idVol%TYPE;
		idCompagnie_v COMPAGNIE.idCompagnie%TYPE;

	BEGIN 
		-- récupération des infos sur le vol (idVol + idCompagnie)
		SELECT idVol, idCompagnie INTO idVol_v, idCompagnie_v
			FROM BILLET
			WHERE idBillet = idBillet_p;

		-- récupération de la date de départ
		SELECT dateDepart INTO date_vol_v
			FROM VOL v
			WHERE v.dateDepart = date_vol_v and v.idVol = idVol_v and v.idCompagnie = idCompagnie_v;

		-- récupération de la date de réservation
		SELECT r.dateReservation INTO date_reservation_v
			FROM RESERVATION r
			WHERE idBillet_p = r.idBillet and idClient_p = r.idClient ;

		-- si date actulle + 3 jours + 1h >= décollage de l'avion : alerte
		-- si date de réservation + 2 jours + 1h <= date actuelle : alerte
		IF (SYSDATE + 1/24 + 3) >= date_vol_v OR (date_reservation_v + 2 + 1/24) <= SYSDATE 
		THEN 
			RETURN TRUE;
		END IF;

		-- sinon pas d'alerte
		RETURN FALSE;
END ;
