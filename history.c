#include "shell.h"
/**
 * _history - gets the history list
 * Return: 0 uposon success
 */
HistList **_history()
{
	static HistList *h_list;

	return (&h_list);
}
/**
 * sethist - set hist and value
 * @cmd: command
 * Return: 0 upon success
 */
int sethist(char *cmd)
{
	HistList **h_list_root = _history();
	HistList *h_list = *h_list_root;
	HistList *ptr = h_list, *new;

	if (h_list == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);

		new->cmd = _strdup(cmd);
		new->next = NULL;
		*h_list_root = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;

	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}
/**
 * print_hist - prints all elements of listint
 *
 * Return: num of elements
 */
int print_hist(void)
{
	HistList **h_list_root = _history();
	HistList *h = *h_list_root;
	int i;
	int len, numlen;
	char *s, *num;

	i = 0;
	while (h != NULL)
	{
		len = _strlen(h->cmd);
		s = h->cmd;
		num = intos(i);
		numlen = _strlen(num);
		write(1, num, numlen);
		_putchar(' ');
		write(1, s, len);
		h = h->next;
		i++;
	}
	return (i);
}
/**
 * exit_hist - exit history and copy to file
 *
 * Return: int
 */
int exit_hist(void)
{

	int fd;
	char *file = ".simple_shell_history";
	int len;
	char *s;

	HistList **h_list_root = _history();
	HistList *h_list = *h_list_root;
	HistList *ptr = h_list;

/*
 *	file = tildeexpand(file);
 */
	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (-1);

	while (h_list != NULL)
	{
		ptr = h_list->next;
		s = h_list->cmd;
		len = _strlen(s);
		write(fd, s, len);
		free(h_list->cmd);
		free(h_list);
		h_list = ptr;
	}

	close(fd);


	return (1);
}
