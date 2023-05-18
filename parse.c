#include "main.h"
/**
 * parseInput - tokenizes the input
 * @buffer: stores the command
 * @args: arguments passes
 * Return: Always 0.
 */
void parseInput(char *input, char **args)
{
	int last_exit_status = 0;
	char *token;
	int i = 0;
	int j;
	char pid[10];
	char exit_status[10];
	token = _strtok(input, " ");
	while (token != NULL)
	{
		if (token[0] == '#')
		{
			break;
		}
		args[i++] = token;
		token = _strtok(NULL, " ");
	}
	args[i] = NULL;
	/*Replace $?, $$ and $PATH variables*/
	for (j = 0; args[j] != NULL; j++)
	{
		if (_strcmpr(args[j], "$?") == 0)
		{
			_sprintf(exit_status, "%d", last_exit_status);
			args[j] = _strdup(exit_status);
		}
		else if (_strcmpr(args[j], "$$") == 0)
		{
			_sprintf(pid, "%d", getpid());
			args[j] = _strdup(pid);
		}
		else if (_strcmpr(args[j], "$PATH") == 0)
		{
			args[j] = _strdup(getenv("PATH"));
		}
	}
}
