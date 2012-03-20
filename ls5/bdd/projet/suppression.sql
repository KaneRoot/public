alter table VOL drop CONSTRAINT fk_vol_compagnie;
alter table VOL drop CONSTRAINT fk_vol_villedepart;
alter table VOL drop CONSTRAINT fk_vol_villearrivee;

alter table ESCALE drop CONSTRAINT fk_escale_villedepart;
alter table ESCALE drop CONSTRAINT fk_escale_villearrivee;

alter table CARTE_FIDELITE drop CONSTRAINT fk_carte_fidelite_compagnie;
alter table CARTE_FIDELITE drop CONSTRAINT fk_carte_fidelite_client;

alter table BILLET drop CONSTRAINT fk_billet_vol;
alter table BILLET drop CONSTRAINT fk_billet_compagnie;

alter table RESERVATION drop CONSTRAINT fk_reservation_client;
alter table RESERVATION drop CONSTRAINT fk_reservation_billet;

alter table VOL_ESCALE drop CONSTRAINT fk_vol_escale_vol;
alter table VOL_ESCALE drop CONSTRAINT fk_vol_escale_escale;

alter table ACHAT drop CONSTRAINT fk_achat_client;
alter table ACHAT drop CONSTRAINT fk_achat_billet;


drop table CLIENT;
drop table BILLET;
drop table VOL;
drop table ESCALE;
drop table COMPAGNIE;
drop table CARTE_FIDELITE; 
drop table RESERVATION;
drop table VOL_ESCALE;
drop table ACHAT;
