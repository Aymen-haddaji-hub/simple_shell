#include "shell.h"
/**
 * _unset_env - unset environment
 * @name: name of variable to unset
 * Return: 0 if sucess
 *
 * testing functionality  copy environ, if hits skip over, realloc
 */
int _unset_env(char *name)
{
	char **envir = *get_environ();
	int i, j;
	int check = 0;
	char *s;
	char **env;
	
	if (name == NULL)
		return (0);

	i = 0;
	while (envir[i] != NULL)
	{
		s = envir[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (s[j] == '=' && name[j] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		i++;
	}
	free(envir[i]);
	while (envir[i] != NULL)
	{
		envir[i] = envir[i + 1];
		i++;
	}
	envir[i] = NULL;
	env = envir;
	set_all_env(env, NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
