#include <stdlib.h>
#include "shell.h"
/**
 * _calloc - allocates memory for an array and initializes it to 0
 * @nmemb: number of  elements
 * @size: size of element
 * Return: pointr to the allocated memory, NULL if fails
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr = NULL;
	unsigned int i;

	if (nmemb == 0 || size == 0)
	{
		return (NULL);
	}
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; i < (nmemb * size); i++)
	{
		*((char *)(ptr) + i) = 0;
	}
	return (ptr);
}
