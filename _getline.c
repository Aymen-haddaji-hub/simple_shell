#include "shell.h"
/**
 * _get_line - a function that gets a line from fd or std input
 * @lineptr: buffer to fill line with
 * @fd: file descriptor
 * Return: num of characters
 */
int _get_line(char **lineptr, int fd)
{
	int size = 1025;
	int old_size = 0;
	int j = 1;
	int k = 0;
	static char buffer[1025];
	static int begin;
	static int end;
	int c = 0;
	int d;

	if (fd == -2)
	{
		begin = 0;
		end = 0;
	}

	if (lineptr == NULL)
	{
		return (0);
	}
	if (*lineptr == NULL)
	{
		*lineptr = malloc(sizeof(char) * size + 1);
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (begin == end)
		{
			while (k < 1024 && j != 0)
			{
				j = read(fd, buffer + k, 1024 - k);
				begin = 0;
				k += j;
				end = k;
				
				for (d = 0; j != 0 && d < end; d++)
					if (buffer[d] == '\n')
						j = 0;
			}
			if (k == 0)
			{
				buffer[0] = 0;
				return (k);
			}
			buffer[k] = 0;
			k = 0;
		}
		for (; buffer[begin]; begin++)
		{
			if (begin == 1024)
			{
				
				break;
			}
			
			if (buffer[begin] == '\n')
			{
				(*lineptr)[c] = '\n';
				begin++;
				c++;
				(*lineptr)[c] = '\0';
				return (c);
			}
			else
			{
				(*lineptr)[c] = buffer[begin];
			}
			c++;
		}
		if (c + begin >= 1024)
		{
			old_size = size;
			size = size + 1024;
			*lineptr = _realloc(*lineptr, old_size, size);
			if (*lineptr == NULL)
			{
				return (-1);
			}
		}
		else
		{
			(*lineptr)[old_size + begin] = 0;
			return (c);
		}
		
	}
}
