#include "shell.h"

/**
 * execute_command - Execute a command using execve.
 *
 * @command: The command to execute.
 */
void execute_command(char **command)
{

	if (execve(command[0], command, environ) == -1)
	{
		perror("Command execution error");
		exit(EXIT_FAILURE);
	}
}
