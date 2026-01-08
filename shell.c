#include "shell.h"

extern char **environ;

/**
 * split_line - split a command line into arguments
 * @line: input string
 *
 * Return: NULL-terminated array of arguments
 */
char **split_line(char *line)
{
	int bufsize = 64, pos = 0;
	char **args = malloc(bufsize * sizeof(char *));
	char *token;

	if (!args)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " \t\r\n");
	while (token)
	{
		args[pos++] = token;
		if (pos >= bufsize)
		{
			bufsize += 64;
			args = realloc(args, bufsize * sizeof(char *));
			if (!args)
			{
				perror("allocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, " \t\r\n");
	}
	args[pos] = NULL;
	return (args);
}

/**
 * execute_command - fork and execute a command with arguments
 * @args: array of command and arguments
 * @prog_name: name of the shell (argv[0])
 * @line_num: current line number for error messages
 *
 * Return: void
 */
void execute_command(char **args, char *prog_name, int line_num)
{
	pid_t pid;
	int status;

	if (!args[0])
		return;

	/* handle built-in exit */
	if (strcmp(args[0], "exit") == 0)
		exit(0);

	pid = fork();
	if (pid == -1)
	{
		perror(prog_name);
		return;
	}

	if (pid == 0)
	{
		execve(args[0], args, environ);
		fprintf(stderr, "%s: %d: %s: not found\n",
			prog_name, line_num, args[0]);
		_exit(127);
	}
	else
		wait(&status);
}

/**
 * main - simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int interactive;
	int line_num = 0;
	char **args;

	(void)argc;
	interactive = isatty(STDIN_FILENO);

	while (1)
	{
		line_num++;

		if (interactive)
			write(STDOUT_FILENO, "($) ", 4);

		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			if (interactive)
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		if (line[read - 1] == '\n')
			line[read - 1] = '\0';

		if (line[0] == '\0')
			continue;

		args = split_line(line);
		execute_command(args, argv[0], line_num);
		free(args);
	}

	free(line);
	return (0);
}
