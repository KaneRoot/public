create or replace procedure aff_reserv_cli
IS
	CURSOR curs_circ IS 
		SELECT * FROM Circuit WHERE dateDepart > SYSDATE
		ORDER BY dateDepart ASC;
	CURSOR curs_cli(id_p INTEGER) IS
		SELECT * FROM Reservation JOIN client ON Client.idClient = Reservation.idClient
		WHERE identifiant = id_p;

BEGIN 
	FOR row_circ IN curs_circ
	LOOP
		DBMS_OUTPUT_PUTLINE('Circuit ' || row_circ.identifiant || ', ' || row_circ.villeDepart 
				|| ' _ ' || row_circ.villeArrive || ' , ' || row_circ.dateDepart);
		FOR row_cli IN curs_cli(row_circ.identifiant)
		LOOP
			DBMS_OUTPUT_PUTLINE('Nom : ' || row_cli.nom || ' ' || row_cli.prenom || ' : ' || row_cli.nbplace);
		END LOOP;
	END LOOP;
END;
SHOW ERRORS;

