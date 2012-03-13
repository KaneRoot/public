create table CLIENT
{
	id_client number(15) PRIMARY KEY,
	nom_client varchar2(50),
	prenom_client varchar2(50),
	adresse_client varchar2(100),
	num_tel_client number(10)
};
create table VOL
{
	id_vol number(10) PRIMARY KEY,
	date_depart date,
	date_arrivee date,
	ville_depart varchar2(50),
	ville_arrivee varchar2(50),
	CONSTRAINT fk_vol_compagnie FOREIGN KEY(id_compagnie) REFERENCES COMPAGNIE
};
create table ESCALE
{
	id_escale number(10) PRIMARY KEY,
	ville_depart varchar2(50),
	ville_arrivee varchar2(50)	
};
create table COMPAGNIE
{
	id_compagnie number(10) PRIMARY KEY,
	nom_compagnie varchar2(50)
};
create table CARTE_FIDELITE
{
	id_compagnie number(8) NOT NULL, 
	id_client number(6) NOT NULL,
	miles number(10),
	CONSTRAINT fk_carte_fidelite_compagnie FOREIGN KEY (id_compagnie) REFERENCES COMPAGNIE,
	CONSTRAINT fk_carte_fidelite_client FOREIGN KEY (id_client) REFERENCES CLIENT
};
create table RESERVATION
{
	id_reservation number(15) PRIMARY KEY,
	date_reservation date,
	etat_reservation char(1),
	id_client number(15) NOT NULL,
	id_billet number(15) NOT NULL,
	CONSTRAINT fk_reservation_client FOREIGN KEY (id_client) REFERENCES CLIENT,
	CONSTRAINT fk_reservation_billet FOREIGN KEY (id_billet) REFERENCES BILLET
};
create table BILLET
{
	id_billet number(15) PRIMARY KEY,
	promo number(2),
	prix number(15),
	date_achat date,

	id_vol number(10) NOT NULL,
	id_client number(15) NOT NULL,
	id_compagnie number(10) NOT NULL,
	CONSTRAINT fk_billet_vol FOREIGN KEY (id_vol) REFERENCES VOL,
	CONSTRAINT fk_billet_client FOREIGN KEY (id_client) REFERENCES CLIENT,
	CONSTRAINT fk_billet_compagnie FOREIGN KEY (id_compagnie) REFERENCES COMPAGNIE
};


