#ifndef SHELLH
#define SHELLH

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "history.h"
#include "shellvars.h"
/*#include <string.h>*/

/* in.c */
int shintmode(void);

/*  _printenv.c */
int _printenv(void);

/*  cmdcall.c */
int builtincall(char *av[]);
int cmdcaller(char *av[], char *path);

/*  parser.c */
int parseargs(char **buf);

/*  errhandl.c */
int errhandl(int status);

/*  _getenv.c and getenviron.c */
char ***getenviron(void);
int setallenv(char **environ, char *add);
char *_getenv(char *avzero);
int _setenv(char *name, char *val);
int _unsetenv(char *name);
char **getallenv(void);

/*  string.c */
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *, char *);
char *_strdup(char *str);
char *_strcat(char *a, char *b);

/* utilities */
char *intos(int digits);
char *_strchr(char *s, char c);
int strprinter(int fd, char *str, ...);
int printer(char *);
int linecounter(int);

/*  cd.c */
int _cd(char *av[]);

/* alias.c */
int aliascmd(char **av);
char *getalias(char *name);
int unsetalias(char *name);

/* shellvars.c */
int _vars(int ac, char **av);
char *get_var(char *name);
int set_var(char *name, char *val);
int unset_var(char *name);
ShellVar **getspecial(void);
ShellVar **getvars(void);

/* _realloc.c */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* _strtok.c */
char *strtok(char *str, char *delim);

/* _getline.c */
int _getline(char **lineptr, int fd);

char *strtokqe(char *str, char *delim, int escflags);


/* _printenv.c */
int _printenv(void);
int _putchar(char c);

/* history.c*/
int sethist(char *cmd);
int print_hist(void);
int exit_hist(void);

/* help.c*/
int help(char *cmd);

/*  exitcleanup.c */
void exitcleanup(char **av);

/* _atoi*/
int _atoi(char *s);

char *_getpid(void);


#endif
