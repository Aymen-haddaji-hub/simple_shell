#include "shell.h"
#include <dirent.h>

/**
 * _get_pid - gets the pid of the currently running process
 *
 * Return: string of pid
 */
char *_get_pid()
{
	char *s;
	char *pid;
	int fd;
	char *name;
	char *file = "/proc/self/status";

	s = malloc(256);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);

	while (_get_line(&s, fd))
	{
		name = strtok(s, ":");
		if (!_strcmp(name, "Pid"))
		{
			pid = _strdup(strtok(NULL, "\n \t"));
			free(s);
			return (pid);
		}
		free(s);
		s = NULL;
	}
	return (NULL);
}
