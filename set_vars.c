#include "shell.h"
/**
 * set_var - sets shell var
 * @name: name of var
 * @val: value of var
 * Return: int
 */
int set_var(char *name, char *val)
{
	ShellVar **vars = get_vars();
	ShellVar *spc = *(get_special());
	ShellVar *ptr = spc, *new;

	while (_strcmp(ptr->name, name) && ptr->next != NULL)
			ptr = ptr->next;
	if (!_strcmp(ptr->name, name))
	{
		free(ptr->val);
		ptr->val = _strdup(val);
		return (0);
	}
	ptr = *vars;

	if (ptr == NULL)
	{
		new = malloc(sizeof(ShellVar));
		if (new == NULL)
			return (-1);
		new->name = _strdup(name);
		new->val = _strdup(val);
		new->next = NULL;
		*vars = new;
		return (0);
	}
	while (_strcmp(ptr->name, name) && ptr->next != NULL)
		ptr = ptr->next;
	if (ptr != NULL && !_strcmp(ptr->name, name))
	{
		free(ptr->val);
		ptr->val = _strdup(val);
	}
	else
	{
		new = malloc(sizeof(ShellVar));
		if (new == NULL)
			return (-1);
		new->name = _strdup(name);
		new->val = _strdup(val);
		new->next = NULL;
		ptr->next = new;
	}
	return (0);
}