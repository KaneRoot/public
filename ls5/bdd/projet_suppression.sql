alter table VOL drop CONSTRAINT fk_vol_compagnie;
alter table CARTE_FIDELITE drop CONSTRAINT fk_carte_fidelite_compagnie;
alter table CARTE_FIDELITE drop CONSTRAINT fk_carte_fidelite_client;
alter table RESERVATION drop CONSTRAINT fk_reservation_client;
alter table RESERVATION drop CONSTRAINT fk_reservation_billet;
alter table BILLET drop CONSTRAINT fk_billet_vol;
alter table BILLET drop CONSTRAINT fk_billet_client;
alter table BILLET drop CONSTRAINT fk_billet_compagnie;


