#include "coque.h"
/**
 * find_match - A function that checks if a char matches another
 * @ch: Char to be checked
 * @stg: String to be checked
 * Return: 1 if success, otherwise 0
 */
unsigned int find_match(char ch, const char *stg)
{
	unsigned int idx = 0;

	while (stg[idx] != '\0')
	{
		if (ch == stg[idx])
			return (1);
		idx++;
	}
	return (0);
}

/**
 * is_builtin - A function that checks if a command is builtin
 * @comd: A command to be checked
 * Return: 0 on success, otherwise -1
 */
int is_builtin(char **comd)
{
	built_func funct[] = {
		{"env", NULL},
		{"help", NULL},
		{"cd", NULL},
		{"history", NULL},
		{"setenv", NULL},
		{"unsetenv", NULL},
		{"echo", NULL},
		{NULL, NULL}
	};
	int idx = 0;

	if (*comd == NULL)
		return (-1);
	while ((funct + idx)->cmdname)
	{
		if (cust_strcmp(comd[0], (funct + idx)->cmdname) == 0)
			return (0);
		idx++;
	}
	return (-1);
}

/**
 * cust_strtok - A function that tokenizes a string
 * @stg: String
 * @sep: Separator
 * Return: NULL or a pointer to a string
 */
char *cust_strtok(char *stg, const char *sep)
{
	static char *ch1, *ch2;
	unsigned int idx = 0;

	if (stg != NULL)
		ch2 = stg;
	ch1 = ch2;
	if (ch1 == NULL)
		return (NULL);
	while (ch1[idx] != '\0')
	{
		if (find_match(ch1[idx], sep) == 0)
			break;
		idx++;
	}
	if (ch2[idx] == '\0' || ch2[idx] == '#')
	{
		ch2 = NULL;
		return (NULL);
	}
	ch1 = ch2 + idx;
	ch2 = ch1;
	while (ch2[idx] != '\0')
	{
		if (find_match(ch2[idx], sep) == 1)
			break;
		idx++;
	}
	if (ch2[idx] == '\0')
		ch2 = NULL;
	else
	{
		ch2[idx] = '\0';
		ch2 = ch2 + idx + 1;
		if (*ch2 == '\0')
			ch2 = NULL;
	}
	return (ch1);
}

/**
 * shell_env - A function that prints env variables in the shell
 * @array: Array of variable
 */
void shell_env(char **array)
{
	int idx;

	for (idx = 0; environ[idx]; idx++)
		array[idx] = cust_strdup(environ[idx]);
	array[idx] = NULL;
}

/**
 * cust_memset - function that fills memory with a constant byte.
 * @s: pointer to the memory area
 * @n: bytes of the memory
 * @b: value to be filled with n bytes
 * Return: (s)
 */

char *cust_memset(char *s, char b, unsigned int n)
{
	unsigned int idx;

	for (idx = 0; idx < n; idx++)
	{
		*(s + idx) = b;
	}
	return (s);
}
