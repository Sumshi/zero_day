#include "main.h"
/**
 * getAbsolutePath - gets the absolute path of a command
 * @command: command to execute
 * Return: Always 0.
 */
char *getAbsolutePath(char *command)
{

	char *pathDirectory[MAX_ARGS + 2];
	int numDirectory = 0;
	int i;
	char *token;
	char tempCmd[BUFFER_SIZE];
	char *pathEnvVar;

	if (command[0] == '/')
	{
		return (_strdup(command));
	}
	pathDirectory[numDirectory++] = "/bin";/*add /bin to search path*/
	pathEnvVar = getenv("PATH");
	token = _strtok(pathEnvVar, ":");
	while (token != NULL)
	{
		pathDirectory[numDirectory++] = token;
		if (numDirectory >= MAX_ARGS + 1)
		{/*increase size check accordingly*/
			break;
		}
		token = _strtok(NULL, ":");
	}
	pathDirectory[numDirectory] = NULL;
	for (i = 0; i < numDirectory; i++)
	{
		snprintf(tempCmd, BUFFER_SIZE, "%s/%s", pathDirectory[i], command);
		if (access(tempCmd, X_OK) == 0)
		{
			return (_strdup(tempCmd));
		}
	}
	return (NULL);
}
