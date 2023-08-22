#include "shell.h"

/**
 * _gethome - get the value of the HOME environment variable
 * @m: Pointer to an array of strings
 *Return: string inside the HOME enviroment variable
 */
char *_gethome(char **m)
{
	int i, j, ken, count = 0;
	char str[] = "HOME=";
	char *home = NULL;

	for (i = 0; m[i] != NULL; i++)
	{
		for (j = 0; m[i][j] != '\0'; j++)
		{
			if (count == 5)
				break;
			if (m[i][j] == str[j])
				count++;
			else
				break;
		}
		if (count == 5)
			break;
	}
	if (count == 5)
	{
		home = m[i];
		for (ken = 0; ken < 5; ken++)
		{
			home++;
		}
	}
	return (home);
}
