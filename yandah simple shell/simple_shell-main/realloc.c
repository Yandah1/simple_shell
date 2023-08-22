#include "shell.h"
/**
 * _realloc - Reallocates memory block with a new size and copy data
 * @ptr: malloc pointer to reallocate
 * @old_size: size of original memory
 * @new_size: new size of reallocated memory
 * Return: pointer to the reallocted memory
 */
void *_realloc(char *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p = NULL;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		return (p);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size > old_size)
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		for (i = 0; i < old_size; i++)
			p[i] = *((char *)ptr + i);
		free(ptr);
	}
	else
	{
		p = _calloc(new_size + 1, sizeof(char));
		if (!p)
			return (NULL);
		for (i = 0; i < new_size; i++)
			p[i] = *((char *)ptr + i);
		free(ptr);
	}
	return (p);
}

/**
 * _realloc2 - Reallocated a memory block with a new size and copies data
 * @a: pointer to the original memory block
 * @p: malloc pointer to reallocate
 * @old: size of original memory block
 * @new_size: new size for reallocated memory
 * Return: pointer to the reallocated memory
 */
void *_realloc2(char *a, char *p, unsigned int old, unsigned int new_size)
{
	char *ps = NULL;
	unsigned int i, j = 0;

	if (new_size == old)
		return (p);
	if (p == NULL || a == NULL)
	{
		ps = _calloc(new_size + 1, sizeof(char));
		if (!ps)
			return (NULL);
		return (ps);
	}
	while (a[j] != '\0')
		j++;
	if (new_size == 0 && p != NULL)
	{
		free(p);
		return (NULL);
	}
	if (new_size > old)
	{
		ps = _calloc(new_size + 1, sizeof(char));
		if (!ps)
			return (NULL);
		for (i = 0; i < j; i++)
			ps[i] = a[i];
		for (; i <= new_size; i++)
			ps[i] = *((char *)p + (i - j));
		free(p);
	}
	else
	{
		ps = _calloc(new_size, sizeof(char));
		if (!ps)
			return (NULL);
		for (i = 0; i < new_size; i++)
			ps[i] = *((char *)p + i);
		free(p);
	}
	return (ps);
}
