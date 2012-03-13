create table CLIENT
(
	idClient number(15) PRIMARY KEY,
	nomClient varchar2(50),
	prenomClient varchar2(50),
	adresseClient varchar2(100),
	numTelClient number(10)
);
create table COMPAGNIE
(
	idCompagnie number(10) PRIMARY KEY,
	nomCompagnie varchar2(50)
);
create table ESCALE
(
	idEscale number(10) PRIMARY KEY,
	villeDepart varchar2(50),
	villeArrivee varchar2(50)	
);
create table VOL
(
	idVol number(10) PRIMARY KEY,
	dateDepart date,
	dateArrivee date,
	villeDepart varchar2(50),
	villeArrivee varchar2(50),
	idCompagnie number(10) PRIMARY KEY,
	CONSTRAINT fk_vol_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE
);
create table BILLET
(
	idBillet number(15) PRIMARY KEY,
	promo number(2) CHECK (promo > 0),
	idVol number(10) PRIMARY KEY,
	idCompagnie number(10) PRIMARY KEY,
	CONSTRAINT fk_billet_vol FOREIGN KEY (idVol) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_billet_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE
);
create table ACHAT
(
	idAchat number(15) PRIMARY KEY,
	idBillet number(15) NOT NULL,
	idClient number(15) NOT NULL,
	prix number(15) CHECK (prix > 0),
	dateAchat date,
	CONSTRAINT fk_achat_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE ,
	CONSTRAINT fk_achat_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE
);
create table CARTE_FIDELITE
(
	idCompagnie number(8) NOT NULL, 
	idClient number(6) NOT NULL,
	miles number(10),
	CONSTRAINT fk_carte_fidelite_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_carte_fidelite_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE
);
create table RESERVATION
(
	idReservation number(15) PRIMARY KEY,
	dateReservation date,
	etatReservation char(1) CHECK (etatReservation = 'R' OR etatReservation = 'A'),
	idClient number(15) NOT NULL,
	idBillet number(15) NOT NULL,
	CONSTRAINT fk_reservation_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE,
	CONSTRAINT fk_reservation_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE
);
create table VOL_ESCALE
(
	idVol number(10) NOT NULL,
	idEscale number(10) NOT NULL,
	CONSTRAINT fk_vol_escale_vol FOREIGN KEY (idVol) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_vol_escale_escale FOREIGN KEY (idEscale) REFERENCES ESCALE ON DELETE CASCADE
);
