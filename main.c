#include "shell.h"

int main(void)
{
	char buffer[MAX_CMD_LEN + 1];

	printf("Type \"quit\", \"exit\" or [Ctrl-D] to exit shell\n");

	while (read_command(buffer))
	{
		int tokc = 0;
		char *tokv[MAX_TOK_CNT];

		tokv[tokc] = strtok(buffer, " ");

		while (tokv[tokc] != NULL)
		{
			tokc++;
			tokv[tokc] = strtok(NULL, " ");
		}

		if (!parse(tokc, tokv)) {
			printf("syntax error\n");
		}
	}

	exit(0);
}
