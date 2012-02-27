#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define N 31
struct 
{
	int signo;
	char * signame;
} tab[N] =
{
	{	SIGHUP		 ,"* Hangup (POSIX).  *,"},
	{	SIGINT		 ,"* Interrupt (ANSI).  *,"},
	{	SIGQUIT		 ,"* Quit (POSIX).  *,"},
	{	SIGILL		 ,"* Illegal instruction (ANSI).  *,"},
	{	SIGTRAP		 ,"* Trace trap (POSIX).  *,"},
	{	SIGABRT		 ,"* Abort (ANSI).  *,"},
	{	SIGIOT		 ,"* IOT trap (4.2 BSD).  *,"},
	{	SIGBUS		 ,"* BUS error (4.2 BSD).  *,"},
	{	SIGFPE		 ,"* Floating-point exception (ANSI).  *,"},
	{	SIGKILL		 ,"* Kill, unblockable (POSIX).  *,"},
	{	SIGUSR1		 ,"* User-defined signal 1 (POSIX).  *,"},
	{	SIGSEGV		 ,"* Segmentation violation (ANSI).  *,"},
	{	SIGUSR2		 ,"* User-defined signal 2 (POSIX).  *,"},
	{	SIGPIPE		 ,"* Broken pipe (POSIX).  *,"},
	{	SIGALRM		 ,"* Alarm clock (POSIX).  *,"},
	{	SIGTERM		 ,"* Termination (ANSI).  *,"},
	{	SIGSTKFLT	 ,"* Stack fault.  *,"},
	{	SIGCHLD		 ,"* Child status has changed (POSIX).  *,"},
	{	SIGCONT		 ,"* Continue (POSIX).  *,"},
	{	SIGSTOP		 ,"* Stop, unblockable (POSIX).  *,"},
	{	SIGTSTP		 ,"* Keyboard stop (POSIX).  *,"},
	{	SIGTTIN		 ,"* Background read from tty (POSIX).  *,"},
	{	SIGTTOU		 ,"* Background write to tty (POSIX).  *,"},
	{	SIGURG		 ,"* Urgent condition on socket (4.2 BSD).  *,"},
	{	SIGXCPU		 ,"* CPU limit exceeded (4.2 BSD).  *,"},
	{	SIGXFSZ		 ,"* File size limit exceeded (4.2 BSD).  *,"},
	{	SIGVTALRM	 ,"* Virtual alarm clock (4.2 BSD).  *,"},
	{	SIGPROF		 ,"* Profiling alarm clock (4.2 BSD).  *,"},
	{	SIGWINCH	 ,"* Window size change (4.3 BSD, Sun).  *,"},
	{	SIGIO		 ,"* IO now possible (4.2 BSD).  *,"},
	{	SIGPWR		 ,"* Power failure restart (System V).  *,"}
};

void print(int signal)
{
	struct tab;
	printf("Signal : %d : %s",signal , tab[signal].signame);
}

int main(int argc, char * argv[])
{
	sigset_t signaux;
	struct sigaction s;
	int i;
	s.sa_handler = print;
	s.sa_flags = 0;
	sigfillset(&s.sa_mask);

	for(i = 0 ; i < N ; i++) 
		sigaction(tab[i].signo, &s, NULL);

	sigfillset(&signaux);
	while(1)
	{
		sigsuspend(&signaux);
	}

	return EXIT_SUCCESS;
}

