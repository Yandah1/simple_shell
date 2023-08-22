#include "shell.h"

/**
 * _signal - function that handles SIGINT signal
 * @s: signal to catch
 */
void _signal(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n#cisfun$ ", 10);
}

