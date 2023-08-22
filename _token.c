#include "shell.h"

/**
 * _tokenize - tokenizes a buffer with a delimiter
 * @input_buffer: buffer to tokenize
 * @delimiter: delimiter to tokenize along
 *
 * Return: pointer to an array of pointers to the tokens
 */
char **_tokenize(char *input_buffer, char *delimiter)
{
	char **token_array = NULL;
	size_t i = 0, max_tokens = 10;

	if (input_buffer == NULL)
		return (NULL);
	token_array = malloc(sizeof(char *) * max_tokens);
	if (token_array == NULL)
	{
		perror("Fatal Error");
		return (NULL);
	}
	while ((token_array[i] = custom_new_strtok(input_buffer, delimiter)) != NULL)
	{
		i++;
		if (i == max_tokens)
		{
			token_array = custom_realloc(token_array, &max_tokens);
			if (token_array == NULL)
			{
				perror("Fatal Error");
				return (NULL);
			}
		}
		input_buffer = NULL;
	}
	return (token_array);
}
