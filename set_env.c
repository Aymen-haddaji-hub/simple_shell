#include "shell.h"
/**
 * _set_env - set environment for new value
 * @name: name of variable
 * @val: value of variable
 * Return: 0 or set_all_env if success, -1 if fail
 */
int _set_env(char *name, char *val)
{
	char ***envroot = get_environ();
	char **env = *envroot;
	int i, j, k, l;
	char *s, *ptr;


	if (name == NULL || val == NULL)
		return (0);
	k = _strlen(name);
	l = _strlen(val);
	ptr = malloc(sizeof(char) * (k + l + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	_strcpy(s, name);
	s += k;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += l;
	*s = 0;

	i = 0;
	while (env[i] != NULL)
	{
		s = env[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
				free(env[i]);
				env[i] = ptr;
				return (0);
			}
		}
		i++;
	}
	return (set_all_env(*envroot, ptr));
}
