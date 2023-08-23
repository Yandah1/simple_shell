#include "shell.h"
/**
 * path_execute - function that executes a command in the path
 * @command: full path
 * @shell_vars: pointer to struct of variables
 * Return: 0 on success, 1 on failure
 */
int path_execute(char *command, vars_t *shell_vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error(shell_vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, shell_vars->av, shell_vars->env) == -1)
				print_error(shell_vars, NULL);
		}
		else
		{
			wait(&shell_vars->status);
			if (WIFEXITED(shell_vars->status))
				shell_vars->status = WEXITSTATUS(shell_vars->status);
			else if (WIFSIGNALED(shell_vars->status) && WTERMSIG(shell_vars->status) == SIGINT)
				shell_vars->status = 130;
			return (0);
		}
		shell_vars->status = 127;
		return (1);
	}
	else
	{
		print_error(shell_vars, ": Permission denied\n");
		shell_vars->status = 126;
	}
	return (0);
}
/**
 * find_path - function that finds the PATH variable
 * @env: array of environment variables
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i, j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			if (path[j] != env[i][j])
				break;
		if (j == 5)
			break;
	}
	return (env[i]);
}
/**
 * check_for_path - functon that checks if the command is in the PATH
 * @shell_vars: shell variables
 * Return: void
 */
void check_for_path(shell_vars_t *shell_vars)
{
	char *path, *path_dup = NULL, *check = NULL;
	unsigned int i = 0, r = 0;
	char **path_tokens;
	struct stat buf;

	if (check_for_dir(shell_vars->av[0]))
		r = execute_cwd(shell_vars);
	else
	{
		path = find_path(shell_vars->env);
		if (path != NULL)
		{
			path_dup = _strdup(path + 5);
			path_tokens = tokenize(path_dup, ":");
			for (i = 0; path_tokens && path_tokens[i]; i++, free(check))
			{
				check = _strcat(path_tokens[i], shell_vars->av[0]);
				if (stat(check, &buf) == 0)
				{
					r = path_execute(check, shell_vars);
					free(check);
					break;
				}
			}
			free(path_dup);
			if (path_tokens == NULL)
			{
				shell_vars->status = 127;
				new_exit(shell_vars);
			}
		}
		if (path == NULL || path_tokens[i] == NULL)
		{
			print_error(shell_vars, ": not found\n");
			shell_vars->status = 127;
		}
		free(path_tokens);
	}
	if (r == 1)
		new_exit(shell_vars);
}
/**
 * execute_cwd - function executes the command in the current working directory
 * @shell_vars: pointer to struct of shell variables
 * Return: 0 on success, 1 on failure
 */
int execute_cwd(vars_t *shell_vars)
{
	pid_t child_pid;
	struct stat buf;

	if (stat(shell_vars->av[0], &buf) == 0)
	{
		if (access(shell_vars->av[0], X_OK) == 0)
		{
			child_pid = fork();
			if (child_pid == -1)
				print_error(shell_vars, NULL);
			if (child_pid == 0)
			{
				if (execve(shell_vars->av[0], shell_vars->av, shell_vars->env) == -1)
					print_error(shell_vars, NULL);
			}
			else
			{
				wait(&shell_vars->status);
				if (WIFEXITED(shell_vars->status))
					shell_vars->status = WEXITSTATUS(shell_vars->status);
				else if (WIFSIGNALED(shell_vars->status) && WTERMSIG(shell_vars->status) == SIGINT)
					shell_vars->status = 130;
				return (0);
			}
			shell_vars->status = 127;
			return (1);
		}
		else
		{
			print_error(shell_vars, ": Permission denied\n");
			shell_vars->status = 126;
		}
		return (0);
	}
	print_error(vars, ": not found\n");
	shell_vars->status = 127;
	return (0);
}
/**
 * check_for_dir - function checks if the command is a part of a path
 * @str: command
 * Return: 1 on success, 0 on failure
 */
int check_for_dir(char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == '/')
			return (1);
	}
	return (0);
}
