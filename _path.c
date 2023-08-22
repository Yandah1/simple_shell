#include "shell.h"

/**
 * path_execute - executes a command in the path
 * @command: full path to the command
 * @shell_vars: pointer to struct of shell variables
 *
 * Return: 0 on success, 1 on failure
 */
int path_execute(char *command, shell_vars_t *shell_vars)
{
	pid_t child_pid;

	if (access(command, X_OK) == 0)
	{
		child_pid = fork();
		if (child_pid == -1)
			print_error(shell_vars, NULL);
		if (child_pid == 0)
		{
			if (execve(command, shell_vars->arguments, shell_vars->env) == -1)
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
		else
		{
			print_error(shell_vars, ": Permission denied\n");
			shell_vars->status = 126;
		}
		return (0);
	}
}


/**
 * find_path - finds the PATH variable
 * @env: array of environment variables
 *
 * Return: pointer to the node that contains the PATH, or NULL on failure
 */
char *find_path(char **env)
{
	char *path = "PATH=";
	unsigned int i,j;

	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < 5; j++)
			 if (path[j] != env[i][j])






