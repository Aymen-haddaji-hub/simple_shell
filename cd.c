#include "shell.h" 
/**
 *_cd - change directory builtin
 * @av: argument
 * Return: int ret
 */
int _cd(char *av[])
{
	char *oldpwd = NULL, *new_path, *path_bit, *new_ptr;
	char *home_str = "HOME", *old_pwdstr = "OLDPWD";
	int ret, print_path = 0;

	oldpwd = getcwd(oldpwd, 0);
	if (oldpwd == NULL)
		return (1);
	if (av[1] == NULL || av[1][0] == 0)
	{
		new_path = _get_env(home_str);
		if (new_path == home_str)
			new_path = _strdup("");
		av[1] = new_path;
		av[2] = NULL;
	}
	else if (av[1][0] == '-' && av[1][1] == 0)
	{
		/*check getenv malloc error here and above*/
		new_path = _get_env(old_pwdstr);
		if (new_path == old_pwdstr)
			new_path = _strdup("");
		print_path = 1;
		free(av[1]);
		av[1] = new_path;
	}
	

	new_path = malloc(sizeof(char) * (_strlen(oldpwd) + _strlen(av[1]) + 2));
	if (new_path == NULL)
		return (-1);
	new_ptr = new_path;
	path_bit = oldpwd;
	if (av[1][0] != '/' && path_bit[1] != 0)
		while (*path_bit)
			*new_ptr++ = *path_bit++;
	*new_ptr++ = '/';
	path_bit = strtok(av[1], "/");

	while (path_bit != NULL)
	{
		if (path_bit[0] == '.' && path_bit[1] == '.'
		    && path_bit[2] == 0)
		{

			new_ptr--;
			if (new_ptr != new_path)
				new_ptr--;
			while (*new_ptr != '/')
				new_ptr--;
			*new_ptr++ = '/';
		}
		else if (!(path_bit[0] == '.' && path_bit[1] == 0))
		{
			while (*path_bit)
				*new_ptr++ = *path_bit++;
			*new_ptr++ = '/';
		}
		path_bit = strtok(NULL, "/");

	}
	if (new_ptr != new_path && new_ptr != new_path + 1)
		new_ptr--;
	*new_ptr = 0;

	
	ret = chdir(new_path);
	if (ret == 0)
	{
		_set_env("OLDPWD", oldpwd);
		free(oldpwd);
		_set_env("PWD", new_path);
		if (print_path)
			str_printer(1, new_path, "\n", NULL);
		free(new_path);
		return (0);
	}
	printer(": cd: can't cd to ");
	str_printer(STDERR_FILENO, av[1], "\n", NULL);
	free(oldpwd);
	free(new_path);
	return (ret);
}
