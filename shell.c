 #include "shell.h"
/**
 * input_validator - validates input buffer
 * @buf: buffer
 * @fd: file descriptor
 * Return: return command value
 */
int input_validator(char **buf, int fd)
{
	char *newb, *bufgl, *bufptr = *buf;
	ssize_t lenghtr;
	size_t lenghtbuf;
	int start = 1;
	int complete = 0;

	linecounter(1);
	if (*bufptr == 0)
		return (0);
	while (*bufptr)
	{

		while ((*bufptr == ' ' || *bufptr == '\n') && !(complete & 3))
			bufptr++;
		if (*bufptr == 0)
			break;
		if (start)
		{
			if (*bufptr == ';' && *(bufptr + 1) == ';')
			{
				free(*buf);
				printer(": Syntax error \";;\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			if (*bufptr == ';')
			{
				free(*buf);
				printer(": Syntax error \";\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			if (*bufptr == '&' && *(bufptr + 1) == '&')
			{
				free(*buf);
				printer(": Syntax error \"&&\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			if (*bufptr == '&')
			{
				free(*buf);
				printer(": Syntax error \"&\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			if (*bufptr == '|' && *(bufptr + 1) == '|')
			{
				free(*buf);
				printer(": syntax error \"||\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			if (*bufptr == '|')
			{
				free(*buf);
				printer(": syntax error \"|\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			start = 0;
		}
		if (bufptr[0] == '\n' && bufptr[1] == 0)
			break;
		if (*bufptr == '#' &&
		    !(complete & 3) &&
		    (bufptr == *buf || *(bufptr - 1) == ' '))
		{
			*bufptr = 0;
			break;
		}
		complete &= ~4;

		if (*bufptr == '"' && !(complete & 3))
		{
			complete |= 2;
			bufptr++;
			continue;
		}
		if (*bufptr == '"' && complete & 2)
			complete &= ~2;
		if (*bufptr == '\'' && !(complete & 3))
		{
			complete |= 1;
			bufptr++;
			continue;
		}
		if (*bufptr == '\'' && complete & 1)
			complete &= ~1;
		if (bufptr[0] == '&' && !(complete & 3))
		{
			if (bufptr[1] == '&')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
			else if (bufptr[1] == '|')
			{
				free(*buf);
				printer(": syntax error \"|\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			else if (bufptr[1] == ';')
			{
				free(*buf);
				printer(": syntax error \";\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
		}
		if ((bufptr[0] == '|') && !(complete & 3))
		{
			if (bufptr[1] == '|')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
			else if (bufptr[1] == ';')
			{
				free(*buf);
				printer(": syntax error \";\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			else if (bufptr[1] == '&')
			{
				free(*buf);
				printer(": syntax error \"&\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
		}
		if (*bufptr == ';')
		{
			if (*(bufptr + 1) == ';')
			{
				free(*buf);
				printer(": Syntax error \";;\" unexpected\n");
				set_var("0", "2");
				return (2);
			}
			start = 1;
		}
		bufptr++;
	}

	if (complete & 7)
	{

		bufgl = NULL;
		if (isatty(fd))
			str_printer(1, ">", NULL);
		lenghtr = _get_line(&bufgl, fd);
		if (lenghtr == 0 && !isatty(fd))
		{
			free(buf);
			free(bufgl);
			printer(": Syntax error: unterminated quoted string\n");
			return (-1);
		}
		if (lenghtr == -1)
		{
			; 
		}
		lenghtbuf = _strlen(*buf);
		newb = malloc(lenghtbuf + lenghtr + 1);
		/* check malloc fail here */
		_strcpy(newb, *buf);
		_strcpy(newb + lenghtbuf, bufgl);
		free(*buf);
		free(bufgl);

		return (input_validator(&newb, fd));
	}

	/*history begin*/
	sethist(*buf);
	/*end history*/
	return (parse_args(buf));
}

/**
 * shint_mode - shell interactive mode
 * Return: 0
 */
int shint_mode(void)
{
	char *bufgl = NULL, *pwd;
	ssize_t lenghtr = 0, off_lag = 0, ret = 0;
	int istty = isatty(0) && isatty(1);

	while (!off_lag)
	{

		if (istty)
		{
			pwd = _get_env("PWD");
			if (pwd != NULL)
			{
				str_printer(1, "simplesh:", pwd, "$", NULL);
				free(pwd);
			}
			else
			{
				str_printer(1, "simplesh$", NULL);
			}
		}
		lenghtr = _get_line(&bufgl, STDIN_FILENO);
		if (lenghtr == 0 || lenghtr == -1)
		{
			free(bufgl);
			break;
		}
		if (bufgl[lenghtr - 1] != '\n')
			off_lag = 1;

		ret = input_validator(&bufgl, STDIN_FILENO);
		bufgl = NULL;
		if (off_lag)
			break;
	}
	return (ret);
}
/**
 * scriptmode - shell script mode
 * @av: arguments
 * Return: 0 upon success or -1 if failure
 */
int scriptmode(char *av[])
{
	char *bufgl = NULL;
	int infile;
	ssize_t lenghtr = 0, off_lag = 0, ret = 0;

	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		str_printer(STDERR_FILENO, av[0], ": 0: Can't open ",
			   av[1], "\n", NULL);
		return (127);
	}
	while (!off_lag)
	{
		lenghtr = _get_line(&bufgl, infile);
		if (lenghtr == 0 || lenghtr == -1)
		{
			free(bufgl);
			break;
		}
		if (bufgl[lenghtr - 1] != '\n')
			off_lag = 1;

		ret = input_validator(&bufgl, STDIN_FILENO);
		bufgl = NULL;
		if (off_lag)
			break;
	}
	close(infile);
	return (ret);
}
/**
 * main - runs a shell
 *
 * @ac: args
 * @av: cmd line args
 * @environ: env
 *
 * Return: return value of last command
 */
int main(int ac, char *av[], char **environ)
{
	int ret = 0;

	char *pidptr;

	_vars(ac - 1, av);
	pidptr = _get_pid();
	set_var("$", pidptr);
	free(pidptr);
	_get_line(NULL, -2);

	set_all_env(environ, NULL);

	if (ac > 1)
		ret = scriptmode(av);
	else
		ret = shint_mode();
	exit_clean(NULL);
	exit_hist();
	return (ret);
}
