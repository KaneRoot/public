alter table ARTICLE_AUTEUR drop CONSTRAINT fk_article_auteur_article;
alter table ARTICLE_AUTEUR drop CONSTRAINT fk_article_auteur_auteur;
alter table ARTICLE_MOTCLES drop CONSTRAINT fk_article_motcles_auteur;
alter table ARTICLE_MOTCLES drop CONSTRAINT fk_article_motcles_mot;
alter table OUVRAGE_AUTEUR drop CONSTRAINT fk_ouvrage_auteur_auteur;
alter table OUVRAGE_AUTEUR drop CONSTRAINT fk_ouvrage_auteur_ouvrage;
alter table AUTEUR_ORGANISME drop CONSTRAINT fk_auteur_organisme_auteur;
alter table AUTEUR_ORGANISME drop CONSTRAINT fk_auteur_organisme_organisme;

alter table REVUE drop CONSTRAINT fk_revue_editeur;
alter table ARTICLE drop CONSTRAINT fk_article_revue;
alter table OUVRAGE drop CONSTRAINT fk_ouvrage_editeur;


drop table EDITEUR;
drop table REVUE;
drop table ARTICLE;
drop table AUTEUR;
drop table ORGANISME;
drop table OUVRAGE;
drop table MOTCLES;
drop table ARTICLE_AUTEUR;
drop table AUTEUR_ORGANISME;
drop table OUVRAGE_AUTEUR;
drop table ARTICLE_MOTCLES;
