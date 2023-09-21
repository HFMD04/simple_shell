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
	if (bytes <= 0)
	{
		if (feof(stdin))
		{
			free(input);
			 exit(EXIT_FAILURE);
		}
		else
		{
			perror("Input reading error");
			free(input);
			return (NULL);
		}
	}
	
	if (input == NULL)
	{
		return (NULL);
	}
	input[strcspn(input, "\n")] = '\0';
	return (input);
}
