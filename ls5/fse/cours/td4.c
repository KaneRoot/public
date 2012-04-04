#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZ 512

FILE * fopen(char * nom, int flag)
{
	int fd;
	if(fd = open(nom, conversion(flag)) < 0) /* "r" -> O_RDONLY, "w" -> O_WRONLY, etc… */
		return NULL;
	if( (_iob[fd]._base = malloc(BUFSIZ)) == NULL)
		return (NULL);
	_iob[fd]._cnt = 0;
	_iob[fd]._ptr = _iob[fd]._base; // optionnel sans doute.
	_iob[fd]._file = fd;
	_iob[fd]._flag = conversion(flag);

	return fd;;
}

int _filbuf(struct _iobuf *p)
{
	p->ptr = p->base;
	p->cnt = read(p->_file, BUFSIZ);
	if(p->cnt <= 0)
		return (EOF);

	return (getc(p));
}
void quitter(char * error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
	return EXIT_SUCCESS;
}

