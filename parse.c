#include "shell.h"
#include <fcntl.h>	// O_TRUNC, O_APPEND

bool parse(int tokc, char *tokv[])
{
	int i;
	char *ifile = NULL;
	char *ofile = NULL;
	int omode;
	int argc = 0;
	char *argv[MAX_TOK_CNT];
	int fd;
	pid_t pid;

	for (i = 0; i < tokc; i++) {
		if (strcmp(tokv[i], "<") == 0)	// input from file
		{
			if (++i >= tokc)
			{
				return false;
			}

			ifile = tokv[i];
		}
		else if (strcmp(tokv[i], ">") == 0)	// create/truncate file
		{
			if (++i >= tokc)
			{
				return false;
			}

			ofile = tokv[i];
			omode = O_TRUNC;
		}
		else if (strcmp(tokv[i], ">>") == 0)	// append to file
		{
			if (++i >= tokc)
			{
				return false;
			}

			ofile = tokv[i];
			omode = O_APPEND;
		}
		else if (ifile || ofile)	// arguments after redirection
		{
			return false;
		}
		else
		{
			argv[argc++] = tokv[i];
		}
	}

	argv[argc] = NULL;	// argument vector terminator
	return exec(argv, ifile, ofile, omode);
}
