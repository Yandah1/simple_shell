#include "shell.h"

/**
 * semicolon -check if  there is a ";" or a ";;"
 * @line: complete input line to check
 * @loop: number of actual loop
 * @argv: command_line argument
 * Return: 1 if find ";" or ";;" or 0 if not
 */
int semicolon(char *line, int loop, char **argv)
{
	int isValid = 0, index = 0;

	while (line[index] != '\0')
	{
		if (line[0] == ';')
		{
			isValid = 1;
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			print_number(loop);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "Syntax error: ", 14);
			write(STDERR_FILENO, ";", 1);
			write(STDERR_FILENO, " unexpected\n", 12);
			break;
		}
		if (line[index] == ';' && line[index + 1] == ';')
		{
			isValid = 1;
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": ", 2);
			print_number(loop);
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "Syntax error: ", 14);
			write(STDERR_FILENO, ";;", 2);
			write(STDERR_FILENO, " unexpected\n", 12);
			break;
		}
		index++;
	}
	return (isValid);
}
/**
 *_comments - remove comments from a line
 *@line: input line
 * Return: the new input
 */
char *_comments(char *line)
{
	int b = 0, c = 0, flagComment = 0;

	while (line[c] != '\0')
		c++;
	while (line[b] != '\0')
	{
		if (line[0] == '#')
		{
			flagComment = 1;
			break;
		}
		if (line[b] == '#' && line[b - 1] == ' ')
		{
			flagComment = 1;
			break;
		}
		b++;
	}
	if (flagComment == 1)
	{
		for (; b < c; b++)
			line[b] = 0;
	}
	return (line);
}

