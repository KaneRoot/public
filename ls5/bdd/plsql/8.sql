create or replace procedure suppressionEtape(idCirc_p circuit.identifiant%TYPE, numEtape NUMBER)
IS
	i INTEGER := 1;
	Cursor curs_ordre IS select * from Etape WHERE identifiant = idCirc_p ORDER BY ordre ASC FOR UPDATE OF ordre;

BEGIN
	if numEtape < 1 then RAISE_APPLICATION_ERROR(-2000, 'Numéro étape incohérent')
	end if;

	for row in curs_ordre
	loop
		if row.ordre = numEtape then
			delete from etape where current of curs_ordre;
			i := i - 1;
		else if row.ordre > numEtape then 
			update Etape set ordre = i where current of curs_ordre;
		end if;
		i := i + 1;
	end loop;

END;
SHOW ERRORS;
