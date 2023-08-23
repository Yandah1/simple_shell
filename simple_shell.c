#include "shell.h"

/* global variable for ^C handling */
unsigned int sig_flag;

/**
 * sig_handler - handles ^C signal interupt
 * @uuv: unused variable (required for signal function prototype)
 *
 * Return: void
 */
static void sig_handler(int uuv)
{
	(void) uuv;
	if (sig_flag == 0)
		_puts("\n$ ");
	else
		_puts("\n");
}

/**
 * main - main function for this shell
 * @argc: number of arguments
 * @argv: array of arguments
 * @environment: array of environment variables
 * Return: 0 or exit status, or ?
 */
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
	size_t len_buffer = 0;
	unsigned int is_pipe = 0, i;
	vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL};

	shell_vars.argv = argv;
	shell_vars.env = make_env(environment);
	signal(SIGINT, sig_handler);
	if (!isatty(STDIN_FILENO))
		is_pipe = 1;
	if (is_pipe == 0)
		_puts("$ ");
	sig_flag = 0;
	while (getline(&(shell_vars.buffer), &len_buffer, stdin) != -1)
	{
		sig_flag = 1;
		shell_vars.count++;
		shell_vars.commands = tokenize(shell_vars.buffer, ";");
		for (i = 0; shell_vars.commands && shell_vars.commands[i] != NULL; i++)
		{
			shell_vars.av = tokenize(shell_vars.commands[i], "\n \t\r");
			if (shell_vars.av && shell_vars.av[0])
				if (check_for_builtins(shell_&vars) == NULL)
					check_for_path(&shell_vars);
			free(shell_vars.av);
		}
		free(shell_vars.buffer);
		free(shell_vars.commands);
		sig_flag = 0;
		if (is_pipe == 0)
			_puts("$ ");
		shell_vars.buffer = NULL;
	}
	if (is_pipe == 0)
		_puts("\n");
	free_env(shell_vars.env);
	free(shell_vars.buffer);
	exit(shell_vars.status);
}
