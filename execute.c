#include "main.h"
#include "main.h"
/**
 * executeCommand - executes a command
 * @cmd: command to execute
 * @args: arguments passed
 * Return: Always 0.
 */
void executeCommand(char *cmd, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(cmd, args, NULL);
		perror("execve error");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
