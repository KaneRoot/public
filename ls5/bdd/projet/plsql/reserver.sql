-- dans cette version, on ne peut pas savoir lorsqu'on n'a pas fait la réservation.
create or REPLACE procedure reserver(	idClient_p CLIENT.idClient%TYPE,
											idBillet_p BILLET.idBillet%TYPE)
IS
	val NUMBER(2);
BEGIN
	-- si le billet est déjà réservé ou acheté
	SELECT count(*) into val
		FROM BILLET
		WHERE idBillet = idBillet_p and etatBillet IN ('R', 'A');

	if val != 0
	then
		exit;
	end if;

	-- on ne fait pas de réservation si on a déjà 3 réservations en cours
	select count(*) into val
		from RESERVATION
		where idClient = idClient_p;
	
	if val >= 3
	then
		exit;
	end if;

	-- on insère une nouvelle réservation dans la table RESERVATION 
	INSERT INTO RESERVATION VALUES(SYSDATE, idClient_p, idBillet_p);

	-- On marque le billet comme étant réservé
	UPDATE BILLET SET etatBillet='R' WHERE idBillet = idBillet_p;

END;
/
SHOW ERRORS procedure reserver;

--create or replace trigger trig_reservation
--before insert on RESERVATION
--DECLARE
--	nombre_reservation_v NUMBER(1);
--BEGIN
--	select count(*) into nombre_reservation_v
--		from RESERVATION
--		where idClient = :new.idClient ;
--	
--	if 
