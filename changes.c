#include "shell.h"
/**
 * _updatepwd - change the OLDPWD environment variable
 * @buf: buffer containing the new pwd
 * @myenv: copy of environmental variable
 * Return: the string inside PWD env variable
 */
void _updatepwd(char *buf, char **myenv)
{
	char *entirepwd;
	char str[] = "PWD=";
	int i = 0, j = 0, count = 0, bf = 0, myenvlen = 0, buflen = 0;

	entirepwd = str_concat(str, buf);
	for (i = 0; myenv[i] != NULL; i++, count = 0)
	{
		for (j = 0; myenv[i][j] != '\0' && j < 4; j++)
		{
			if (myenv[i][j] == str[j])
			{
				count++;
			}
			else
				break;
		}
		if (count == 4)
			break;
	}
	if (count == 4)
	{
		myenvlen = _strlen(myenv[i]);
		buflen = _strlen(entirepwd);
		if (buflen < myenvlen)
		{
			for (bf = 0; entirepwd[bf] != '\0'; bf++)
				myenv[i][bf] = entirepwd[bf];
			for (; bf < myenvlen; bf++)
				myenv[i][bf] = 0;
		}
		else
		{
			myenv[i] = _realloc(myenv[i], myenvlen, buflen + 1);
			for (bf = 0; entirepwd[bf] != '\0'; bf++)
				myenv[i][bf] = entirepwd[bf];
		}
	}
	free(entirepwd);
}
/**
 * _updateoldpwd - change the OLDPWD
 * @buf: buffer comtaining new value of old pwd
 * @myenv: copy of environmental variable
 * Return: the string inside PWD env variable
 */
void _updateoldpwd(char *buf, char **myenv)
{
	char *entirepwd;
	char str[] = "OLDPWD=";
	int i = 0, j = 0, count = 0, ken = 0, myenvlen = 0, buflen = 0;

	entirepwd = str_concat(str, buf);
	for (i = 0; myenv[i] != NULL; i++)
	{
		for (j = 0; myenv[i][j] != '\0' && j < 7; j++)
		{
			if (myenv[i][j] == str[j])
				count++;
			else
				break;
		}
		if (count == 7)
			break;
	}
	if (count == 7)
	{
		myenvlen = _strlen(myenv[i]);
		buflen = _strlen(entirepwd);
		if (buflen < myenvlen)
		{
			for (ken = 0; entirepwd[ken] != '\0'; ken++)
				myenv[i][ken] = entirepwd[ken];
			for (; ken < myenvlen; ken++)
				myenv[i][ken] = 0;
		}
		else
		{
			myenv[i] = _realloc(myenv[i], myenvlen, buflen + 1);
			for (ken = 0; entirepwd[ken] != '\0'; ken++)
				myenv[i][ken] = entirepwd[ken];
		}
	}
	free(entirepwd);
}
