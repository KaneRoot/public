-- TOUJOURS METTRE DES SIMPLES COTES
-- PAS DE COMMENTAIRE SUR UNE LIGNE AVEC UNE INSTRUCTION

-- idClient loginClient motDePasseClient nomClient prenomClient adresseClient numTelClient
INSERT INTO CLIENT VALUES(seq_client.nextVal,'login1', 'mdp1', 'moi1', 'prenomdemoi1', 'adresse1', 1050305010); 
INSERT INTO CLIENT VALUES(seq_client.nextVal,'login2', 'mdp2', 'moi2', 'prenomdemoi2', 'adresse2', 1050305010); 
INSERT INTO CLIENT VALUES(seq_client.nextVal,'login3', 'mdp3', 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 
--
-- idCompagnie nomCompagnie
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla1');
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla2');
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla3');
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla4');
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla5');
INSERT INTO COMPAGNIE VALUES(seq_compagnie.nextVal, 'bla6');


-- idGestionnaire loginGestionnaire mdpGestionnaire idCompagnie
INSERT INTO GESTIONNAIRE VALUES(seq_gestionnaire.nextVal, 'gest1', 'gest1', 2);

-- idVille nomVille
INSERT INTO VILLE VALUES(seq_ville.nextVal, 'PARIS');
INSERT INTO VILLE VALUES(seq_ville.nextVal, 'LARIS');
INSERT INTO VILLE VALUES(seq_ville.nextVal, 'SARIS');

-- idVol idCompagnie idVilleDepart idVilleArrivee dateDepart dateArrivee
INSERT INTO VOL VALUES(1, 2, 2, 4, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(1, 3, 2, 4, to_date('2012/03/29 18:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(2, 2, 3, 4, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));
INSERT INTO VOL VALUES(3, 2, 4, 2, to_date('2012/03/16 21:02:44', 'yyyy/mm/dd hh24:mi:ss'), to_date('2012/04/18 21:02:44', 'yyyy/mm/dd hh24:mi:ss'));

-- idEscale idVille idVol idCompagnie
INSERT INTO ESCALE VALUES(seq_escale.nextVal, 2, 1, 2);
INSERT INTO ESCALE VALUES(seq_escale.nextVal, 3, 1, 3);
INSERT INTO ESCALE VALUES(seq_escale.nextVal, 3, 1, 3);

-- idCompagnie idClient miles
INSERT INTO CARTE_FIDELITE VALUES(2, 2, 900);
INSERT INTO CARTE_FIDELITE VALUES(3, 2, 950);

-- idBillet idVol idCompagnie prix promo etatBillet
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, null);
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, null);
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, null);
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, null);
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, 'A');
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, 'A');
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, 'R');
INSERT INTO BILLET VALUES(seq_billet.nextVal, 2, 2, 1000, 0, 'R');

-- idAchat idBillet idClient dateAchat
INSERT INTO BILLET_CLIENT VALUES(seq_billet_client.nextVal, 2, 2, DEFAULT);
INSERT INTO BILLET_CLIENT VALUES(seq_billet_client.nextVal, 3, 2, DEFAULT);

-- erreur volontaire
-- INSERT INTO CLIENT VALUES(3, 'moi3', 'prenomdemoi3', 'adresse3', 1050305010); 

