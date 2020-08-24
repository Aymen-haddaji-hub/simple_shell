#include "shell.h"
/**
 * get_environ - a static wrapper that copies whole env
 * Return: the adress of the env
 */
char ***get_environ()
{
	static char **env;

	return (&env);
}
