#include "shell.h"
/**
 * salida3 - Free memory allocated for a grid.
 * @m: pointer to pointer char
 * @e: number of elements in m
 */
void salida3(char **m, int e)
{
	free_grid(m, e);
	exit(currentstatus(NULL));
}
/**
 * salida2 - Frees memory and exit progam with a prompt
 *@m: pointer to pointer char, rewpresents the grid
 *@e: number of elements in m
 *@line: input of user
 */
void salida2(char **m, int e, char *line)
{
	free(line);
	free_grid(m, e);
	write(STDIN_FILENO, "#cisfun$ ", 9);
	write(STDIN_FILENO, "\n", 1);
	exit(currentstatus(NULL));
}
/**
 * salida1 - Frees memory
 * @m: pointer to pointer
 * @e: number of elements in m
 */
void salida1(char **m, int e)
{
	free_grid(m, e);
	write(STDIN_FILENO, "\n", 1);
	exit(currentstatus(NULL));
}
/**
 * _getline - function to read what the user writes
 * @a: pointer to an integer to store number
 * @e: pointer to pointer to char
 * @m: size of the grid
 * Return: line in sucess otherwise NULL.
 */
char  *_getline(int *a, char **m, int e)
{
	char letter[1] = {0}, *input_line = NULL;
	size_t bufsize = 0;
	static int number = 1;

	if (number == 2)
	salida2(m, e, input_line);
	for (; (number != 0); bufsize = 0, free(input_line))
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);
		*a = *a + 1;
		signal(SIGINT, _signal);
		for (; ((number = read(STDIN_FILENO, letter, 1)) > 0); bufsize++)
		{
			if (bufsize == 0)
				input_line = _calloc(bufsize + 3, sizeof(char));
			else
				input_line = _realloc(input_line, bufsize, bufsize + 3);
			if (!input_line)
			{
				number = 0;
				break;
			}
			input_line[bufsize] = letter[0], input_line[bufsize + 1] = '\n';
			input_line[bufsize + 2] = '\0';
			if (input_line[bufsize] == '\n')
				break;
		}
		if (number == 0 && bufsize == 0)
			break;
		else if (number == 0 && bufsize != 0)
		{
			number = 2;
			break;
		}
		else if (input_line[0] != '\n')
			return (input_line);
	}
	if (number == 0)
		salida1(m, e);
	return (input_line);
}
/**
 * _getlineav - function reads the lines from a file.
 * @a: pointer to an integer
 * @e: size
 * @m: pointer to pointer char
 * @av: arguments in input
 * Return: line in sucess otherwise NULL.
 */
char  *_getlineav(int *a, char **m, int e, char **av)
{
	char letter[1] = {0}, *inputLin = NULL;
	size_t lineSiz = 0;
	static unsigned int num = 1;
	static int  fd;

	for (; (num != 0); lineSiz = 0, free(inputLin))
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{ close(fd), free_grid(m, e);
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": 0: ", 5);
			write(STDERR_FILENO, "Can't open ", 11);
			write(STDERR_FILENO, av[1], _strlen(av[1]));
			write(STDERR_FILENO, "\n", 1), exit(127);
		}
		*a = *a + 1;
		while ((num = read(fd, letter, 1)) > 0)
		{
			if (lineSiz == 0)
				inputLin = _calloc(lineSiz + 3, sizeof(char));
			else
				inputLin = _realloc(inputLin, lineSiz, lineSiz + 3);
			if (!inputLin)
			{
				num = 0;
				break;
			}
				inputLin[lineSiz] = letter[0], inputLin[lineSiz + 1] = '\n';
			inputLin[lineSiz + 2] = '\0', lineSiz++;
		}
		if (num == 0 && lineSiz == 0)
			break;
		else if (inputLin[0] != '\n')
			return (inputLin);
	}
	if (num == 0)
		close(fd), salida3(m, e);
	return (inputLin);
}

