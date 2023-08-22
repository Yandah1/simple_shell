#include "shell.h"
/**
* main - shell skeleton
* @argc: number of arguments
* @argv: arguments vector
* @envp: environment variables
* Return: 0 on Success
*/
int main(int argc, char *argv[], char *envp[])
{

	if (argc == 1)
	{
		_noargv(argv, envp);
	}
	else if (argc == 2)
	{
		_yesargv(argv, envp);
	}
	else
	{
		write(STDERR_FILENO, "NO ADMITTED AMOUNT OF ARGUMENTS", 31);
		write(STDIN_FILENO, "\n", 1);
	}
	execute_command(); 

	return (0);
}

