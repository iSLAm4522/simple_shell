#include "main.h"

/**
* is_command_executable - Checks if a command is executable
* @command: The command to check
*
* Return: 1 if executable, 0 otherwise
*/
static int is_command_executable(char *command)
{
	struct stat st;

	if (!command)
		return (0);

	if (stat(command, &st) == -1)
		return (0);

	if (!S_ISREG(st.st_mode))
		return (0);

	if (!(st.st_mode & S_IXUSR))
		return (0);

	return (1);
}


/**
* search_in_path - Searches for command in PATH directories
* @path_copy: Copy of PATH environment variable
* @command: The command name to search for
*
* Return: Full path to the command if found, NULL otherwise
*/
static char *search_in_path(char *path_copy, char *command)
{
	char *dir;
	char full_path[1024];

	dir = strtok(path_copy, ":");
	while (dir)
	{
		size_t len_dir = string_length(dir);
		size_t len_cmd = string_length(command);

		if (len_dir + len_cmd + 2 > sizeof(full_path))
		{
			dir = strtok(NULL, ":");
			continue;
		}
		string_copy(full_path, dir);
		string_concat(full_path, "/");
		string_concat(full_path, command);
		if (is_command_executable(full_path))
			return (string_duplicate(full_path));
		dir = strtok(NULL, ":");
	}
	return (NULL);
}

/**
* find_command_path - Searches for the full path of a command in PATH
* @command: The command name to search for
*
* Return: Full path to the command if found, NULL otherwise
*/
char *find_command_path(char *command)
{
	char *path_env = get_env_var("PATH");
	char *path_copy;
	char *result;

	if (!command)
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (is_command_executable(command))
			return (string_duplicate(command));
		return (NULL);
	}
	if (!path_env)
		return (NULL);

	path_copy = string_duplicate(path_env);
	if (!path_copy)
		return (NULL);

	result = search_in_path(path_copy, command);
	free(path_copy);
	return (result);
}
