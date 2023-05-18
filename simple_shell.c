#include "main.h"
/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main()
{
	char buffer[BUFFER_SIZE];
	ssize_t length;
	int status;
	int clear_requested = 0;
	char *cmd;
	char *msg;
	char *args[MAX_ARGS + 1]; /* 1 for null terminator */
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)/*reads from terminal*/
		{
			if (clear_requested)
			{
				clear();
				clear_requested = 0;
			}
			write(STDOUT_FILENO, "$ ", 2);
			length = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (length == -1)
			{
				perror("Error from read");
				exit(EXIT_FAILURE);
			}
			if (length == 0)
			{
				break;/*end of file*/
			}
			if (buffer[length - 1] == '\n')
			{/*REMOVES NEW LINE*/
				buffer[length - 1] = '\0';
			}
			parseInput(buffer, args);
			if (_strcmpr(args[0], "exit") == 0)
			{/*Handle exit command*/
				status = EXIT_SUCCESS;
				if (args[1] != NULL)
				{/*If argument is provided*/
					status = _atoi(args[1]);/*Convert to integer*/
				}
				exit(status);/*Exit the shell with given status*/
			}
			else if (_strcmpr(args[0], "env") == 0)
			{/*Handle env command*/
				printEnv();
				continue;
			}
			else if (_strcmpr(args[0], "cd") == 0)
			{/*Handle cd command*/
				if (changeDirectory(args[1]) != 0)
				{
					continue;
				}
			}
			else if (_strcmpr(args[0], "setenv") == 0)
			{/*Handle setenv command*/
				if (args[1] == NULL || args[2] == NULL)
				{
					msg = "Usage: setenv VARIABLE VALUE\n";
					write(STDOUT_FILENO, msg, _strlen(msg));
					continue;
				}
				if (mySetEnv(args[1], args[2]) != 0)
				{
					continue;
				}
			}
			else if (_strcmpr(args[0], "unsetenv") == 0)
			{/*Handle unsetenv command*/
				if (args[1] == NULL)
				{
					msg = "Usage: unsetenv VARIABLE\n";
					write(STDOUT_FILENO, msg, _strlen(msg));
					continue;
				}
				if (myUnsetEnv(args[1]) != 0)
				{
					continue;
				}
			}
			else if (_strcmpr(args[0], "clear") == 0)
			{
				clear_requested = 1;/*executes clear()*/
			}
			else
			{
				cmd = getAbsolutePath(args[0]);
				if (cmd == NULL)
				{
					msg = ": command not found\n";
					write(STDOUT_FILENO, args[0], _strlen(args[0]));
					write(STDOUT_FILENO, msg, _strlen(msg));
				}
				else
				{
					executeCommand(cmd, args);
				}

				free(cmd);
			}
			continue; // Move the continue statement to the end of the loop body
		}
	}
	return (0);
}
