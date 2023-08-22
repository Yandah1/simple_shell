#include "shell.h"
/**
 *rev - The function get the input of user is env, cd
 *@pointer: User input variables and pointers
 *@Loop: counts number of loops
 *@li: input user
 *@v: input arguments
 *@m: variables of the environment
 *@e: counts number of elements in m
 *@f: complete input
 * Return: 0 if the input is cd or env or -1
 */
int rev(char **pointer, int Loop, char *li, char **v, char ***m,
	int *e, char *f)
{
	int valenv = 0, valcd = 0, other = -1, valex = 0, valhel = 0;
	int valunset = 0, valset = 0;

	valunset = _isunsetenv(pointer, *m, e, Loop, v);
	if (valunset == 0)
		return (valunset);
	valset = _issetenv(pointer, m, e, Loop, v);
	if (valset == 0)
	return (valset);
	valex = _isexit(pointer, Loop, li, v, *m, f);
	if (valex == 0)
		return (valex);
	valhel = _ishelp(pointer, Loop, v, *m);
	if (valhel == 0)
		return (valhel);
	 _env(pointer);
valcd = _iscd(pointer, Loop, v, *m);
	if (valenv == 0)
		return (valenv);
	if (valcd == 0)
		return (valcd);
	return (other);
}
/**
 * functions - realize all the funcitons
 *@line: input of user
 *@loop: number of loops
 *@argv: argumnets
 *@m:  variables of the environment
 *@e: counts number of elements in m
 *@f: complete user input
 */
void functions(char *line, int loop, char *argv[], char ***m, int *e, char *f)
{
	char **args = NULL;
	int value = 1, i = 0;

	line = _comments(line);
	args = parsing(line);
	if (args)
	{
		for (i = 0; args[i] != NULL; i++)
			;
		value = rev(args, loop, line, argv, m, e, f);
		if (value != 0)
		{
			args = checkbin(args, *m);
			if (args)
				_frk(args, line, i, loop, argv, *e, *m, f);
		}
		free_grid(args, i);
		free(line);
	}
	else
	{
		free(line);
		fflush(STDIN_FILENO);
	}
	_put_err(args, loop, 0, argv);
}
/**
 * _noargv - empty shell form
 * @argv: input variables
 * @envp: variables of the environment
 */
void _noargv(char *argv[], char *envp[])
{
	char *line = NULL, **m = NULL, *p = NULL, *pr1 = NULL;
	int e = 0, *ploop, i = 0, sem = 0;
	static int loop;

	loop = 0;
	ploop = &loop;
	while (1)
	{
		if (loop == 0)
		{
			m = create_env(envp);
			for (e = 0; m[e] != NULL; e++)
				;
		}
		line = _getline(ploop, m, e);
		sem = semicolon(line, loop, argv);
		if (!(sem == 1))
		{
			p = _strtoky2(line, ";\n");
			while (p)
			{
				pr1 = _calloc(_strlen(p) + 2, sizeof(char));
				for (i = 0; p[i] != '\0'; i++)
					pr1[i] = p[i];
				pr1[i] = '\n';
				pr1[i + 1] = '\0';
				functions(pr1, loop, argv, &m, &e, line);
				p = _strtoky2(NULL, ";\n");
			}
		}
		free(line);
	}
}

