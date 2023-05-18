#include "main.h"
/**
 * changeDirectory - changes a directory
 * @directory: directory to change from or to
 * Return: retur 0
 */
int changeDirectory(char *directory)
{
	char *msg;
	char cwd[BUFFER_SIZE];
	char newCwd[BUFFER_SIZE];

	if (directory == NULL || _strcmpr(directory, "~") == 0)
	{
		directory = getenv("HOME");
	}
	if (_strcmpr(directory, "-") == 0)
	{
		directory = getenv("OLDPWD");
		msg = "Changing to previous directory: ";
		write(STDOUT_FILENO, msg, _strlen(msg));
		write(STDOUT_FILENO, directory, _strlen(directory));
		write(STDOUT_FILENO, "\n", 1);
	}
	getcwd(cwd, BUFFER_SIZE);/*Get current working directory*/

	if (chdir(directory) != 0)
	{/*Change the directory*/
		perror("cd error");
		return (-1);
	}
	getcwd(newCwd, BUFFER_SIZE);/*Get new current working directory*/

	setenv("OLDPWD", cwd, 1);/*Set OLDPWD environment variable*/
	setenv("PWD", newCwd, 1);/*Set PWD environment variable*/

	return (0);
}
