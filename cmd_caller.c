#include "shell.h"

/**
 * pathchecker - checks the path
 * @av: arguments
 * Return: 1
 */
int pathchecker(char *av[])
{
	char *path, *pathptr, *pathvar, *ptr, *pathenv = "PATH", *linect;
	int pathlen, cmdlen;


	for (ptr = av[0], cmdlen = 0; *ptr != 0; ptr++)
		cmdlen++;
	pathvar = _get_env(pathenv);
	if (pathvar != pathenv)
	{
		pathenv = pathvar;
		while (*pathvar != 0)
		{

			for (pathlen = 0, ptr = pathvar; *ptr != 0 && *ptr != ':'; ptr++)
				pathlen++;
			path = malloc(sizeof(char) * (cmdlen + pathlen + 2));
			if (path == NULL)
			{
				free(pathenv);
				return (-1);
			}
			pathptr = path;
			while (*pathvar != ':' && *pathvar != 0)
				*pathptr++ = *pathvar++;
			if (pathptr != path)
				*pathptr++ = '/';
			ptr = av[0];
			while (*ptr != 0)
				*pathptr++ = *ptr++;
			*pathptr = 0;
			if (!access(path, F_OK))
			{

				pathlen = cmd_caller(av, path);
				free(path);
				free(pathenv);
				return (pathlen);
			}
			free(path);
			if (*pathvar == ':')
				pathvar++;
		}
	}
	linect = intos(linecounter(0));
	path = get_var("0");
	str_printer(2, path, ": ", linect, ": ", av[0], ": not found\n", NULL);
	free(path);
	free(linect);
	if (pathenv != pathvar)
		free(pathenv);
	return (127);
}
/**
 * cmd_caller - calls commands
 * @av: arguments
 * @cmd: command
 * Return: retval
 */
int cmd_caller(char *av[], char *cmd)
{
	pid_t command;
	int status;
	char *linect, *dolz;


	environ = get_all_env();
	if (environ == NULL)
		return (-1);

	command = fork();

	if (command == 0)
	{

		if (execve(cmd, av, *(get_environ())) == -1)
		{
			if (!access(cmd, F_OK))
			{
				printer(NULL);
				exit(126);
			}
			else
			{
				linect = intos(linecounter(0));
				dolz = get_var("0");
				str_printer(2, dolz, ": ", linect, ": ", cmd, ": not found\n", NULL);
				free(dolz);
				free(linect);
				exit(127);
			}
			exit(1);
		}

	}
	else
	{
		wait(&status);
	}

	free(environ);
	return (status);
}
/**
 * builtin_call - calls builtin commands
 * @av: arguments
 * Return: retval
 */
int builtin_call(char *av[])
{
	int retval = 0;
	char *retstr;

	if (av[0] == NULL)
		return (0);

	if (!_strcmp(av[0], "exit"))
	{
		if (av[1] != NULL)
			if (av[1][0] >= '0' && av[1][0] <= '9')
			{
				retval = _atoi(av[1]);
				exit_clean(av);
				exit_hist();
				exit(retval);
			}
			else
			{
				printer(": exit: Illegal number: ");
				str_printer(STDERR_FILENO, av[1], "\n", NULL);
				retval = 2;
			}
		else
		{
			retstr = get_var("?");
			retval = _atoi(retstr);
			free(retstr);
			exit_clean(av);
			exit_hist();
			exit(retval);
		}
	}
	else if (!_strcmp(av[0], "cd"))
		retval = _cd(av);
/*
 *
 * else if (!_strcmp(av[0], "getenv"))
 *	retval = !printf("%s\n", _get_env(av[1]));
*/
	else if (!_strcmp(av[0], "history"))
		retval = print_hist();
	else if (!_strcmp(av[0], "help"))
		retval = help(av[1]);
	else if (!_strcmp(av[0], "env"))
		retval = _print_env();
	else if (!_strcmp(av[0], "setenv"))
		retval = _set_env(av[1], av[2]);
	else if (!_strcmp(av[0], "unsetenv"))
		retval = _unset_env(av[1]);
	else if (!_strcmp(av[0], "alias"))
		retval = alias_cmd(av);
	else if (!_strcmp(av[0], "unset"))
		retval = unset_var(av[1]);
	else if (!_strcmp(av[0], "unalias"))
		retval = unset_alias(av[1]);
	else if (av[0][0] != '/' &&
		 !(av[0][0] == '.' && (av[0][1] == '/' ||
				       (av[0][1] == '.' && av[0][2] == '/'))))
		retval = pathchecker(av);
	else
		retval = cmd_caller(av, av[0]);

	if (retval % 256 == 0)
		retval /= 256;
	retstr = intos(retval % 128);

	set_var("?", retstr);
	free(retstr);
	return (retval);
}
