#ifndef _SHELL_H_
#define _SHELL_H_

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

/* task 0*/
int sub_numbers(int a, int b);

/*global variables*/

char **create_env(char *envp[]);
void _updateoldpwd(char *buf, char **myenv);
void _updatepwd(char *buf, char **myenv);


/* shell functions*/

void *_realloc(char *ptr, unsigned int old_size, unsigned int new_size);
char *_getline(int *a, char **m, int e);
char  *_getlineav(int *a, char **m, int e, char **av);
char **parsing(char *line);
char *_comments(char *line);
int semicolon(char *line, int loop, char **argv);
int currentstatus(int *status);
void _noargv(char *argv[], char *envp[]);
void _yesargv(char *argv[], char *envp[]);
void functions(char *line, int loop, char *argv[], char ***m, int *e, char *f);
int rev(char **p, int L, char *li, char **v, char ***m, int *e, char *f);
char *str_concat(char *s1, char *s2);
int _strlen(char *s);

/*setenv*/
int _issetenv(char **p, char ***myenv, int *e, int loop, char *v[]);
void _setenv(char **p, char ***myenv, int *e, int loop, char *v[]);
void _setenvcreat(char ***myenv, int *e, char *entirenv);

/* unsetenv*/
int _isunsetenv(char **p, char **myenv, int *e, int loop, char *v[]);
void _unsetenv(char **p, char **myenv, int *e, int loop, char *v[]);
void _errorenv(char **p);

/*char _getline_av(char *buffer);*/
void free_grid(char **grid, int height);
void _frk(char **p, char *l, int a, int L, char **v, int e, char **m, char *f);
char *_getpwd(char **m);
char **checkbin(char **b, char **m);
void *_realloc2(char *a, char *p, unsigned int old, unsigned int new_size);
int  _isexit(char **p, int L, char *l, char **v, char **m, char *f);
void _signal(int s);

char *_strtoky(char *s, char *d);
char *_strtoky2(char *s, char *d);

/* Other declarations */

int _atoi(char *s);
char *verify_path(char *path, char *pwd);
char *_getpwd(char **m);
char *_changeoldpwd(void);
char *_changepwd(void);
char *_gethome(char **m);
int _iscd(char **p, int loop, char *v[], char **myenv);
void _cd(char **a, int loop, char *v[], char **myenv);
void _env(char **myenv);
void *_calloc(unsigned int nmemb, unsigned int size);


#define SIZE 1024

/* help files*/
ssize_t read_help(char **m);
ssize_t read_cdhelp(char **m);
ssize_t read_exithelp(char **m);
ssize_t read_helphelp(char **m);
int _ishelp(char **p, int loop, char *v[], char **m);
void _help_builtin(char **p, int loop, char *v[], char **m);
void _help(char **p, int loop, char *v[], char **m);

/* errors */
void _put_err(char **p, int loop, int sig, char *v[]);
void _builtinerr(char **p);
void _builtinerr2(char **p);
void _errorcd(char **p);
void _errorexit(char **p);
void _errorhelp(char **p);
void _errorgarbage(char **p);
void print_number(int n);

/* alias */
typedef  struct list list_t;

struct list {
	char *str;
	list_t *next;
};

typedef struct {

	list_t *history;
	list_t *alias;

} info_t;

typedef struct {
	
	int arg;
	char **argv;
	list_t *alias;
} command_t;

int myaliasfun_(info_t *info);
int _aliashistory(info_t *info);
int print_alias(list_t *node);
int set_alias(info_t *info, char *str);
int unset_alias(info_t *info, char *str);

#endif
