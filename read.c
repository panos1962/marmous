#include "shell.h"

bool read_command(char *s)
{
	char *exit_token[] = {
		"quit",
		"exit",
		"maria",
	};
	int i;

	printf("Our shell: ");

	if (fgets(s, MAX_CMD_LEN, stdin) == NULL)
	{
		return false;
	}

	s[strlen(s) - 1] = '\0';

	for (i = 0; i < sizeof(exit_token) / sizeof(exit_token[0]); i++)
	{
		if (strcmp(s, exit_token[i]) == 0)
		{
			return false;
		}
	}

	return true;
}
