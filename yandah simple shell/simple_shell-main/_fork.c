#include "shell.h"
/**
 * currentstatus - Set the current status
 * @status: Pointer to the ststus value
 * Return: the actual changed
 */
int currentstatus(int *status)
{
        static int actualstatus;

        if (status)
                actualstatus = *status;

        return (actualstatus);
}
/**
 * _frk - Fork and execute a command
 * @p: array of command argument
 * @l: pointer to the command line string
 * @a: number of arguments in @p
 * @L: count of loops
 * @v: array of environmental variables
 * @e: env length
 * @m: copy of environmental variable
 * @f: complete input
 * Return: Nothing.
 */
void executeCommand(char **p, int a, int L, char **v, char *f, char **m, int e) 
{
	int exist = access((const char *) p[0], F_OK);
	int execute = access((const char *) p[0], X_OK);

	if (exist == 0 && execute == -1) 
	{
		_put_err(p, L, 4, v);
		free(f);
		free_grid(p, a);
		free_grid(m, e);
		exit(126);
 	}

	if (strcmp(p[0], "ls") == 0 && a == 1)
	{
		char *const argv[] = { "/bin/ls", "-l", "/tmp", NULL };
		char *const envp[] = { NULL };

	if (execve("/bin/ls", argv, envp) == -1)
	{
		perror("execve");
		exit(1);
	}
	} else {
		if (execve(p[0], p, m) == -1) 
		{
			_put_err(p, L, 3, v);
			free(f);
			free_grid(p, a);
			free_grid(m, e);
			exit(127);
		}
	}
}
void _frk(char **p, char *l, int a, int L, char **v, int e, char **m, char *f) 
{
	pid_t child_pid;
	int ty = 0, status

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		exit(127);
	}

	if (child_pid == 0) 
	{
		executeCommand(p, a, L, v, f, m, e);
	} else
	{
		waitpid(child_pid, &status, 0);
		if (WIFEXITED(status)) 
		{
			ty = WEXITSTATUS(status);
			currentstatus(&ty);
		}
    	}
}
