#include "main.h"
/**
 * parseInput - divides a command into command and arguments
 * @buffer: stores the command
 * @args: arguments passes
 * Return: Always 0.
 */
void parseInput(char *buffer, char **args)
{
	int last_exit_status = 0;/*stores last exit status of a command*/
	char *token;/*stores each token during tokenization*/
	int i = 0;/*counter for args array*/
	int j;/*iterates over args*/
	char pid[10];
	char exit_status[10];
	token = _strtok(buffer, " ");/*tokenizes using a space*/
	while (token != NULL)
	{
		if (token[0] == '#')/*checks if the first character of token is #*/
		{
			break;/*since it is a comment it breaks out of the loop*/
		}
		args[i++] = token;/*increments to the next*/
		token = _strtok(NULL, " ");
	}
	args[i] = NULL;
	/*Replace $?, $$ and $PATH variables*/
	for (j = 0; args[j] != NULL; j++)
	{
		if (_strcmpr(args[j], "$?") == 0)
		{/*it replaces the value of last exit and it becomes exit status value*/
			_sprintf(exit_status, "%d", last_exit_status);
			args[j] = _strdup(exit_status);
		}
		else if (_strcmpr(args[j], "$$") == 0)/*gets process id*/
		{
			_sprintf(pid, "%d", getpid());/*stores value of $$ in pid*/
			args[j] = _strdup(pid);/*stores a copy*/
		}
		else if (_strcmpr(args[j], "$PATH") == 0)
		{
			args[j] = _strdup(getenv("PATH"));
		}/*args are replaced with duplicates of the value*/
	}
}
