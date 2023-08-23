This is a repository for the C - Simple Shell team project.

Done by : Nonkululeko Khanyile and Nimrod Sekwati

The objective of this project is to create a simple UNIX shell. The shell should be able to handle basic commands such as ls, cd, pwd, echo, and exit. The shell should also be able to handle pipes and redirection.

The shell is written in C and is fully documented. All codes have to pass all of the Betty checks.


This simple shell includes the basic functionality of a traditional Unix-like command line user interface. Standard functions and system calls employed in simple shell include: access, execve, exit, fork, free, fstat, getline, malloc, perror, signal, stat, wait, write.

* [shell.h](shell.h) - program header file

* [builtins.c](builtins.c) - major builtin functions

* [builtins2.c](builtins2.c) - helper functions for the builtins
 
* [environment.c](environment.c) - functions related to the environment

* [errors.c](errors.c) - functions related to printing errors

* [memory_allocation.c](memory_allocation.c) - memory allocation functions

* [new_strtok.c](new_strtok.c) - custom strtok and helper functions
 
* [path.c](path.c) - functions related to executing commands
 
* [simple_shell.c](simple_shell.c) - essential functions to the shell

* [strfunc.c](strfunc.c) - functions related to string manipulation

* [tokenize.c](tokenize.c) - tokenizing function
  * 

