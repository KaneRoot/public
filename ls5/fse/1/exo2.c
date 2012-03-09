#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define STR_SIZE 512

typedef struct
{
	unsigned int pid ;
	unsigned int ppid ;
	char cmd [STR_SIZE] ;
	unsigned int uid ;
	unsigned int gid ;
	char state ;
	unsigned int mem ;
} proc_s;


void quitter(char erreur[]);
void aff_ps(proc_s *p);
int lire_ps(int pid, proc_s * p);

int main(int argc, char * argv[])
{
	int pid;
	if(argc != 2) 
		pid = 31545;
	else
		pid = atoi(argv[1]);

	proc_s *processus = (proc_s*) malloc(sizeof(proc_s));
	if(lire_ps(pid, processus) == EXIT_FAILURE)
		quitter("Erreur lire_ps");

	processus->ppid = 152;
	processus->uid = 1566;
	processus->mem = 15666;
	aff_ps(processus);
	return EXIT_SUCCESS;
}
void quitter(char erreur[])
{
	printf(erreur);
	exit(EXIT_FAILURE);
}

int lire_ps(int pid, proc_s * p)
{
	int fd = -1;
	char buffer[STR_SIZE], rep[STR_SIZE], fichier[STR_SIZE];

	snprintf(rep, STR_SIZE, "/proc/%d/", pid);

	// CMDLINE
	snprintf(fichier, STR_SIZE, "%s/cmdline",rep);
	fd = open(fichier, O_RDONLY);
	if(fd <= 0) 
		return EXIT_FAILURE;
	read(fd, p->cmd , STR_SIZE);
	close(fd);

	// STATUS
	snprintf(fichier, STR_SIZE, "%s/status",rep);
	fd = open(fichier, O_RDONLY);
	if(fd <= 0)
		return EXIT_FAILURE;
	read(fd, buffer, STR_SIZE*2);
	printf("Buffer : %s\n", buffer);

	for(i = 1 ; ; i++, buffer = NULL)
	{
		token = strtok_r(str1, argv[2], &saveptr1);
		if (token == NULL)
			break;
		printf("%d: %s\n", j, token);

		for (str2 = token; ; str2 = NULL) {
			subtoken = strtok_r(str2, argv[3], &saveptr2);
		if (subtoken == NULL)
			break;
		printf(" --> %s\n", subtoken);

	}

	sscanf(buffer, "State:\t%c", &p->state);
	close(fd);

	p->pid = pid;
	return EXIT_SUCCESS;
}
void aff_ps(proc_s *p)
{
	printf("pid : %d \nppid : %d \ncmd : %s\nuid : %d\ngid : %d\nstate : %c\nmem : %d\n", 
			p->pid, p->ppid, p->cmd, p->uid, p->gid, p->state, p->mem);
}
