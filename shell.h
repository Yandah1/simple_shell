#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


/**
 * struct variables - variables
 * @av: command line arguments
 * @buffer: buffer of command
 * @env: environment variables
 * @count: count of commands entered
 * @argv: arguments at opening of shell
 * @status: exit status
 * @commands: double pointer to commands
 */
typedef struct variables
{
	char **av;
	char *buffer;
	char **env;
	size_t count;
	char **argv;
	int status;
	char **commands;
} shell_vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */
typedef struct builtins
{
	char *name;
	void (*f)(vars_t *);
} builtins_t;

char **make_env(char **env);
void free_env(char **env);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

/*BUILINS*/
void (*check_for_builtins(vars_t *shell_vars))(vars_t shell_*vars);
void new_exit(shell_vars_t *shell_vars);
void _env(vars_t *shell_vars);
void new_setenv(vars_t *shell_vars);
void new_unsetenv(vars_t *shell_vars);

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);
void add_key(vars_t *shell_vars);

char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);
/* PATHS*/
void check_for_path(vars_t *shell_vars);
int path_execute(char *command, vars_t *shell_vars);
char *find_path(char **env);
int execute_cwd(vars_t *shell_vars);
int check_for_dir(char *str);
/*ERRORS*/
void print_error(vars_t *shell_vars, char *msg);
void _puts2(char *str);
char *_uitoa(unsigned int count);

#endif /* _SHELL_H_ */
