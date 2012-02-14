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
	FOREIGN KEY (idEditeur) REFERENCES EDITEUR
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
	FOREIGN KEY (idRevue) REFERENCES REVUE
);

AUTEUR(idAuteur number(8), nomAuteur varchar2(60), email varchar2(80), siteWeb varchar2(150))

ORGANISME(idOrganisme number(6), nom varchar2(512), telephone varchar2(20), pays varchar2(20))

OUVRAGE(idOuvrage number(8), titre varchar2(80), idEditeur number(6), annee number(4))

MOTCLES(idMot number(6), mot varchar2(40), descriptif varchar2(80))

ARTICLE_AUTEUR(idArticle number(8), idAuteur number(8))

AUTEUR_ORGANISME(idAuteur number(8), idOrganisme number(6))

OUVRAGE_AUTEUR(idOuvrage number(8), idAuteur number(8))

ARTICLE_MOTCLES(idArticle number(8), idMot number(6))

