#include "shell.h"
#define BUF_SIZE 2048
/**
 * _iscd - checks if the command is "cd"
 * @p: the command and it arguments
 * @loop: the loop counter
 * @v: the array of command tokens
 * @myenv: the environment variables
 * Return: -1 if not success 0 if exist cd in args[0]
 */
int _iscd(char **p, int loop, char *v[], char **myenv)
{
	char str[] = "cd";
	int i = 0, count = 0, status = -1;

	while (p[0][i] != '\0')
	{
		if (i < 2)
		{
			if (p[0][i] == str[i])
				count++;
		}
		i++;
	}
	if (i == 2)
		count++;

	if (count == 3)
	{
		_cd(p, loop, v, myenv);
		status = 0;
	}
	else if (count == 2)
	{
		_put_err(p, loop, 3, v);
		status = 0;
	}
	return (status);
}

/**
 * _cleancd - clear the contents of character of array
 * @c: array to be cleared
 * Return: -1 if not success 0 if exist cd in args[0]
 */
void _cleancd(char *c)
{
	int i;

	for (i = 0; i < BUF_SIZE; i++)
		c[i] = 0;
}

/**
 * _fullcd -copy the content of one character array to anather
 * @f: destination char
 * @aux: the source character array
 * Return: -1 if not success 0 if exist cd in args[0]
 */
void _fullcd(char *f, char *aux)
{
	int w;

	for (w = 0; aux[w] != '\0'; w++)
		f[w] = aux[w];
	for (; w < BUF_SIZE; w++)
		f[w] = 0;
}
/**
 * _cd - Changes the current working directory
 * @a:the array of pointers
 * @loop: the loop counter
 * @v: array of command tokens
 * @myenv: the environment variables
 * Return:-1 if not find the directory or 0 if success
 */
void _cd(char **a, int loop, char *v[], char **myenv)
{
	int status = 0, x = 0;
	static char buf[BUF_SIZE];
	static int w = 1;
	char *home, aux[BUF_SIZE] = {0};

	currentstatus(&x);
	if (w == 1)
	{ home = _gethome(myenv);
		if (!home)
			getcwd(home, BUF_SIZE);
		_updateoldpwd(getcwd(buf, BUF_SIZE), myenv);
		_fullcd(buf, _gethome(myenv));
		w++;
	}
	if (a[1] == NULL)
	{
		_cleancd(buf);
		getcwd(buf, BUF_SIZE);
		_updateoldpwd(buf, myenv);
		status = chdir((const char *)_gethome(myenv));
		_updatepwd(_gethome(myenv), myenv);
	}
	else if (a[1][0] == '-' && a[1][1] == '\0')
	{
		_cleancd(aux), getcwd(aux, BUF_SIZE);
		_updateoldpwd(aux, myenv);
		write(STDOUT_FILENO, buf, BUF_SIZE);
		write(STDOUT_FILENO, "\n", 1);
		status = chdir((const char *) buf);
		_updatepwd(buf, myenv), _fullcd(buf, aux);
	}
	else
	{
		_cleancd(buf), getcwd(buf, BUF_SIZE);
		_updateoldpwd(buf, myenv);
		status = chdir((const char *)a[1]);
		_updatepwd(a[1], myenv);
	}
	if (status == -1)
		_put_err(a, loop, 1, v);
}
