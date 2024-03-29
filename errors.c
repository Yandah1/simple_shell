#include "shell.h"

/**
 * print_error - fuction that prints error messages to standard error
 * @shell_vars: pointer to struct of variables
 * @msg: message to be printed
 * Return: void
 */
void print_error(vars_t *shell_vars, char *msg)
{
	char *count;

	_puts2(shell_vars->argv[0]);
	_puts2(": ");
	count = _uitoa(shell_vars->count);
	_puts2(count);
	free(count);
	_puts2(": ");
	_puts2(shell_vars->av[0]);
	if (msg)
	{
		_puts2(msg);
	}
	else
		perror("");
}

/**
 * _puts2 - function that prints a string to standard error
 * @str: string to be printed
 * Return: void
 */
void _puts2(char *str)
{
	ssize_t num, len;

	num = _strlen(str);
	len = write(STDERR_FILENO, str, num);
	if (len != num)
	{
		perror("Fatal Error");
		exit(1);
	}

}

/**
 * _uitoa - function that converts an unsigned int to a string
 * @count: unsigned int to be converted
 * Return: pointer to the converted string
 */
char *_uitoa(unsigned int count)
{
	char *numstr;
	unsigned int tmp, digits;

	tmp = count;
	for (digits = 0; tmp != 0; digits++)
		tmp /= 10;
	numstr = malloc(sizeof(char) * (digits + 1));
	if (numstr == NULL)
	{
		perror("Fatal Error1");
		exit(127);
	}
	numstr[digits] = '\0';
	for (--digits; count; --digits)
	{
		numstr[digits] = (count % 10) + '0';
		count /= 10;
	}
	return (numstr);
}
