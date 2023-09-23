#include "shell.h"

/**
 * read_user_input - Read user input from stdin.
 *
 * Return: The user input as a string or NULL on error.
 */
char *read_user_input(void)
{
	ssize_t bytes;
	char *input = NULL;
	size_t buffer_size = 0;

	write(STDOUT_FILENO, "$ ", 2);
	bytes = getline(&input, &buffer_size, stdin);
	if (bytes == -1)
	{
		
		free(input);
		return (NULL);
	} 
	
	return (input);
}
