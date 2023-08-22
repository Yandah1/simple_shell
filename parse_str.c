#include "shell.h"
/**
 * Counter - counter of the lim found in the input
 * @L: string  input data type;
 * @lim: finds characters in the L string
 * Return: number of characters found
 */
int Counter(char *L, char *lim)
{
	int count1 = 0, number = 0, count2 = 0;

	while (lim[count2] != '\0')
	{
		count1 = 0;
		while (L && L[count1] != '\0')
		{
			if (L[count1] != lim[count2])
			{
				if (L[count1 + 1] == lim[count2] || L[count1 + 1] == '\0')
					number++;
			}
			count1++;
		}
		count2++;
	}
	return (number);
}
/**
 * parsing - create an array of pointers depending of the delimit characters
 * @line: user input
 * Return: an array of pointers of n size
 */
char **parsing(char *line)
{
	char *token = NULL, **p = NULL;
	int length = 0, k = 0, m = 0, buffsize = 0;

	if (line == NULL)
		return (NULL);
	buffsize = Counter(line, " \t");
	p = _calloc((buffsize + 1), sizeof(char *));
	if (!p)
	{
		perror("No memory");
		return (NULL);
	}
/*store the token partition inside **p */
	token = _strtoky(line, " \t\n");
	if (!token)
	{
		free(p);
		return (NULL);
	}
	while (token)
	{
		while (token[length] != '\0')
			length++;
		p[k] = _calloc((length + 1), sizeof(char));
		if (p[k] == NULL)
		{
			free_grid(p, k);
			perror("No memory");
			return (NULL);
		}
/*fill the pointer with the content of token*/
		for (m = 0; m < length; m++)
			p[k][m] = token[m];
		length = 0;
		k++;
/*get the next element*/
		token = _strtoky(NULL, " \t\n");
	}
	p[k] = NULL;
	return (p);
}
