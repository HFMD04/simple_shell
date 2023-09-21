#include "shell.h"

/**
 * main - simple shell
 *
 * Return: success or error message.
 */
int main(void)
{
	char *user_input;
	bool from_pipe = false;
	int i;
	int copy_result = system("cp /bin/ls hbtn_ls");

	if (copy_result != 0)
	{
		perror("Copy error");
		exit(EXIT_FAILURE);
	}	
	for (i = 0; i < 3; i++)
	{
		while (!from_pipe)
		{
			pid_t process_id;
			if (isatty(STDIN_FILENO) == 0)
				from_pipe = true;
			user_input = read_user_input();
			if (user_input == NULL)
			{
				return (EXIT_SUCCESS);
			}

			process_id = fork();
			if (process_id == -1)
			{
				perror("Process creation error");
				free(user_input);
				return (EXIT_FAILURE);
			}
			else if (process_id == 0)
			{
				execute_command(user_input);
				free(user_input);
				exit(EXIT_SUCCESS);
			}
			else
			{
				waitpid(process_id, NULL, 0);
			}
			free(user_input);
		}
	}
	return (EXIT_SUCCESS);
}

