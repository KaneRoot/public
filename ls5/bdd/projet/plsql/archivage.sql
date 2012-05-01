-- procédure pour archiver les billets enregistrés
create or replace procedure archivage
IS
	CURSOR curseur IS SELECT * FROM BILLET WHERE etatBillet='A';
	dateachat_v DATE;
BEGIN 
	FOR ligne IN curseur
	LOOP
		select dateAchat into dateachat_v
		from BILLET_CLIENT where idBillet=ligne.idBillet;

		-- archives : idArchive, idVol, idCompagnie, prix, promo, dateAchat
		insert into ARCHIVES 
		VALUES(seq_archives.nextVal, ligne.idVol, ligne.idCompagnie, 
				ligne.prix, ligne.promo, dateachat_v);
	END LOOP;
END;
SHOW ERRORS procedure archivage;

