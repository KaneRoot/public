set serveroutput on;

-- dans cette version, on ne peut pas savoir lorsqu'on n'a pas fait la réservation.
create or REPLACE procedure reserver(	idClient_p CLIENT.idClient%TYPE,
											idBillet_p BILLET.idBillet%TYPE)
IS
	val NUMBER(2);
	etatBillet_v BILLET.etatBillet%TYPE;

BEGIN

	dbms_output.enable(1000);

	-- on récupère l'état du billet
	SELECT etatBillet into etatBillet_v
		FROM BILLET
		WHERE idBillet = idBillet_p;

	if etatBillet_v = 'A'
	then
		dbms_output.put_line('PROCEDURE RESERVER : DÉJÀ ACHETÉ');
	elsif etatBillet_v = 'R'
	then
		dbms_output.put_line('PROCEDURE RESERVER : DÉJÀ RÉSERVÉ');
	else

		-- on ne fait pas de réservation si on a déjà 3 réservations en cours
		select count(*) into val
			from RESERVATION
			where idClient = idClient_p;
		
		if val < 3
		then
			-- on insère une nouvelle réservation dans la table RESERVATION 
			INSERT INTO RESERVATION VALUES(SYSDATE, idClient_p, idBillet_p);

			-- On marque le billet comme étant réservé
			UPDATE BILLET SET etatBillet='R' WHERE idBillet = idBillet_p;
		end if;

	end if;

END;
/
SHOW ERRORS procedure reserver;

