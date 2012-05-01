-- procédure pour archiver les billets enregistrés
create or replace procedure archivage
IS
	CURSOR curseur IS SELECT * FROM BILLET WHERE etatBillet='A' and idBillet in (select idBillet from BILLET_CLIENT);
	dateachat_v BILLET_CLIENT.dateAchat%TYPE;
	idclient_v CLIENT.idClient%TYPE;
BEGIN 
	FOR ligne IN curseur
	LOOP
		select dateAchat, idClient into dateachat_v, idclient_v
		from BILLET_CLIENT where idBillet=ligne.idBillet;

		-- archives : idArchive, idVol, idCompagnie, prix, promo, dateAchat
		insert into ARCHIVES 
		VALUES(seq_archives.nextVal, ligne.idVol, ligne.idCompagnie, 
				ligne.prix, ligne.promo, dateachat_v, idclient_v);
	END LOOP;
END;
/
SHOW ERRORS procedure archivage;

