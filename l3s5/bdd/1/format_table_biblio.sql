create table EDITEUR
(
	idEditeur number(6) PRIMARY KEY,
	nom varchar2(40),
	telephone varchar2(20),
	fax varchar2(20),
	pays varchar2(20)
);

create table REVUE
(
	idRevue number(8) PRIMARY KEY, 
	nomRevue varchar2(100) NOT NULL,
	idEditeur number(6),
	annee number(4),
	CONSTRAINT fk_revue_editeur FOREIGN KEY (idEditeur) REFERENCES EDITEUR
);

create table ARTICLE
(
	idArticle number(8) PRIMARY KEY,
	idRevue number(8) NOT NULL, 
	titre varchar2(200) NOT NULL,
	pageDebut number(4),
	pageFin number(4),
	volume number(4),
	serie number(3),
	CONSTRAINT fk_article_revue FOREIGN KEY (idRevue) REFERENCES REVUE
);

create table AUTEUR
(
	idAuteur number(8) PRIMARY KEY, 
	nomAuteur varchar2(60) NOT NULL, 
	email varchar2(80), 
	siteWeb varchar2(150)
);

create table ORGANISME
(
	idOrganisme number(6) PRIMARY KEY, 
	nom varchar2(512) NOT NULL, 
	telephone varchar2(20), 
	pays varchar2(20)
);

create table OUVRAGE
(
	idOuvrage number(8) PRIMARY KEY, 
	titre varchar2(80) NOT NULL, 
	idEditeur number(6) NOT NULL, 
	annee number(4),
	CONSTRAINT fk_ouvrage_editeur FOREIGN KEY (idEditeur) REFERENCES EDITEUR
);

create table MOTCLES
(
	idMot number(6) PRIMARY KEY, 
	mot varchar2(40) NOT NULL, 
	descriptif varchar2(80)
);

create table ARTICLE_AUTEUR
(
	idArticle number(8) NOT NULL, 
	idAuteur number(8) NOT NULL,
	CONSTRAINT fk_article_auteur_article FOREIGN KEY (idArticle) REFERENCES ARTICLE,
	CONSTRAINT fk_article_auteur_auteur FOREIGN KEY (idAuteur) REFERENCES AUTEUR
);

create table AUTEUR_ORGANISME
(
	idAuteur number(8) NOT NULL, 
	idOrganisme number(6) NOT NULL,
	CONSTRAINT fk_auteur_organisme_auteur FOREIGN KEY (idAuteur) REFERENCES AUTEUR,
	CONSTRAINT fk_auteur_organisme_organisme FOREIGN KEY (idOrganisme) REFERENCES ORGANISME
);

create table OUVRAGE_AUTEUR
(
	idOuvrage number(8) NOT NULL, 
	idAuteur number(8) NOT NULL,
	CONSTRAINT fk_ouvrage_auteur_auteur FOREIGN KEY (idAuteur) REFERENCES AUTEUR,
	CONSTRAINT fk_ouvrage_auteur_ouvrage FOREIGN KEY (idOuvrage) REFERENCES ORGANISME
);

create table ARTICLE_MOTCLES
(
	idArticle number(8) NOT NULL, 
	idMot number(6) NOT NULL,
	CONSTRAINT fk_article_motcles_auteur FOREIGN KEY (idArticle) REFERENCES AUTEUR ,
	CONSTRAINT fk_article_motcles_mot FOREIGN KEY (idMot) REFERENCES MOTCLES
);

