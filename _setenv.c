#include "coque.h"
/**
 * shell_setenv - A function that sets a new environment variable
 * @input: A string representing the input
 * @prevstatus: Status code of the last executed command
 * Return: 0
 */
int shell_setenv(char **input, int prevstatus)
{
	char *nom, *val;

	(void)prevstatus;
	nom = cust_strtok(input[0], " \t\n");
	val = cust_strtok(NULL, " \t\n");
	if (nom == NULL || val == NULL)
	{
		prints("Wrong num of inputs\n");
		return (-1);
	}
	if (cust_setenv(nom, val, 1) != 0)
	{
		prints("Can't set env variable\n");
		return (-1);
	}
	return (0);
}

/**
 * shell_unsetenv - A function that deletes an environment variable
 * @input: A string representing the input
 * @prevstatus: Status code of the last executed command
 * Return: 0
 */
int shell_unsetenv(char **input, int prevstatus)
{
	char *parse;
	int unset_result = 0;

	(void)prevstatus;
	parse = cust_strtok(input[0], " \t\n");
	parse = cust_strtok(NULL, " \t\n");
	if (parse == NULL)
	{
		prints("Not enough inputs\n");
		return (-1);
	}
	while (parse != NULL)
	{
		unset_result++;
		cust_unsetenv(parse);
		parse = cust_strtok(NULL, " \t\n");
	}
	if (unset_result == 0)
	{
		prints("There is no variables to unset\n");
		return (-1);
	}
	return (0);
}

/**
 * cust_setenv - A function that checks if the env variable specified exists
 * @nom: Environment variable to be set
 * @val: Value to be assigned to the environment variable
 * @prev: A to be replaced
 * Return: NULL or a pointer
 */
int cust_setenv(char *nom, char *val, int prev)
{
	char **space, *new = NULL, **newdomain;
	char *dest = NULL, *src = NULL;
	size_t num = 0, lgth_nom = cust_strlen(nom);
	size_t lgth_val = cust_strlen(val);
	size_t lgth_first = lgth_nom + lgth_val + 2;

	for (space = environ; *space != NULL; ++space)
	{
		if (cust_strncmp(*space, nom, lgth_nom) == 0
				&& (*space)[lgth_nom] == '=')
		{
			if (prev != 0)
				return (0);
			new = malloc(lgth_first * sizeof(char));
			if (new == NULL)
				return (-1);
			cust_strcpy(new, nom);
			cust_strcat(new, "=");
			cust_strcat(new, val);
			free(*space);
			*space = new;
			return (0);
		}
	}
	while (environ[num] != NULL)
		++num;
	newdomain = malloc((num + 2) * sizeof(char *));
	if (newdomain == NULL)
	{
		return (-1);
	}
	dest = (char *)newdomain;
	src = (char *)environ;
	cust_memcpy(dest, src, num * sizeof(char *));
	newdomain[num] = new;
	newdomain[num + 1] = NULL;
	environ = newdomain;
	return (0);
}

/**
 * cust_unsetenv - A function that unsets environment variable
 * @nom: Environment variable
 * Return: 0
 */
int cust_unsetenv(char *nom)
{
	int ind1, ind2, slgth;

	slgth = cust_strlen(nom);
	for (ind1 = 0; environ[ind1] != NULL; ind1++)
	{
		if (cust_strncmp(nom, environ[ind1], slgth) == 0
				&& environ[ind1][slgth] == '=')
		{
			for (ind2 = ind1; environ[ind2] != NULL; ind2++)
				environ[ind2] = environ[ind2 + 1];
			return (0);
		}
	}
	return (-1);
}

/**
 * cust_isdigit - checks for a digit 0 through 9
 * @c: is the char to be checked
 * Return: 1 if c is a digit, otherwise 0
 */

int cust_isdigit(int c)
{

	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
