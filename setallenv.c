#include "shell.h"
/**
 * set_all_env - q function that sets whole env for a new value
 * @envin: env
 * @newval: new added value
 * Return: 0 if success, -1 if failure
 */

int set_all_env(char **envin, char *newval)
{
	char ***env = get_environ();
	size_t length = 0;

	while (env[length] != NULL)
		length++;
	if (newval != NULL)
		length++;
	*env = malloc(sizeof(char **) * (length + 1));
	if (*env == NULL)
		return (-1);
	for (length = 0; envin[length] != NULL; length++)
		if (newval == NULL)
		{
			(*env)[length] = _strdup(envin[length]);
		}
		else
			(*env)[length] = envin[length];
	if (newval != NULL)
	{

		(*env)[length] = newval;
		length++;
	}
	(*env)[length] = NULL;

	if (newval != NULL)
		free(envin);
	return (0);
}
