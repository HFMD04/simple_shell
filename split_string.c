#include "shell.h"

/**
 * split_string - Split a string into an array of tokens.
 *
 * @input: The input string to split.
 * @delimiter: The delimiter used to split the string.
 * @argc: A pointer to store the number of tokens.
 *
 * Return: An array of strings (tokens) or NULL on error.
 */

char **split_string(char *input, const char *delimiter, int *argc)
{
	char **tokens = NULL;
	char *token;
	int count = 0;
	int i;
	char *tmp = NULL;

	if (input == NULL || delimiter == NULL || argc == NULL)
		return (NULL);
	
	tmp = strdup(input);
	token = strtok(tmp, delimiter);
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delimiter);
	}
	free(tmp);

	tokens = malloc(sizeof(char *) * (count + 1));
	count = 0;

	token = strtok(input, delimiter);
	while (token != NULL)
	{
		tokens[count] = strdup(token);
		if (tokens[count] == NULL)
		{
			perror("Memory allocation error");
			for (i = 0; i < count; i++)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}
		count++;
		token = strtok(NULL, delimiter);
	}
	free(input);
	tokens[count] = NULL;
	*argc = count;
	return (tokens);
}

