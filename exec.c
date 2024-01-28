#include "shell.h"
#include <unistd.h>	// fork, execvp...
#include <fcntl.h>	// open...
#include <sys/types.h>	// pid_t...
#include <sys/wait.h>	// wait...

bool exec(char *argv[], char *ifile, char *ofile, int omode)
{
	pid_t pid;
	int fd;

	pid = fork();

	if (pid < 0)
	{
		perror("fork failed");
		return false;
	}

	if (pid > 0)	// parent process (our shell)
	{
		wait(NULL);
		return true;
	}

	if (ifile != NULL)		// if input file specified
	{
		fd = open(ifile, O_RDONLY);

		if (fd < 0) {
			fprintf(stderr, "%s: cannot read\n", ifile);
			exit(1);
		}

		if (dup2(fd, 0) < 0)	// standard input redirection
		{
			perror("dup2 failed");
			exit(1);
		}

		if (close(fd) < 0)
		{
			perror(ifile);
			exit(1);
		}
	}

	if (ofile != NULL)		// if output file specified
	{
		fd = open(ofile, O_CREAT | O_WRONLY | omode, 0777);

		if (fd < 0) {
			fprintf(stderr, "%s: cannot write\n", ofile);
			exit(1);
		}

		if (dup2(fd, 1) < 0)	// standard output redirection
		{
			perror("dup2 failed");
			exit(1);
		}

		if (close(fd) < 0)
		{
			perror(ofile);
			exit(1);
		}
	}

	execvp(argv[0], argv);

	perror(argv[0]);
	exit(1);
}
