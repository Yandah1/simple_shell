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

/* SHELL */
static void signal_handler(int unused_var);
int main(int argc __attribute__((unused)), char **argv, char **environment);

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

char **_tokenize(char *input_buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *new_strtok(char *str, const char *delim);


char *check_for_builtins(vars_t *vars);
void check_for_path(vars_t *vars);
char **make_env(char **environment);

struct list_t
{
char *str;
struct list *next
} list_t;
int print_alias(list_t *node);
int print_alias(list_t *node)
char *p = NULL, *a = NULL;
