create table CLIENT
(
	idClient number(15) PRIMARY KEY,
	nomClient varchar2(50) NOT NULL,
	prenomClient varchar2(50) NOT NULL,
	adresseClient varchar2(100) NOT NULL,
	numTelClient number(10)
);
create table COMPAGNIE
(
	idCompagnie number(10) PRIMARY KEY,
	nomCompagnie varchar2(50) NOT NULL
);
create table ESCALE
(
	idEscale number(10) PRIMARY KEY,
	villeDepart varchar2(50) NOT NULL,
	villeArrivee varchar2(50) NOT NULL	
);
create table VOL
(
	idVol number(10) PRIMARY KEY,
	idCompagnie number(10) PRIMARY KEY,
	dateDepart date NOT NULL,
	dateArrivee date NOT NULL,
	villeDepart varchar2(50) NOT NULL,
	villeArrivee varchar2(50) NOT NULL,
	CONSTRAINT fk_vol_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE
);
create table BILLET
(
	idBillet number(15) PRIMARY KEY,
	idVol number(10) PRIMARY KEY,
	idCompagnie number(10) PRIMARY KEY,
	promo number(2) CHECK (promo > 0 AND promo < 100),
	CONSTRAINT fk_billet_vol FOREIGN KEY (idVol) REFERENCES VOL ON DELETE CASCADE,
	CONSTRAINT fk_billet_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE
);
create table ACHAT
(
	idAchat number(15) PRIMARY KEY,
	idBillet number(15) NOT NULL,
	idClient number(15) NOT NULL,
	prix number(15) CHECK (prix > 0),
	dateAchat date NOT NULL,
	CONSTRAINT fk_achat_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE ,
	CONSTRAINT fk_achat_billet FOREIGN KEY (idBillet) REFERENCES BILLET ON DELETE CASCADE
);
create table CARTE_FIDELITE
(
	idCompagnie number(8) PRIMARY KEY, 
	idClient number(6) PRIMARY KEY,
	miles number(10) NOT NULL,
	CONSTRAINT fk_carte_fidelite_compagnie FOREIGN KEY (idCompagnie) REFERENCES COMPAGNIE ON DELETE CASCADE,
	CONSTRAINT fk_carte_fidelite_client FOREIGN KEY (idClient) REFERENCES CLIENT ON DELETE CASCADE
);
create table RESERVATION
(
	idReservation number(15) PRIMARY KEY,
	dateReservation date NOT NULL,
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
