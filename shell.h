#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

int sub_numbers(int a, int b);

/* SHELL */
void signal_handler(int unused_var);
int main(int argc __attribute__((unused)), char **argv, char **environment);

/* Define the shell_vars_t structure */
typedef struct {
    int status;
    char **arguments;
    char* buffer;
    char* commands

  
} shell_vars_t;

/* Define the function pointer type */
typedef void (*builtin_func_ptr_t)(shell_vars_t *shell_vars);

builtin_func_ptr_t check_for_builtin_commands(shell_vars_t *shell_vars);

/*BUILTINS */
void new_exit_command(shell_vars_t *shell_vars);
void _env_command(shell_vars_t *shell_vars);
void new_setenv_command(shell_vars_t *shell_vars);
void new_unsetenv_command(shell_vars_t *shell_vars);

void add_key(shell_vars_t *shell_vars);
char **find_key(char **env, char *key);
char *add_value(char *key, char *value);
int _atoi(char *str);

/*ENVIRONMENTS*/
char **make_env(char **shell_env);
void free_env(char **shell_env);

/*ERRORS*/
void print_error(shell_vars_t *shell_vars, char *msg);
void _puts2(char *str);
char *_uitoa(unsigned int count);

unsigned int check_match(char c, const char *str);
char *new_strtok(char *str, const char *delim);

ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strc1, char *strc2);
unsigned int _strlen(char *str);

/*memory*/
char **_realloc(char **ptr, size_t *size);


/* PATH */
int path_execute(char *command, shell_vars_t *shell_vars);
char *find_path(char **env);
void check_for_path(shell_vars_t *shell_vars);
int execute_cwd(shell_vars_t *shell_vars);
int check_for_dir(char *str);


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
} vars_t;

/**
 * struct builtins - struct for the builtin functions
 * @name: name of builtin command
 * @f: function for corresponding builtin
 */

char **make_env(char **env);
void free_env(char **env);

#endif 
