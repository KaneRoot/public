typedef int pblk_t ;			/* num de bloc physique sur disque */
typedef int lblk_t ;			/* num de bloc logique ds un fichier */
typedef int inum_t ;			/* numero d'inode */

typedef struct context *ctxt_t ;	/* contexte d'acces au file system */
typedef struct buffer *buf_t ;		/* buffer d'E/S */
typedef struct ofile *file_t ;		/* descripteur de fichier ouvert */

/* fonctions de gestion du contexte */
ctxt_t e2_ctxt_init (char *file, int maxbuf) ;
void   e2_ctxt_close (ctxt_t c) ;
int    e2_ctxt_blksize (ctxt_t c) ;

/* fonction de lecture directe sur le disque */
int    e2_block_fetch (ctxt_t c, pblk_t blkno, void *data) ;

/* fonctions de lecture bufferisee */
buf_t  e2_buffer_get (ctxt_t c, pblk_t blkno) ;
void   e2_buffer_put (ctxt_t c, buf_t b) ;
void   *e2_buffer_data (buf_t b) ;
void   e2_buffer_stats (ctxt_t c) ;

/* fonctions de lecture d'inode */
pblk_t e2_inode_to_pblk (ctxt_t c, inum_t i) ;
struct ext2_inode *e2_inode_read (ctxt_t c, inum_t i, buf_t b) ;
pblk_t e2_inode_lblk_to_pblk (ctxt_t c, struct ext2_inode *in, lblk_t blkno) ;

/* fonctions d'acces simplifie au fichier */
file_t e2_file_open (ctxt_t c, inum_t i) ;
void   e2_file_close (file_t of) ;
int    e2_file_getc (file_t of) ;
int    e2_file_read (file_t of, void *data, int len) ;

/* fonction de lecture d'une entree de repertoire */
struct ext2_dir_entry_2 *e2_dir_get (file_t of) ;
inum_t e2_dir_lookup (ctxt_t c, inum_t i, char *str, int len) ;

/* fonctions realisant des operations de haut niveau */
int    e2_cat (ctxt_t c, inum_t i, int disp_pblk) ;
int    e2_ls (ctxt_t c, inum_t i) ;

/* fonction de recherche du numero d'inode d'un fichier, donne par son chemin */
inum_t e2_namei (ctxt_t c, char *path) ;
