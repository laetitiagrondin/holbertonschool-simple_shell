#include "shell.h"
/**
 * exec - Function that executes a command with its arguments
 * @args: an array of command arguments
 */
void exec(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
	{
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("shell");
			exit(1);
		}
	}
	else if (pid > 0)
	{
		wait(&status);
	}
	else
	{
		perror("fork");
	}
}

/**
 * main - Entry point
 * @argc: number of arguments
 * @argc: array of argument strings
 * Return: 0 (Success), 1 (Error)
 */
int main(int argc, char **argv)
{
	char *command[] = {"ls", "-l", NULL};

	(void)argc;
	(void)argv;
	exec(command);
	return (0);
}
