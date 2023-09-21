#include "shell.h"

/**
 * main - simple shell
 *
 * Return: success or error message.
 */

void copy_ls_binary(void);
void execute_shell(void);

int main(void)
{
	copy_ls_binary();
	execute_shell();
	return (EXIT_SUCCESS);
}

/**
 * copy_ls_binary - Copy the ls binary to hbtn_ls.
 */

void copy_ls_binary(void)
{
	int copy_result = system("cp /bin/ls hbtn_ls");

	if (copy_result != 0)
	{
		perror("Copy error");
		exit(EXIT_FAILURE);
	}
}

/**
 * execute_shell - Execute the main logic of the shell.
 */

void execute_shell(void)
{
	char *user_input;
	bool from_pipe = false;
	int i;

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
				exit(EXIT_SUCCESS);
			}

			process_id = fork();
			if (process_id == -1)
			{
				perror("Process creation error");
				free(user_input);
				exit(EXIT_FAILURE);
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
}
