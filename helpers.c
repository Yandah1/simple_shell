#include "shell.h"

/**
 * read_help - reads and deplays  the contents of help file
 * @m: The command
 * Return: number of bytess read,or 0 on failure.
 */

ssize_t read_help(char **m)
{
	int fd, r, w;
	char *buff;
	char helpfile[] = "/simple_shell/_helpfiles/help_all.txt";
	char *home, *helpdir;
	size_t letters = 1024;

	buff = malloc((sizeof(char) * letters + 1));
	if (buff == NULL)
		return (0);
	home = _gethome(m);
	helpdir = str_concat(home, helpfile);
	fd = open(helpdir, O_RDONLY);
	if (fd == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	r = read(fd, buff, letters);
	if (r == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	w = write(STDOUT_FILENO, buff, r);
	if (w == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	close(fd);
	free(helpdir);
	free(buff);
	return (r);
}

/**
 * read_cdhelp - reads and disply the contents of "cd"  help file
 * and prints it to POSIX stdout
 * @m: the command
 * Return: number of bytes read, otherwise 0.
 */

ssize_t read_cdhelp(char **m)
{
	int fd, r, w;
	char *buff;
	char helpfile[] = "/simple_shell/_helpfiles/help_cd.txt";
	char *home, *helpdir;
	size_t letters = 1024;

	buff = malloc((sizeof(char) * letters + 1));
	if (buff == NULL)
		return (0);
	home = _gethome(m);
	helpdir = str_concat(home, helpfile);
	fd = open(helpdir, O_RDONLY);
	if (fd == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	r = read(fd, buff, letters);
	if (r == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	w = write(STDOUT_FILENO, buff, r);
	if (w == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	close(fd);
	free(helpdir);
	free(buff);
	return (r);
}

/**
 * read_exithelp - reads  and display exit text file and
 * prints it to POSIX stdout
 * @m: The command
 * Return: number of bytes read , otherwise 0.
 */

ssize_t read_exithelp(char **m)
{
	int fd, r, w;
	char *buff;
	char helpfile[] = "/simple_shell/_helpfiles/help_exit.txt";
	char *home, *helpdir;
	size_t letters = 1024;

	buff = malloc((sizeof(char) * letters + 1));
	if (buff == NULL)
		return (0);
	home = _gethome(m);
	helpdir = str_concat(home, helpfile);
	fd = open(helpdir, O_RDONLY);
	if (fd == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	r = read(fd, buff, letters);
	if (r == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	w = write(STDOUT_FILENO, buff, r);
	if (w == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	close(fd);
	free(helpdir);
	free(buff);
	return (r);
}

/**
 * read_helphelp - reads and diplay the content of the "help" help file
 * @m: the command
 * Return: number of buytes read, or 0 on failure
 */

ssize_t read_helphelp(char **m)
{
	int fd, r, w;
	char *buff;
	char helpfile[] = "/simple_shell/_helpfiles/help_help.txt";
	char *home, *helpdir;
	size_t letters = 1024;

	buff = malloc((sizeof(char) * letters + 1));
	if (buff == NULL)
		return (0);
	home = _gethome(m);
	helpdir = str_concat(home, helpfile);
	fd = open(helpdir, O_RDONLY);
	if (fd == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	r = read(fd, buff, letters);
	if (r == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	w = write(STDOUT_FILENO, buff, r);
	if (w == -1)
	{
		free(helpdir);
		free(buff);
		return (0);
	}
	close(fd);
	free(helpdir);
	free(buff);
	return (r);
}
