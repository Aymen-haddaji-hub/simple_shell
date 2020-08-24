#include "shell.h"
/**
 * get_var - a functon that gets the shell variable
 * @name: shell var's name
 *
 * Return: the original arg if not found
 */
char *get_var(char *name)
{
	ShellVar *spc = *(get_special()), *vars = *(get_vars());
	ShellVar *pointr = spc;

	while (pointr != NULL && _strcmp(pointr->name, name))
	{

		pointr = pointr->next;
	}
	if (pointr != NULL)
	{

		return (_strdup(pointr->val));
	}
	pointr = vars;
	while (pointr != NULL && _strcmp(pointr->name, name))
	{

		pointr = pointr->next;
	}
	if (pointr == NULL)
	{

		return (name);
	}

	return (_strdup(pointr->val));
}
