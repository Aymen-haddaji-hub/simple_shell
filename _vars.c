#include "shell.h"
/**
 * _vars - initialize variables
 * @ac: arguemnts int
 * @av: strings
 * Return: int
 */
int _vars(int ac, char **av)
{
	ShellVar **specroot = get_special();
	ShellVar *spc;
	ShellVar *ptr;
	int i = 0;
	char numbers[2] = {0, 0};
	*specroot = malloc(sizeof(ShellVar) * 15);
	if (*specroot == NULL)
		return (-1);
	spc = *specroot;

	spc->val = _strdup("0");
	spc->name = _strdup("?");
	ptr = spc + 1;
	spc->next = ptr;
	while (av[i] != NULL)
	{
		numbers[0] = i + '0';
		ptr->val = _strdup(av[i]);
		ptr->name = _strdup(numbers);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	while (i < 10)
	{
		numbers[0] = i + '0';
		ptr->val = _strdup("0");
		ptr->name = _strdup(numbers);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	ptr->name = _strdup("$");
	ptr->val = _strdup("0");
	ptr->next = ptr + 1;
	ptr = ptr->next;
	ptr->name = _strdup("#");
	ptr->val = intos(ac);
	ptr->next = NULL;
	return (0);
}
