#include "shell.h"

/**
 * signal_handler - handles interrupt signal (^C)
 * @unused_var: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void signal_handler(int unused_var)
{
	(void) unused_var;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function for the shell
 * @argc: number of arguments passed to main
 * @argv: array of arguments passed to main
 * @environment: array of environment variables
 *
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t buffer_length = 0;
	unsigned int is_piped = 0, i;
	int status = 0;
	char *buffer = NULL;
	char **commands = NULL;
	char **arguments = NULL;

	argv = argv;
	environment = make_env(environment);
	signal(SIGINT, signal_handler);
	if (!isatty(STDIN_FILENO))
		is_piped = 1;
	if (is_piped == 0)
		_puts("$ ");
	sig_flag = 0;
	while (getline(&buffer, &buffer_length, stdin) != -1)
	{
		sig_flag = 1;
		count++;
		commands = _tokenize(buffer, ";");
		for (i = 0; commands && commands[i] != NULL; i++)
		{
			arguments = _tokenize(commands[i], "\n \t\r");
			if (arguments && arguments[0])
				if (check_for_builtins(arguments) == NULL)
					check_for_path(arguments, environment, &status);
			free(arguments);
		}
		free(buffer);
		free(commands);
		sig_flag = 0;
		if (is_piped == 0)
			_puts("$ ");
		buffer = NULL;
	}
	if (is_piped == 0)
		_puts("\n");
	free_env(environment);
	free(buffer);
	exit(status);
}
