#include "main.h"
/**
 * parseInput - tokenizes the input
 * @buffer: stores the command
 * @args: arguments passes
 * Return: Always 0.
 */
void parseInput(char *buffer, char **args)
{
	int argCount = 0;
	char *token = _strtok(buffer, " ");

	while (token != NULL)
	{
		args[argCount++] = token;
		if (argCount >= MAX_ARGS)
		{
			break;
		}
		token = _strtok(NULL, " ");
	}
	args[argCount] = NULL;
}
