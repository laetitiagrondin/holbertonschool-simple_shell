#include "shell.h"
/**
 * find_path - Finds the full path of a command in the directories listed
 * in the PATH environment variable
 * @command: the name of the command to search for
 * Return: Its full path if found and executable;
 * otherwise, it returns NULL
 */
char *find_path(char *command)
{
	char *path_env = getenv("PATH");
	char *dir = NULL;
	char *full_path = NULL;
	char *path_copy = NULL;

	if (path_env == NULL)
		return (NULL);
	path_copy = strdup(path_env);
	if (path_copy == NULL)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		full_path = malloc(strlen(dir) + strlen(command) + 2);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		sprintf(full_path, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return(full_path);
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return(NULL);
}

/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: array of argument strings
 * Return: 0 (Success)
 */
int main(int argc, char **argv)
{
	char *command = "ls";
	char *path = NULL;

	(void)argc;
	(void)argv;
	path = find_path(command);
	if (path != NULL)
	{
		printf("Full path to '%s' : %s", command, path);
		free(path);
	}
	else
	{
		printf("The command '%s' does not exist in PATH\n", command);
	}
	return (0);
}
