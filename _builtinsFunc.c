#include "shell.h"

/**
 * check_for_builtin_commands - checks if the command is a builtin
 * @shell_vars: shell variables
 * Return: pointer to the function or NULL
 */
typedef void (*builtin_func_ptr_t)(shell_vars_t *shell_vars);

builtin_func_ptr_t check_for_builtin_commands(shell_vars_t *shell_vars);
{
	unsigned int i;
	builtin_command_t check[] = {
		{"exit", new_exit_command},
		{"env", _env_command},
		{"setenv", new_setenv_command},
		{"unsetenv", new_unsetenv_command},
		{NULL, NULL}
	};

	for (i = 0; check[i].f != NULL; i++)
	{
		if (_strcmpr(shell_vars->arguments[0], check[i].name) == 0)
			break;
	}
	if (check[i].f != NULL)
		check[i].f(shell_vars);
	return (check[i].f);
}

/**
 * new_exit_command - exit program
 * @shell_vars: shell variables
 * Return: void
 */
void new_exit_command(shell_vars_t *shell_vars)
{
	int status;

	if (_strcmpr(shell_vars->arguments[0], "exit") == 0 &&
			shell_vars->arguments[1] != NULL)
	{
		status = _atoi(shell_vars->arguments[1]);
		if (status == -1)
		{
			shell_vars->status = 2;
			print_error(shell_vars, ": Illegal number: ");
			_puts2(shell_vars->arguments[1]);
			_puts2("\n");
			free(shell_vars->commands);
			shell_vars->commands = NULL;
			return;
		}
		shell_vars->status = status;
	}
	free(shell_vars->buffer);
	free(shell_vars->arguments);
	free(shell_vars->commands);
	free_env(shell_vars->env);
	exit(shell_vars->status);
}

/**
 * _env_command - prints the current environment
 * @shell_vars: shell variables
 * Return: void.
 */
void _env_command(shell_vars_t *shell_vars)
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
 * new_setenv_command - create a new environment variable,
 * or edit an existing variable
 * @shell_vars: shell variables
 *
 * Return: void
 */
void new_setenv_command(shell_vars_t *shell_vars)
{
	char **key;
	char *var;

	if (shell_vars->arguments[1] == NULL || shell_vars->arguments[2] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	key = find_key(shell_vars->env, shell_vars->arguments[1]);
	if (key == NULL)
		add_key(shell_vars);
	else
	{
		var = add_value(shell_vars->arguments[1], shell_vars->arguments[2]);
		if (var == NULL)
		{
			print_error(shell_vars, NULL);
			free(shell_vars->buffer);
			free(shell_vars->commands);
			free(shell_vars->arguments);
			free_env(shell_vars->env);
			exit(127);
		}
		free(*key);
		*key = var;
	}
	shell_vars->status = 0;
}

/**
 * new_unsetenv_command - remove an environment variable
 * @shell_vars: shell variables
 *
 * Return: void
 */
void new_unsetenv_command(shell_vars_t *shell_vars)
{
	char **key, **newenv;
	unsigned int i, j;

	if (shell_vars->arguments[1] == NULL)
	{
		print_error(shell_vars, ": Incorrect number of arguments\n");
		shell_vars->status = 2;
		return;
	}
	key = find_key(shell_vars->env, shell_vars->arguments[1]);
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
		new_exit_command(shell_vars);
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

