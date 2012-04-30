-- Se charge de dé-réserver les billets
create or replace procedure nettoyage
IS


BEGIN
-- On supprime les réservations qui se sont faites il y a plus de 48h
	DELETE from RESERVATION 
	where (SYSDATE - dateReservation) * 24 >= 48;

-- on supprime également les réservations si dans 72h il y a le décollage
	DELETE from RESERVATION 
	where idBillet in (
	select B.idBillet 
	from BILLET B JOIN VOL V 
	ON B.idVol = V.idVol and B.idCompagnie = V.idCompagnie
	where (V.dateDepart - SYSDATE)*24 <= 72);

END;
/
SHOW ERRORS procedure nettoyage;
