-- TOUJOURS METTRE DES SIMPLES COTES
-- PAS DE COMMENTAIRE SUR UNE LIGNE AVEC UNE INSTRUCTION

-- idClient loginClient motDePasseClient nomClient prenomClient adresseClient numTelClient
INSERT INTO CLIENT VALUES(1,'login1', 'mdp1', 'moi1', 'prenomdemoi1', 'adresse1', 1050305010); 
INSERT INTO CLIENT VALUES(2,'login2', 'mdp2', 'moi2', 'prenomdemoi2', 'adresse2', 1050305010); 
INSERT INTO CLIENT VALUES(3,'login3', 'mdp3', 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 

-- idCompagnie nomCompagnie
INSERT INTO COMPAGNIE VALUES(1, 'bla1');
INSERT INTO COMPAGNIE VALUES(2, 'bla2');
INSERT INTO COMPAGNIE VALUES(3, 'bla3');
INSERT INTO COMPAGNIE VALUES(4, 'bla4');
INSERT INTO COMPAGNIE VALUES(5, 'bla5');
INSERT INTO COMPAGNIE VALUES(6, 'bla6');

-- idVille nomVille
INSERT INTO VILLE VALUES(1, 'PARIS');
INSERT INTO VILLE VALUES(2, 'LARIS');
INSERT INTO VILLE VALUES(3, 'SARIS');

-- idVol idCompagnie idVilleDepart idVilleArrivee dateDepart dateArrivee
INSERT INTO VOL VALUES(1, 1, 1, 3, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(1, 2, 1, 3, to_date('2012/03/29 18:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(2, 1, 2, 3, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(3, 1, 3, 1, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));

-- idEscale idVille idVol idCompagnie
INSERT INTO ESCALE VALUES(1, 1, 1, 1);
INSERT INTO ESCALE VALUES(2, 2, 1, 1);
INSERT INTO ESCALE VALUES(3, 3, 1, 1);

-- idCompagnie idClient miles
INSERT INTO CARTE_FIDELITE VALUES(1, 1, 900);
INSERT INTO CARTE_FIDELITE VALUES(2, 1, 950);

-- idBillet idVol idCompagnie prix promo etatBillet
INSERT INTO BILLET VALUES(1, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(2, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(3, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(4, 1, 1, 1000, 0, null);
INSERT INTO BILLET VALUES(5, 1, 1, 1000, 0, 'A');
INSERT INTO BILLET VALUES(6, 1, 1, 1000, 0, 'A');
INSERT INTO BILLET VALUES(7, 1, 1, 1000, 0, 'R');
INSERT INTO BILLET VALUES(8, 1, 1, 1000, 0, 'R');

-- idAchat idBillet idClient dateAchat
INSERT INTO BILLET_CLIENT VALUES(1, 1, 1, DEFAULT);
INSERT INTO BILLET_CLIENT VALUES(2, 2, 1, DEFAULT);

-- erreur volontaire
-- INSERT INTO CLIENT VALUES(3, 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 

