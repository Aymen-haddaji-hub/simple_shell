#include "shell.h"
#include <stdarg.h>
/**
 * linecount - count the lines
 * @increment: incnrementer
 * Return: count
 */
int linecounter(int increment)
{
	static int count;

	count += increment;

	return (count);
}
/**
 * intos - converts integer to string
 * @digits: int
 * Return: a string
 */
char *intos(int digits)
{
	int count, i, j, k, digitT;
	char *output;

	digitT = digits;
	count = 0;
	j = 0;
	if (digits == 0)
	{
		output = malloc(sizeof(char) * 2);
		output[0] = '0';
		output[1] = 0;
		return (output);
	}
	if (digits < 0)
	{
		j = 1;
		count++;
	}
	while (digitT != 0)
	{
		digitT /= 10;
		count++;
	}
	output = malloc(sizeof(char) * count + 1);
	if (output == NULL)
		return (NULL);
	if (j)
		output[0] = '-';
	digitT = digits;
	for (i = count - 1; i >= 0 + j; i--)
	{
		k = digitT % 10;
		output[i] = (k < 0 ? -k : k) + '0';
		digitT /= 10;
	}
	output[count] = '\0';
	return (output);

}
/**
 * printer - printerrors
 * @str: string
 * null prints errno error with perror, otherwise print string as error
 * Return: 0
 */
int printer(char *str)
{
	char *pathname, *strnumb;

	pathname = get_var("0");
	strnumb = intos(linecounter(0));
	if (str != NULL)
	{
		str_printer(2, pathname, ": ", strnumb, str, NULL);
	}
	else
	{
		str_printer(2, pathname, ": ", strnumb, ": ", NULL);
		perror(NULL);
	}
	free(pathname);
	free(strnumb);
	return (0);
}
/**
 * str_printer - simple string printer, va args should have a NULL last arg
 * @fd: file descriptor
 * @str: string
 * Return: 0
 */
int str_printer(int fd, char *str, ...)
{
	va_list list;

	if (str == NULL)
		return (0);
	va_start(list, str);
	write(fd, str, _strlen(str));
	str = va_arg(list, char *);
	while (str != NULL)
	{
		write(fd, str, _strlen(str));
		str = va_arg(list, char *);
	}
	return (0);
}

/**
 * _str_chr - locates a character in a string
 * @s: char pointer
 * @c: char
 * _str_chr: locates character in a string and returns a pointer
 * to the first occurence of c in the string s
 *
 * Return: address of first occurence of c in s
 */
char *_str_chr(char *s, char c)
{
	int i;
	int j;

	i = 0;
	while (s[i] != '\0')
	{
		j++;
		i++;
	}

	i = 0;
	while (i <= j)
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (0);
}
