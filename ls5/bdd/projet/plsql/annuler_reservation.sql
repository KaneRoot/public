create or replace procedure annuler_reservation(	idClient_p CLIENT.idClient%TYPE,
													idBillet_p BILLET.idBillet%TYPE)

IS
BEGIN
	delete from RESERVATION 
	where idClient=idClient_p and idBillet=idBillet_p;

	update BILLET set etatBillet = NULL where idBillet=idBillet_p;

END;
/
SHOW ERRORS procedure annuler_reservation;
