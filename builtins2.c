#include "shell.h"

/**
 * add_key - create a new environment variable
 * @shell_vars: pointer to struct of variables
 *
 * Return: void
 */
void add_key(vars_t *shell_vars)
{
	unsigned int i;
	char **newenv;

	for (i = 0; shell_vars->env[i] != NULL; i++)
		;
	newenv = malloc(sizeof(char *) * (i + 2));
	if (newenv == NULL)
	{
		print_error(shell_vars, NULL);
		shell_vars->status = 127;
		new_exit(shell_vars);
	}
	for (i = 0; shell_vars->env[i] != NULL; i++)
		newenv[i] = shell_vars->env[i];
	newenv[i] = add_value(shell_vars->av[1], shell_vars->av[2]);
	if (newenv[i] == NULL)
	{
		print_error(shell_vars, NULL);
		free(shell_vars->buffer);
		free(shell_vars->commands);
		free(shell_vars->av);
		free_env(shell_vars->env);
		free(newenv);
		exit(127);
	}
	newenv[i + 1] = NULL;
	free(shell_vars->env);
	shell_vars->env = newenv;
}

/**
 * find_key - function that finds an environment variable
 * @env: array of environment variables
 * @key: environment variable
 *
 * Return: pointer to address of the environment variable
 */
char **find_key(char **env, char *key)
{
	unsigned int i, j, len;

	len = _strlen(key);
	for (i = 0; env[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
			if (key[j] != env[i][j])
				break;
		if (j == len && env[i][j] == '=')
			return (&env[i]);
	}
	return (NULL);
}

/**
 * add_value - function that create a new environment variable string
 * @key: variable name
 * @value: variable value
 *
 * Return: pointer to the new string;
 */
char *add_value(char *key, char *value)
{
	unsigned int len1, len2, i, j;
	char *new;

	len1 = _strlen(key);
	len2 = _strlen(value);
	new = malloc(sizeof(char) * (len1 + len2 + 2));
	if (new == NULL)
		return (NULL);
	for (i = 0; key[i] != '\0'; i++)
		new[i] = key[i];
	new[i] = '=';
	for (j = 0; value[j] != '\0'; j++)
		new[i + 1 + j] = value[j];
	new[i + 1 + j] = '\0';
	return (new);
}

/**
 * _atoi - function converts a string into an integer
 * @str: the string
 *
 * Return: the integer value, or -1 if an error occurs
 */
int _atoi(char *str)
{
	unsigned int i, digits;
	int num = 0, num_test;

	num_test = INT_MAX;
	for (digits = 0; num_test != 0; digits++)
		num_test /= 10;
	for (i = 0; str[i] != '\0' && i < digits; i++)
	{
		num *= 10;
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
			return (-1);
		num += str[i] - '0';
		if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
			return (-1);
	}
	if (i > digits)
		return (-1);
	return (num);
}
