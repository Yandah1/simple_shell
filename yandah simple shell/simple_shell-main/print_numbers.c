#include "shell.h"
/**
 * print_number - prints and integer to standard error output
 * @n: integer to print
 * Return: 0
 */
void print_number(int n)
{
	unsigned int j, count = 1;
	char a;
	unsigned int var1, numb, var2, var3 = 1;

	var2 = n;
	numb = var2;
	while (numb > 9)
	{
		numb = numb / 10;
		count++;
		var3 = var3 * 10;
	}
	for (j = 1; j <= count; j++)
	{
		var1 = var2 / var3;
		var2 = var2 % var3;
		var3 = var3 / 10;
		a = '0' + var1;
		write(STDERR_FILENO, &a, 1);
	}
}
