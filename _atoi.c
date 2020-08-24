#include "shell.h"
/**
 * _atoi - converts string to number
 * @s : pointer int
 *
 * _atoi: converts string to number
 *
 * Return: int
 */
int _atoi(char *s)
{
	int i;
	int num_check;
	unsigned int sum;
	unsigned int j;
	int k;

	k = 0;
	num_check = 0;
	sum = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] > '9' || s[i] < '0') && num_check > 0)
			break;
		if (s[i] == '-')
			k++;
		if (s[i] <= '9' && s[i] >= '9')
			num_check++;
		i++;
	}
	i = i - 1;
	j = 1;
	while (num_check > 0)
	{
		sum = sum + ((s[i] - '0') * j);
		j = j * 10;
		i--;
		num_check--;
	}
	if (k % 2 != 0)
		sum = sum * -1;
	return (sum);
}
