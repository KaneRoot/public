int getchar1(void);
int getchar2(void);
void test_getchar1();
void test_getchar2();
void test_print_ls(int,char**);
void print_ls(char *);
void liste_rep(char *);
void test_liste_rep(int,char **);
int is_dir(char *);

/*
S_IRWXU    00700     mask for file owner permissions
S_IRUSR    00400     owner has read permission
S_IWUSR    00200     owner has write permission
S_IXUSR    00100     owner has execute permission
S_IRWXG    00070     mask for group permissions
S_IRGRP    00040     group has read permission
S_IWGRP    00020     group has write permission
S_IXGRP    00010     group has execute permission
S_IRWXO    00007     mask for permissions for others (not in group)
S_IROTH    00004     others have read permission
S_IWOTH    00002     others have write permission
S_IXOTH    00001     others have execute permission
*/
