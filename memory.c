#include "shell.h"

/**
 * _realloc - reallocates a pointer to double the space
 * @ptr: pointer to the old array
 * @size: pointer to number of elements in the old array
 *
 * Return: pointer to the new array
 */
char **_realloc(char **ptr, size_t *size)
{
	char **new_array;
	size_t i;

	new_array = malloc(sizeof(char *) * ((*size) + 10));
	if (new_array == NULL)
	{
		free(ptr);
		return (NULL);
	}
	for (i = 0; i < (*size); i++)
	{
		new_array[i] = ptr[i];
	}
	*size += 10;
	free(ptr);
	return (new_array);
}

