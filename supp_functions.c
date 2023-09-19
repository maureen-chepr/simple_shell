#include "coque.h"

/**
 * cust_strlen - A function that returns the length of a string
 * @s: String to be checked
 * Return: 0
 */

int cust_strlen(char *s)
{
	int lgth = 0;

	while (s[lgth] != '\0')
	{
		lgth++;
	}
	return (lgth);
}

/**
 * cust_strncpy - A function that copies a string
 * @dest: First string
 * @src: Second string
 * @n: number of bytes
 * Return: dest
 */

char *cust_strncpy(char *dest, char *src, int n)
{
	int idx;

	for (idx = 0; idx < n && src[idx] != '\0'; idx++)
	{
		dest[idx] = src[idx];
	}
	for ( ; idx < n; idx++)
	{
		dest[idx] = '\0';
	}
	return (dest);
}

/**
 * cust_atoi - A function that convert a string to an integer
 * @s: String to be converted
 * Return: 0
 */
int cust_atoi(char *s)
{
	int ind, a, n, lgth, b, dgit;

	ind = 0;
	a = 0;
	n = 0;
	lgth = 0;
	b = 0;
	dgit = 0;

	while (s[lgth] != '\0')
		lgth++;
	while (ind < lgth && b == 0)
	{
		if (s[ind] == 45)
			++a;
		if (s[ind] >= 48 && s[ind] <= 57)
		{
			dgit = s[ind] - 48;
			if (a % 2)
				dgit = -dgit;
			n = n * 10 + dgit;
			b = 1;
			if (s[ind + 1] < 48 || s[ind + 1] > 57)
				break;
			b = 0;
		}
		ind++;
	}
	if (b == 0)
		return (0);
	return (n);
}

/**
 * cust_puts - A function that prints a string
 * @stg: String to be printed
 */
void cust_puts(char *stg)
{
	int a = 0;

	while (a >= 0)
	{
		if (stg[a] == '\0')
		{
			write_char('\n');
			break;
		}
		write_char(stg[a]);
		a++;
	}
}

/**
 * write_char - A function that writes a character
 * @ch: Character to be printed
 * Return: 1 on success, otherwise -1
 */
int write_char(char ch)
{
	return (write(1, &ch, 1));
}

