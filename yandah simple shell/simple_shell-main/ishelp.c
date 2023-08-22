#include "shell.h"
/**
 * _ishelp - if args[0] is help builtin
 * @pointer: Enter  pointer varables
 * @loop: counts number of loops
 * @v: Enter input
 * @m: copy of environment variables
 * Return: 0 if help exist or -1 if not.
 */
int _ishelp(char **pointer, int loop, char *v[], char **m)
{
	char str[] = "help";
	int i = 0, count = 0, outcome = -1;

	while (pointer[0][i])
	{
		if (i < 4)
		{
			if (pointer[0][i] == str[i])
				count++;
		}
		i++;
	}
	if (i == 4)
		count++;

	if (count == 5)
	{
		_help(pointer, loop, v, m);
		outcome = 0;
	}
	return (outcome);
}
/**
 * _help_builtin - builtin function
 * @pointer: enter pointer
 * @loop: counts number of loops
 * @v: Enter input
 * @m: variables of the environment
 * Return: 0
 */
void _help_builtin(char **pointer, int loop, char *v[], char **m)
{
	char str1[3] = "cd", str2[5] = "exit", str3[5] = "help";
	int i = 0, j = 0, count = 0, count2 = 0, k = 1;

	while (pointer[k] != NULL)
	{
		j = 0;
		count = 0, count2 = 0;
		while (pointer[k][j] != '\0')
			j++;
		if (j == 2)
		{
			for (i = 0; i < 2; i++)
				if (pointer[k][i] == str1[i])
					count++;
			if (count == 2)
				read_cdhelp(m);
			else
				_put_err(pointer, loop, 1, v);
		}
		else if (j == 4)
		{
			for (i = 0 ; i < 4; i++)
				if (pointer[k][i] == str2[i])
					count++;
			if (count == 4)
				read_exithelp(m);
			for (i = 0 ; i < 4; i++)
				if (pointer[k][i] == str3[i])
					count2++;
			if (count2 == 4)
				read_helphelp(m);
			else if (count != 4 && count2 != 4)
				_put_err(pointer, loop, 1, v);
		}
		else
			_put_err(pointer, loop, 1, v);
		k++;
	}
}
/**
* _help- handle the "help" command
* @pointer: the command arguments
* @loop: counnts number of  loops
* @v: array of input
* @m: environment variables
* Return: 0
*/
void _help(char **pointer, int loop, char *v[], char **m)
{
	if (pointer[0] != NULL && pointer[1] == NULL)
	{
		read_help(m);
	}
	else
	{
		_help_builtin(pointer, loop, v, m);
	}
}
