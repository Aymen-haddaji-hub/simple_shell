#include "shell.h"
/**
 * unset_var - unset shell var
 * @name: name of var to unset
 * Return: int
 */
int unset_var(char *name)
{
	ShellVar *vars = *get_vars();
	ShellVar *ptr = vars, *next;


	if (vars == NULL)
		return (0);

	if (!_strcmp(ptr->name, name))
	{

		*vars = *vars->next;
		free(ptr->name);
		free(ptr->val);
		free(ptr);
		return (0);
	}
	while (ptr->next != NULL && _strcmp(ptr->next->name, name))
		ptr = ptr->next;
	if (!_strcmp(ptr->next->name, name))
	{
		next = ptr->next->next;
		free(ptr->next->name);
		free(ptr->next->val);
		free(ptr->next);
		ptr->next = next;
	}
	return (0);
}
