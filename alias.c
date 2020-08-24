#include "shell.h"
/**
 * getalist - static wrapper get_alias list
 * Return: address alist
 *
 */
AliasData **getalist()
{
	static AliasData *alist;

	return (&alist);
}
/**
 * get_alias - get alias value
 * returns original argument if not found
 * @name: name of alias
 * Return: original argument if not found, otherwise value
 */
char *get_alias(char *name)
{
	AliasData *alist = *(getalist());
	AliasData *ptr = alist;

	while (ptr != NULL && _strcmp(ptr->name, name))
	{

		ptr = ptr->next;
	}
	if (ptr == NULL)
	{

		return (name);
	}


	free(name);
	return (get_alias(_strdup(ptr->val)));
}
/**
 * setalias - set alias and value
 * @name: name of alias
 * @val: value to set alias to
 * Return: 0 upon success
 */
int setalias(char *name, char *val)
{
	AliasData **alistroot = getalist();
	AliasData *alist = *alistroot;
	AliasData *ptr = alist, *new;

	if (alist == NULL)
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->val = val;
		new->next = NULL;
		*alistroot = new;
		return (0);
	}
	while (_strcmp(ptr->name, name) && ptr->next != NULL)
		ptr = ptr->next;
	if (!_strcmp(ptr->name, name))
	{
		free(ptr->val);
		ptr->val = val;
		free(name);
	}
	else
	{
		new = malloc(sizeof(AliasData));
		if (new == NULL)
			return (-1);
		new->name = name;
		new->val = val;
		new->next = NULL;
		ptr->next = new;
	}
	return (0);
}
/**
 * unset_alias - unset alias of @name
 * @name: name of alias value to unset
 * Return: 0 if sucess
 */
int unset_alias(char *name)
{
	AliasData *alist = *(getalist());
	AliasData *ptr = alist, *next;

	if (alist == NULL)
		return (0);
	if (!(_strcmp(ptr->name, name)))
	{
		alist = alist->next;
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
		free(ptr->next);
		ptr->next = next;
	}
	return (0);
}
/**
 * alias_cmd - tokenizes arguments for alias command
 * @av: arguments
 * Return: 1
 */
int alias_cmd(char *av[])
{
	AliasData *alist = *(getalist());
	AliasData *ptr = alist;
	int i;
	char *name, *val;

	if (av[1] == NULL)
	{
		while (ptr != NULL)
		{
			str_printer(1, ptr->name, "='", ptr->val, "'\n", NULL);
			ptr = ptr->next;
		}
		return (0);
	}

	for (i = 1; av[i] != NULL; i++)
	{

		name = strtok(av[i], "=");
		val = strtok(NULL, "=");
		if (val != NULL)
		{

			name = _strdup(name);
			if (name == NULL)
				return (-1);
			val = _strdup(val);
			if (val == NULL)
			{
				free(name);
				return (-1);
			}
			setalias(name, val);
		}
		else
		{

			val = _strdup(name);
			val = get_alias(val);

			if (!_strcmp(val, name))
			{
				str_printer(1, "alias: ", name, " not found\n", NULL);
				free(val);
			}
			else
			{
				str_printer(1, name, "='", val, "'\n", NULL);
				free(val);
			}
		}
	}
	return (0);
}
