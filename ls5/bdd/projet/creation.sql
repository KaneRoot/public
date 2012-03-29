create table CLIENT
(
	idClient number(15),
	loginClient varchar2(50) NOT NULL,
	motDePasseClient varchar2(50) NOT NULL,
	nomClient varchar2(50) NOT NULL,
	prenomClient varchar2(50) NOT NULL,
	adresseClient varchar2(100) NOT NULL,
	numTelClient number(10),
	CONSTRAINT pk_client PRIMARY KEY(idClient),
	CONSTRAINT u_client_nom_prenom_adresse UNIQUE(nomClient, prenomClient, adresseClient),
	CONSTRAINT u_client_login UNIQUE(loginClient)
);
create table VILLE
(
	idVille number(15),
	nomVille varchar2(50) NOT NULL,
	CONSTRAINT pk_ville PRIMARY KEY(idVille),
	CONSTRAINT u_ville_nomVille UNIQUE (nomVille)
);
create table COMPAGNIE
(
	idCompagnie number(10),
	nomCompagnie varchar2(50) NOT NULL,
	CONSTRAINT pk_compagnie PRIMARY KEY (idCompagnie)
);
create table ESCALE
(
	idEscale number(10),
	idVille number(15) NOT NULL,
	idVol number(10) NOT NULL,
	idCompagnie number(10) NOT NULL, 
	CONSTRAINT pk_escale PRIMARY KEY(idEscale),
	CONSTRAINT fk_escale_vol FOREIGN KEY (idVol, idCompagnie) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_escale_ville FOREIGN KEY(idVille) REFERENCES VILLE ON DELETE CASCADE
);
create table VOL
(
	idVol number(10),
	idCompagnie number(10) NOT NULL,
	idVilleDepart number(15) NOT NULL,
	idVilleArrivee number(15) NOT NULL,
	dateDepart date NOT NULL,
	dateArrivee date NOT NULL,
	CONSTRAINT pk_vol PRIMARY KEY(idVol, idCompagnie),
	CONSTRAINT fk_vol_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_vol_villedepart FOREIGN KEY (idVilleDepart) REFERENCES VILLE ON DELETE CASCADE,
	CONSTRAINT fk_vol_villearrivee FOREIGN KEY (idVilleArrivee) REFERENCES VILLE ON DELETE CASCADE
);
create table BILLET
(
	idBillet number(15),
	idVol number(10) NOT NULL,
	idCompagnie number(10) NOT NULL,
	prix number(15) NOT NULL,
	promo number(10),
	etatBillet char(1),
	CONSTRAINT pk_billet PRIMARY KEY(idBillet),
	CONSTRAINT ck_billet_etatbillet CHECK(etatBillet in ('A', 'R')),
	CONSTRAINT ck_billet_prix CHECK(prix > 0),
	CONSTRAINT fk_billet_vol_compagnie FOREIGN KEY (idVol, idCompagnie) REFERENCES VOL ON DELETE CASCADE
);
create table BILLET_CLIENT
(
	idAchat number(15),
	idBillet number(15) NOT NULL,
	idClient number(15) NOT NULL,
	dateAchat date DEFAULT SYSDATE NOT NULL,
	CONSTRAINT pk_billet_client PRIMARY KEY(idAchat),
	CONSTRAINT fk_billet_client_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE,
	CONSTRAINT fk_billet_client_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE
);
create table CARTE_FIDELITE
(
	idCompagnie number(10) NOT NULL, 
	idClient number(15) NOT NULL,
	miles number(10) NOT NULL,
	CONSTRAINT pk_carte_fidelite PRIMARY KEY(idClient, idCompagnie),
	CONSTRAINT fk_carte_fidelite_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_carte_fidelite_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE
);
create table RESERVATION
(
	dateReservation date DEFAULT SYSDATE NOT NULL,
	idClient number(15) NOT NULL,
	idBillet number(15) NOT NULL,
	CONSTRAINT pk_reservation PRIMARY KEY(idClient, idBillet),
	CONSTRAINT fk_reservation_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE,
	CONSTRAINT fk_reservation_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE
);
