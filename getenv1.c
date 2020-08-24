#include "shell.h"
/**
 * _get_env - function that gets local environment
 * @name: the variable env
 * Return: str of the local env
 */
char *_get_env(char *name)
{
	char **env = *(get_environ());
	int i, j;
	char *s;


	i = 0;
	while (env[i] != NULL)
	{
		s = env[i];
		j = 0;

		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
				return (_strdup(s + j + 1));
		}
		i++;
	}
	return (name);
}
