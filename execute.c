#include "main.h"
/**
 * executeCommand - executes a command
 * @cmd: command to execute
 * @args: arguments passed
 * Return: Always 0.
 */
void executeCommand(char *cmd, char **args)
{
	int last_exit_status = 0;
	pid_t pid;
	int status;

	pid = fork();/*creates a process*/
	if (pid == 0)/*child process*/
	{
		execve(cmd, args, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else/*parent process*/
	{
		waitpid(pid, &status, 0);/*waits for the child*/
		last_exit_status = WEXITSTATUS(status);
	}
}
