#include "shell.h"
/**
 * _sch - searches for character within a string
 * @s: string to search
 * @c: character to find
 * Return: 1 if success 0 if not
 */
int _sch(char *s, char c)
{
	int count = 0;

	while (s[count] != '\0')
	{
		if (s[count] == c)
		{
			break;
		}
		count++;
	}
	if (s[count] == c)
		return (1);
	else
		return (0);
}
/**
 * _strtoky - Tokenizes a string basrd on a set of h delimiters
 * @s: string to tokenize
 * @d: delimiters character
 * Return: first partition
 */
char *_strtoky(char *s, char *d)
{
	static char *lastoken;
	int i = 0, j = 0;

	if (!s)
		s = lastoken;
	while (s[i] != '\0')
	{
		if (_sch(d, s[i]) == 0 && s[i + 1] == '\0')
		{
			lastoken = s + i + 1;
			*lastoken = '\0';
			s = s + j;
			return (s);
		}
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 0)
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 1)
		{
			lastoken = s + i + 1;
			*lastoken = '\0';
			lastoken++;
			s = s + j;
			return (s);
		}
		else if (_sch(d, s[i]) == 1)
		{
			j++;
			i++;
		}
	}
	return (NULL);
}
/**
* _strtoky2 - function that tokenizas a string with ;
* @s: string to tokenize
* @d: delimiter character
* Return: first partition
*/
char *_strtoky2(char *s, char *d)
{
	static char *lastoken;
	int i = 0, j = 0;

	if (!s)
		s = lastoken;
	while (s[i] != '\0')
	{
		if (_sch(d, s[i]) == 0 && s[i + 1] == '\0')
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 0)
			i++;
		else if (_sch(d, s[i]) == 0 && _sch(d, s[i + 1]) == 1)
		{
			lastoken = s + i + 1;
			*lastoken = '\0';
			lastoken++;
			s = s + j;
			return (s);
		}
		else if (_sch(d, s[i]) == 1)
		{
			j++;
			i++;
		}
	}
	return (NULL);
}

