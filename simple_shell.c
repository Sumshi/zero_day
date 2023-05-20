#include "main.h"
/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
	char buffer[BUFFER_SIZE];
	ssize_t length;/*stores length of user input*/
	int status;/*stores status of a process*/
	int clear_requested = 0;/*indicates if a clear screen is reguested*/
	char *cmd;/*stores commands to be executed*/
	char *msg;/*stores error messages*/
	int i;
	/*args stores arguments passed to the shell*/
	char *args[MAX_ARGS + 1]; /* 1 for null terminator */
	while (1)/*infinite loop*/
	{
		if (clear_requested)
		{
			clear();
			clear_requested = 0;/*resets the flag to 0 everytime*/
		}
		printPrompt();/*displays a prompt*/
		length = read(STDIN_FILENO, buffer, BUFFER_SIZE);/*stores number of characters read*/
		if (length == -1)
		{
			perror("Error from read");
			exit(EXIT_FAILURE);
		}
		if (length == 0)/*checks if end of file has been reached*/
		{
			break;/*end of file*/
		}
		if (buffer[length - 1] == '\n')
		{/*REMOVES NEW LINE*/
			buffer[length - 1] = '\0';
		}
		parseInput(buffer, args);/*tokenizes the commands passed*/
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
		continue;
	}
	return (0);
}
