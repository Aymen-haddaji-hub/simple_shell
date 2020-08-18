#include "shell.h"
/**
 * strtokqe - string token with quotes and escapes
 * @str: string
 * @delim: delimiters
 * @escflags: escape flags
 * flags are bitwise.
 * 1 = use \ to escape delims
 * 2 = single quote skips
 * 4 = double quote skips
 * Return: string
 */
char *strtokqe(char *str, char *delim, int escflags)
{
	static char *saved_string;
	int i;
	int j;

	if (str == 0)
		str = saved_string;
	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		while (delim[j] != 0)
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] == 0)
			break;
		i++;
	}
	str = str + i;
	if (*str == 0)
	{
		saved_string = str;
		return (0);
	}

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\\' && escflags & 1)
		{
			if (str[i + 1] != 0)
				i++;
			i++;
			continue;
		}
		if (str[i] == '\'' && escflags & 2)
		{
			i++;
			while (str[i] != '\'')
			{
				if (str[i] == '\\' && escflags & 1)
				{
					if (str[i + 1] != 0)
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		if (str[i] == '"' && escflags & 4)
		{
			i++;
			while (str[i] != '"')
			{
				if (str[i] == '\\' && escflags & 1)
				{
					if (str[i + 1] != 0)
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		j = 0;
		while (delim[j] != 0)
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] != 0)
			break;
		i++;
	}
	saved_string = str;
	if (str[i] != 0)
	{
		saved_string = (saved_string + i + 1);
		str[i] = '\0';
	}
	else
	{
		saved_string = '\0';
	}
	return (str);
}
