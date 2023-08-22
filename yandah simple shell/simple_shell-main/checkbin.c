#include "shell.h"

/**
 * verify_path - check if the path has a : at the begining
 * or if exist ::
 *@path: string inside PATH env varible
 *@pwd: string inside PWD env variable
 *Return: path, or pwd concatenated to path if there is a : at the begining or
 *pwd concatenated when there is ::
 */
char *verify_path(char *path, char *pwd)
{
	int b = 0, c = 0, i = 0;
	char *newPath = NULL;

	while (path[c] != '\0')
		c++;
	while (path[b] != '\0')
	{
		if (path[0] == ':')
		{
			newPath = _calloc(c + 1, sizeof(char));
			newPath[0] = pwd[0];
			for (i = 0; path[i] != '\0'; i++)
				newPath[i + 1] = path[i];
			free(path);
			path = newPath;
			b++;
			c++;
		}
		else if (path[b] == ':' && path[b + 1] == ':')
		{
			newPath = _calloc(c + 1, sizeof(char));
			for (i = 0; i <= b; i++)
				newPath[i] = path[i];
			newPath[i] = pwd[0];
			for (i = i + 1; path[i] != '\0'; i++)
				newPath[i] = path[i - 1];
			free(path);
			b++;
			path = newPath;
		}
			b++;
	}
	return (path);
}
/**
 *_getpath -retrieves the value of the "PATH" environment variable.
 * @m: double pointer
 * Return: string inside PATH enviroment or NULL if failed
 */
char *_getpath(char **m)
{
	int i, j, q = 0, w = 0, count = 0;
	char str[] = "PATH=";
	char *path;

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
	q = count;
	if (count == 5)
	{
		while (m[i][q] != '\0')
		{
			w++;
			q++;
		}
		if (w == 0)
			return (NULL);
		path = _calloc(w + 1, sizeof(char));
		if (path == NULL)
			return (NULL);
		q = 5;
		while (m[i][q] != '\0')
		{
			path[q - 5] = m[i][q];
			q++;
		}
		return (path);
	}
	return (NULL);
}
/**
 * checkbin - checks if arg[0] exist in /bin/
 * @b: double pointer to an array of strings
 * @m: copy of the string environment variables
 * Return: 0.
 */

char **checkbin(char **b, char **m)
{
	unsigned int i = 0, j = 0, k = 0;
	struct stat veri;
	char *path, *tokens, *buf, *newP;
	char *fullpath;

	i = _strlen(b[0]);
	if (b == NULL || i == 0)
		return (NULL);
	path = _getpath(m);
	if (path == NULL)
		return (b);
	newP = verify_path(path, ".");
	tokens = _strtoky(newP, ":");
	if (!tokens)
		return (NULL);
	while (tokens != NULL)
	{
		while (tokens[j] != '\0')
			j++;
		buf = _calloc((j + 2), sizeof(char));
		if (buf == NULL)
			perror("No memory");
		for (k = 0; k < j; k++)
			buf[k] = tokens[k];
		buf[k] = '/';
		fullpath = str_concat(buf, b[0]);
		if (stat(fullpath, &veri) == 0)
		{
			b[0] = _realloc2(buf, b[0], i, _strlen(fullpath));
			free(buf), free(fullpath);
			free(newP);
			return (b);
		}
		tokens = _strtoky(NULL, ":");
		j = 0;
		free(buf), free(fullpath);
	}
	free(newP);
	return (b);
}
