#include "shell.h"

char ***get_environ();
ShellVar **get_special();
ShellVar **get_vars();
AliasData **getalist();

/**
 * exitclean- function that cleans up various vars before exiting
 *
 * @av: freed argumet list
 *
 * Return: void
 */
void exit_clean(char **av)
{
	ShellVar *spetr = *(get_special()), *snext;
	AliasData *apetr = *(getalist()), *anext;
	char **env = *(get_environ());
	int i = 0;

	if (av != NULL)
		for (i = 0; av[i] != NULL; i++)
			free(av[i]);
	i = 0;
	while (env[i] != NULL)
		free(env[i++]);
	free(env);
	while (spetr != NULL)
	{
		free(spetr->val);
		free(spetr->name);
		spetr = spetr->next;
	}
	free(*(get_special()));
	spetr = *(get_vars());
	while (spetr != NULL)
	{
		free(spetr->val);
		free(spetr->name);
		snext = spetr->next;
		free(spetr);
		spetr = snext;
	}
	while (apetr != NULL)
	{
		free(apetr->val);
		free(apetr->name);
		anext = apetr->next;
		free(apetr);
		apetr = anext;
	}
}
