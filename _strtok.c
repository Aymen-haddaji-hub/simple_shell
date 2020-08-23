#include "shell.h"
/**
 * strtok - a function that tokenizes a string
 * @str: string to tokenize
 * @delim: delimiters used to create tokens
 * Return: token
 */
char *strtok(char *str, char *delim)
{
	static char *saved_string;
	int i;
	int j;
	char *tmp_str;
	char *tmp_delim;

	if (str == 0)
		str = saved_string;
	if (str == 0)
		return (0);

	tmp_str = str;
	tmp_delim = delim;
	i = 0;
	while (tmp_str[i] != 0)
	{
		j = 0;
		while (delim[j] != 0)
		{
			if (tmp_str[i] == tmp_delim[j])
				break;
			j++;
		}
		if (tmp_delim[j] == 0)
			break;
		i++;
	}
	str = str + i;
	if (*str == 0)
	{
		saved_string = str;
		return (0);
	}
	tmp_str = tmp_str + i;

	i = 0;
	while (tmp_str[i] != 0)
	{
		j = 0;
		while (tmp_delim[j] != 0)
		{
			if (tmp_str[i] == tmp_delim[j])
				break;
			j++;
		}
		if (tmp_delim[j] != 0)
			break;
		i++;
	}
	saved_string = tmp_str;
	if (tmp_str[i] != 0)
	{
		saved_string = (saved_string + i + 1);
		tmp_str[i] = '\0';
	}
	else
	{
		saved_string = '\0';
	}
	return (tmp_str);
}
