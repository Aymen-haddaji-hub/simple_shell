#include "shell.h"
/**
 * get_all_env - a function that gets all env
 * Return: env
 *
 */
char **get_all_env()
{
	char **env = *(get_environ());
	char **envcp;
	size_t length = 0;

	envcp = env;
	while (envcp[length] != NULL)
		length++;
	envcp = malloc(sizeof(char **) * (length + 1));
	if (envcp == NULL)
		return (NULL);
	while (length > 0)
	{
		envcp[length] = env[length];
		length--;
	}
	envcp[length] = env[length];
	return (envcp);
}
