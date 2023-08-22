#include "shell.h"

/**
 * _issetenv - checck if command is "setenv"
 * @p: array of pointers
 * @myenv: pointer to number of environmental variables
 * @loop: current loop iteration
 * @e: number of elements in m
 * @v: arguments
 * Return: -1 if fails or 0 if success
 */
int _issetenv(char **p, char ***myenv, int *e, int loop, char *v[])
{
	char str[] = "setenv";
	int i = 0, count = 0, outcome = -1;

	i = 0;
	while (p[0][i] != '\0')
	{
		if (i < 6)
		{
			if (p[0][i] == str[i])
				count++;
		}
		i++;
	}
	if (i == 6)
		count++;
	if (count == 7)
	{
		if (p[1] != NULL && p[2] != NULL)
			_setenv(p, myenv, e, loop, v);
		else
			_put_err(p, loop, 5, v);
		outcome = 0;
		currentstatus(&outcome);
	}
	else if (count == 6)
	{
		outcome = 0;
		_put_err(p, loop, 3, v);
		currentstatus(&outcome);
	}
	return (outcome);
}

/**
 * _setenv - sets an environment variable
 * environ points to an array of pointers to strings called the "environment"
 * @myenv: icopy of environmental
 * @loop: current loop iteration
 * @p: array of command line arguments
 * @e: number of elements in m
 * @v: arguments
 */
void _setenv(char **p, char ***myenv, int *e, int loop, char *v[])
{
	int i, lg, j, kd = 0, count = 0, p2len = 0, myenvlen = 0;
	char *entirenv, *withequal;

	lg = _strlen(p[1]);
	withequal = str_concat(p[1], "=");
	entirenv = str_concat(withequal, p[2]);
	for (i = 0; (*myenv)[i] != NULL; i++, count = 0)
	{
		for (j = 0; p[1][j] != '\0' && j < lg; j++)
		{
			if (p[1][j] == (*myenv)[i][j])
				count++;
		}
		if (count == lg)
			break;
	}
	if (count == lg)
	{
		myenvlen = _strlen((*myenv)[i]), p2len = _strlen(p[2]);
		if (p2len < myenvlen)
		{
			for (kd = 0; entirenv[kd] != '\0'; kd++)
				(*myenv)[i][kd] = entirenv[kd];
			for (; kd < myenvlen; kd++)
				(*myenv)[i][kd] = 0;
		}
		else
		{
			(*myenv)[i] = _realloc((*myenv)[i], myenvlen, _strlen(entirenv));
			for (kd = 0; entirenv[kd] != '\0'; kd++)
				(*myenv)[i][kd] = entirenv[kd];
		} free(withequal), free(entirenv), *e = *e;
	}
	else if (count != lg && p[1] != NULL && p[2] != NULL)
	{
		_setenvcreat(myenv, e, entirenv);
		free(withequal), free(entirenv);
	}
	else
		_put_err(p, loop, 5, v);
}
/**
 * _setenvcreat - add or modify an environment variable
 * environ: points to an array of pointers to strings called the "environment"
 * @myenv: pointer environmental variable array
 * @e: number of elements in m
 * @entirenv: concatenate arguments
 */
void _setenvcreat(char ***myenv, int *e, char *entirenv)
{
	int i = 0, kd = 0;
	char **new = NULL;

	new = _calloc(*e + 2, sizeof(char *));
	for (i = 0; (*myenv)[i] != NULL; i++)
	{
		for (kd = 0; (*myenv)[i][kd]; kd++)
			;
		new[i] = _calloc(kd + 1, sizeof(char));
		for (kd = 0; (*myenv)[i][kd] != '\0'; kd++)
			new[i][kd] = (*myenv)[i][kd];
	}
	new[i] = _calloc(_strlen(entirenv) + 1, sizeof(char));
	for (kd = 0; entirenv[kd] != '\0'; kd++)
		new[i][kd] = entirenv[kd];
	new[i + 1] = NULL;
	*e = *e + 1;
	free_grid((*myenv), *e);
	(*myenv) = new;
}
