#include <stdio.h>
/**
 * _atoi - converts string to integer
 *
 * @s: string to convert from
 *
 * Return: integer from conversion
 */
int _atoi(char *s)
{
	int sign = 1;
	unsigned int total = 0;
	char working = 0;

	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '-')
			sign = sign * -1;
		if (*s >= '0' && *s <= '9')
		{
			working = 1;
			total = total * 10 + *s - '0';
		}
		else if (*s < '0' || *s > '9')
		{
			if (working)
				break;
		}
		s++;
	}
	if (sign < 0)
		total = (-(total));
	return (total);
}

/**
 * _strlen - gets the length of a null byte terminated string
 * @str: string to check length of
 *
 * Return: length of string
 */
int _strlen(char *str)
{
	int len = 0;

	while (str[len])
		len++;
	return (len);
}
