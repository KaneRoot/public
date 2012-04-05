create or REPLACE procedure reserver(	idClient_p CLIENT.idClient%TYPE,
											idBillet_p BILLET.idBillet%TYPE)
IS

BEGIN
	INSERT INTO RESERVATION VALUES(SYSDATE, idClient_p, idBillet_p);
	UPDATE BILLET SET etatBillet='R' WHERE idBillet = idBillet_p;
END;
/
SHOW ERRORS procedure reserver;
