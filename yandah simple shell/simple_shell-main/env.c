#include "shell.h"
/**
 * _isenv - check if command  is env
 * @p: double pointer to the command and its argumentss
 * @myenv: double pointer to the environmental variables
 * Return: -1 if fails or 0 if success
 */
int _isenv(char **p, char **myenv)
{
	char str[4] = "env";
	int i = 0, j = 0, count = 0;

	while (p[0][j] != '\0')
		j++;
	if (j == 3)
	{
		while (i < 3)
		{
			if (p[0][i] == str[i])
				count++;
			i++;
		}
		if (count == 3)
		{
			_env(myenv);
			return (0);
		}
	}
	return (-1);
}
/**
 * create_env - create a copy of the environmental variables
 * @envp: array of environment variables
 * Return: Pointer to the creatyed copy, or NULL if fails.
 */
char **create_env(char *envp[])
{
	int i, j = 0, cr = 0;
	static char **myenv;

	for (i = 0; envp[i] != NULL; i++)
		;
	myenv = _calloc(i + 1, sizeof(char *));
	if (!myenv)
		return (NULL);
	while (envp[j] != NULL)
	{
		cr = 0;
		while (envp[j][cr] != '\0')
			cr++;
		myenv[j] = _calloc(cr + 1, sizeof(char));
		if (myenv[j] == NULL)
		{
			free_grid(myenv, j);
			return (NULL);
		}
		for (i = 0; i < cr; i++)
			myenv[j][i] = envp[j][i];
		j++;
	}
	myenv[j] = NULL;
	return (myenv);
}
/**
 * _env - function prints the environment variables
 * environ points to an array of pointers to strings
 * @myenv: copy of environment
 */
void _env(char **myenv)
{
	int i;

	for (i = 0; myenv[i] != NULL; i++)
	{
		write(STDOUT_FILENO, myenv[i], _strlen(myenv[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
