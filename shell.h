#ifndef SHELLH
#define SHELLH

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef SHELLVARH
#define SHELLVARH

/**
 * struct ShellVar - shellvar list node
 *
 * @name: name of var
 * @val: value of var
 * @next: next var in list
 */
typedef struct ShellVar
{
	char *name;
	char *val;
	struct ShellVar *next;
} ShellVar;

#endif

#ifndef HISTORY_H
#define HISTORY_H
/**
 * struct HistList - singly linked list
 * @cmd: command
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct HistList
{
	char *cmd;
	struct HistList *next;
} HistList;
#endif

#ifndef ALIASH
#define ALIASH
/**
 * struct AliasData - struct for alias function
 * @AliasData - name of struct
 * @name: name of alias value
 * @val: value for alias
 * @next: ptr to next node
 */
typedef struct AliasData
{
	char *name;
	char *val;
	struct AliasData *next;
} AliasData;

#endif

int shint_mode(void);


int _print_env(void);


int builtin_call(char *av[]);
int cmd_caller(char *av[], char *path);


int parse_args(char **buf);


int err_handler(int status);


char ***get_environ(void);
int set_all_env(char **environ, char *add);
char *_get_env(char *avzero);
int _set_env(char *name, char *val);
int _unset_env(char *name);
char **get_all_env(void);


size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *, char *);
char *_strdup(char *str);
char *_strcat(char *a, char *b);


char *intos(int digits);
char *_str_chr(char *s, char c);
int str_printer(int fd, char *str, ...);
int printer(char *);
int linecounter(int);


int _cd(char *av[]);


int alias_cmd(char **av);
char *get_alias(char *name);
int unset_alias(char *name);


int _vars(int ac, char **av);
char *get_var(char *name);
int set_var(char *name, char *val);
int unset_var(char *name);
ShellVar **get_special(void);
ShellVar **get_vars(void);


void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);


char *strtok(char *str, char *delim);


int _get_line(char **lineptr, int fd);

char *strtoken(char *str, char *delim, int escflags);



int _printenv(void);
int _putchar(char c);


int sethist(char *cmd);
int print_hist(void);
int exit_hist(void);


int help(char *cmd);


void exit_clean(char **av);


int _atoi(char *s);

char *_get_pid(void);


#endif




