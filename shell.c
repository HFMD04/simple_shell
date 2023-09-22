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
	int source_fd, dest_fd;
	ssize_t bytes_read, bytes_written;
	char buffer[1024];

	source_fd = open("/bin/ls", O_RDONLY);
	if (source_fd == -1)
	{
		perror("Failed to open /bin/ls");
		exit(EXIT_FAILURE);
	}

	dest_fd = open("hbtn_ls", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (dest_fd == -1)
	{
		perror("Failed to create hbtn_ls");
		close(source_fd);
		exit(EXIT_FAILURE);
	}

	while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(dest_fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			perror("Failed to write to hbtn_ls");
			close(source_fd);
			close(dest_fd);
			exit(EXIT_FAILURE);
		}
	}

	if (bytes_read == -1)
	{
		perror("Failed to read from /bin/ls");
		close(source_fd);
		close(dest_fd);
		exit(EXIT_FAILURE);
	}

	close(source_fd);
	close(dest_fd);
}


/**
 * execute_shell - Execute the main logic of the shell.
 */

void execute_shell(void)
{
	char *user_input;
	pid_t process_id;
	while (1)

	{
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
			free(user_input);
		}
	}
}
