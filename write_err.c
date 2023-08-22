#include "shell.h"
/**
 * _put_err - prints error messeages
 * @p: the command
 * @loop: current loop
 * @sig: signal value
 * @v: an arry of command tokens
 * Return: Nothing.
 */
void _put_err(char **p, int loop, int sig, char *v[])
{
	static int per = 1;


	if (sig == 0)
		per = 0;
	per++;
	if (sig == 3)
		per = 3;
	if (sig == 4)
		per = 4;
	if (sig == 5)
		per = 5;
	if (per == 2 || (per == 3 && sig == 3) || (per == 4 && sig == 4)
	    || (per == 5 && sig == 5))
	{
		write(STDERR_FILENO, v[0], _strlen(v[0]));
		write(STDERR_FILENO, ": ", 2);
		print_number(loop);
		write(STDERR_FILENO, ": ", 2);
	}
	if (per == 2)
		_builtinerr(p);
	else if (per == 3 && sig == 3)
	{
		_errorgarbage(p);
		per = 1;
	}
	else if (per == 4 && sig == 4)
	{
		write(STDERR_FILENO, p[0], _strlen(p[0]));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	else if (per == 5 && sig == 5)
		_builtinerr2(p);
}

/**
 * _builtinerr - writes the error cases for built-in commands
 * @p:the command
 *
 * Return: nothing.
 */
void _builtinerr(char **p)
{
	char str1[3] = "cd", str2[5] = "exit", str3[5] = "help";
	int i = 0, j = 0, count = 0, count2 = 0;

	while (p[0][j] != '\0')
		j++;
	if (j == 2)
	{
		for (; i < 2; i++)
			if (p[0][i] == str1[i])
				count++;
		if (count == 2)
			_errorcd(p);
	}
	if (j == 4)
	{
		for (i = 0 ; i < 4; i++)
			if (p[0][i] == str2[i])
				count++;
		if (count == 4)
			_errorexit(p);
		for (i = 0; i < 4; i++)
			if (p[0][i] == str3[i])
				count2++;
		if (count2 == 4)
			_errorhelp(p);
	}
}
/**
 * _builtinerr2- handles the error
 * @p: the command
 *
 * Return: nothing.
 */
void _builtinerr2(char **p)
{
	char str1[9] = "unsetenv", str2[7] = "setenv";
	int d = 0, f = 0, count = 0;

	while (p[0][f] != '\0')
		f++;
	if (f == 8)
	{
		for (; d < 8; d++)
			if (p[0][d] == str1[d])
				count++;
		if (count == 8)
			_errorenv(p);
	}
	if (f == 6)
	{
		for (; d < 6; d++)
			if (p[0][d] == str2[d])
				count++;
		if (count == 6)
			_errorenv(p);
	}
}
