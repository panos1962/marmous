#include <stdio.h>	// exit...
#include <stdlib.h>	// exit...
#include <stdbool.h>	// true, false...
#include <string.h>	// strcmp, strtok...

#define MAX_CMD_LEN 2048
#define MAX_TOK_CNT 16

extern int check_exit(char *);

int main(void)
{
	char buffer[MAX_CMD_LEN + 1];
	char *argv[MAX_TOK_CNT];

	printf("Type \"quit\", \"exit\" or [Ctrl-D] to exit shell\n");

	while (true)
	{
		int token_count = 0;

		printf("Our shell: ");

		if (fgets(buffer, MAX_CMD_LEN, stdin) == NULL)
		{
			break;
		}

		buffer[strlen(buffer) - 1] = '\0';

		if (check_exit(buffer))
		{
			break;
		}

		argv[token_count] = strtok(buffer, " ");

		while (argv[token_count] != NULL)
		{
			token_count++;
			argv[token_count] = strtok(NULL, " ");
		}

	}

END:
	exit(0);
}

int check_exit(char *s)
{
	char *exit_token[] = {
		"quit",
		"exit",
		"maria",
	};
	int i;

	for (i = 0; i < sizeof(exit_token) / sizeof(exit_token[0]); i++)
	{
		if (strcmp(s, exit_token[i]) == 0)
		{
			return true;
		}
	}

	return false;
}
