#include "shell.h"

/**
 * str_concat - concetenates two strings
 * @s1: first string
 * @s2: second string
 * Return: return a pointer to the concetenated sring,
 *  or null on failure
 */
char *str_concat(char *s1, char *s2)
{
	char *p;
	unsigned int a = 0, b = 0, c, d = 0;

	if (s1 == NULL)
	{
		s1 = "";
	}
	if (s2 == NULL)
	{
		s2 = "";
	}
	while (*(s1 + a) != '\0')
	{
		a++;
	}
	while (s2[b])
	{
		b++;
	}
	p = _calloc(a + b + 1, sizeof(char));
	if (!p)
	{
		return (NULL);
	}
	else
	{
		for (c = 0; c < a; c++)
		{
			p[c] = s1[c];
		}
		for (c = a; c <= (a + b); c++, d++)
		{
			p[c] = s2[d];
		}
		return (p);
	}
}

/**
 * _strlen - cslculate the length of a string.
 * @s: string
 * Return: Always 0.
 */
int _strlen(char *s)
{
	int length = 0;

	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

