#include "shell.h"

/**
 * check_for_builtins - checks if the command is a builtin
 * @Shell_vars:  shell variables
 * Return: pointer to the function or NULL
 */
void (*check_for_builtins(vars_t *shell_vars))(vars_t *shell_vars)
{
	unsigned int i;
	builtins_t check[] = {
		{"exit", new_exit},
		{"env", _env},
		{"setenv", new_setenv},
		{"unsetenv", new_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(shell_vars->av[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(shell_vars);
	return (check[i].f);
}

/**
 * new_exit - exit program
 * @shell_vars: variables
 * Return: void
 */
void new_exit(vars_t *shell_vars)
{
	int status;

	if (_strcmpr(shell_vars->av[0], "exit") == 0 && shell_vars->av[1] != NULL)
	{
		status = _atoi(shell_vars->av[1]);
		if (status == -1)
		{
			shell_vars->status = 2;
			print_error(shell_vars, ": Illegal number: ");
			_puts2(shell_vars->av[1]);
			_puts2("\n");
			free(shell_vars->commands);
			shell_vars->commands = NULL;
			return;
		}
		shell_vars->status = status;
	}
	free(shell_vars->buffer);
	frees(shell_vars->av);
	free(shell_vars->commands);
	free_env(shell_vars->env);
	exit(shell_vars->status);
}

/**
 * _env - prints the current environment
 * @shell_vars: struct of variables
 * Return: void.
 */
void _env(vars_t *shell_vars)
{
	unsigned int i;

	for (i = 0; shell_vars->env[i]; i++)
	{
		_puts(shell_vars->env[i]);
		_puts("\n");
	}
	shell_vars->status = 0;
}

/**
 * new_setenv - create a new environment variable, or edit an existing variable
 * @vars: pointer to struct of variables
 *
 * Return: void
 */
void new_setenv(vars_t *shell_vars)
{
	char **key;
	char *shell_var;

	if (shell_vars->av[1] == NULL || shell_vars->av[2] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	key = find_key(shell_vars->env, shell_vars->av[1]);
	if (key == NULL)
		add_key(shell_vars);
	else
	{
		var = add_value(shell_vars->av[1], shell_vars->av[2]);
		if (shell_var == NULL)
		{
			print_error(shell_vars, NULL);
			free(shell_vars->buffer);
			free(shell_vars->commands);
			free(shell_vars->av);
			free_env(shell_vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	shell_vars->status = 0;
}

/**
 * new_unsetenv - function that remove an environment variable
 * @shell_vars: pointer to a struct of variables
 *
 * Return: void
 */
void new_unsetenv(vars_t *shell_vars)
{
	char **key, **newenv;

	unsigned int i, j;

	if (shell_vars->av[1] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	key = find_key(shell_vars->env, shell_vars->av[1]);
	if (key == NULL)
	{
		print_error(shell_vars, ": No variable to unset");
		return;
	}
	for (i = 0; shell_vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * i);
	if (newenv == NULL)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		new_exit(shell_vars);
	}
	for (i = 0; shell_vars->env[i] != *key; i++)
		newenv[i] = shell_vars->env[i];
	for (j = i + 1; shell_vars->env[j] != NULL; j++, i++)
		newenv[i] = shell_vars->env[j];
	newenv[i] = NULL;
	free(*key);
	free(shell_vars->env);
	shell_vars->env = newenv;
	shell_vars->status = 0;
}
