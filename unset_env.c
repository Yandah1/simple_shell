#include "shell.h"

/**
 * _isunsetenv - finds if the command is unsetenv
 * @p: an array of string
 * @myenv: copy of environmental variables
 * @loop: the current loopr
 * @v: arguments in input
 * @e: a pointer to integer represebting myenv
 * Return: -1 if fails or 0 if success
 */
int _isunsetenv(char **p, char **myenv, int *e, int loop, char *v[])
{
	char str[] = "unsetenv";
	int i = 0, count = 0, outcome = -1;

	i = 0;
	while (p[0][i] != '\0')
	{
		if (i < 8)
		{
			if (p[0][i] == str[i])
				count++;
		}
		i++;
	}
	if (i == 8)
		count++;
	if (count == 9)
	{
		if (p[1] != NULL)
			_unsetenv(p, myenv, e, loop, v);
		else
			_put_err(p, loop, 5, v);
		outcome = 0;
		currentstatus(&outcome);
	}
	else if (count == 8)
	{
		outcome = 0;
		_put_err(p, loop, 3, v);
		currentstatus(&outcome);
	}
	return (outcome);
}
/**
 * _unsetenv - function thast unset an environment variable
 * @p: array of pointers
 * @myenv: icopy of environmental
 * @loop: current loop
 * @v: an array of string representing command history
 * @e: number of elements in myenv
 */
void _unsetenv(char **p, char **myenv, int *e, int loop, char *v[])
{
	int i, lg, j, kd = 0, kd2 = 0, kd3 = 0, count = 0;

	lg = _strlen(p[1]);
	for (i = 0; myenv[i] != NULL; i++, count = 0)
	{
		for (j = 0; p[1][j] != '\0' && j < lg; j++)
		{
			if (p[1][j] == myenv[i][j])
				count++;
		}
		if (count == lg)
			break;
	}
	if (count == lg)
	{
		for (kd = i; myenv[kd] != NULL && myenv[kd + 1] != NULL; kd++)
		{
			for (kd2 = 0; myenv[kd][kd2] != '\0'; kd2++)
				myenv[kd][kd2] = 0;
			for (kd3 = 0; myenv[kd + 1][kd3] != '\0'; kd3++)
				;
			if (kd2 < kd3)
				myenv[kd] = _realloc(myenv[kd], kd2, kd3);
			for (kd2 = 0; myenv[kd + 1][kd2] != '\0'; kd2++)
				myenv[kd][kd2] = myenv[kd + 1][kd2];
		}
		free(myenv[kd]);
		myenv[kd] = NULL;
		*e = *e - 1;
		free(myenv[kd + 1]);
	}
	else
		_put_err(p, loop, 5, v);
}

