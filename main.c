#include <stdio.h>	// exit...
#include <stdlib.h>	// exit...
#include <string.h>	// strcmp, strtok...
#include <stdbool.h>	// true, false...

#define MAX_CMD_LEN 2048
#define MAX_TOK_CNT 16

extern bool read_command(char *);

int main(void)
{
	char buffer[MAX_CMD_LEN + 1];

	printf("Type \"quit\", \"exit\" or [Ctrl-D] to exit shell\n");

	while (read_command(buffer))
	{
		char *argv[MAX_TOK_CNT];
		int token_count = 0;

		argv[token_count] = strtok(buffer, " ");

		while (argv[token_count] != NULL)
		{
			token_count++;
			argv[token_count] = strtok(NULL, " ");
		}
	}

	exit(0);
}

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
