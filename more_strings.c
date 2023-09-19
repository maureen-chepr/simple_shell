#include "coque.h"

/**
 * cust_itoa - A function that converts integer to string
 * @integer: Integer to be converted
 * @base: Integer
 * Return: NULL or pointer
 */
char *cust_itoa(unsigned int integer, int base)
{
	int lgth = 0, idx, digit;
	char *str;

	if (base < 2 || base > 36)
		return (NULL);
	lgth = size_int(integer);
	str = malloc(lgth + 1);
	if (!str)
		return (NULL);
	*str = '\0';
	for (idx = 0; integer / 10; idx++)
	{
		digit = integer % base;
		str[idx] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
		integer /= base;
	}
	reverse_array(str, lgth);
	str[idx] = '\0';
	return (str);
}

/**
 * size_int - A function that finds the length of an integer
 * @nb: Integer
 * Return: Length of the integer
 */
int size_int(int nb)
{
	int lgth;

	if (nb < 0)
		nb = -nb;
	if (nb == 0)
		return (1);
	for (lgth = 0; nb != 0; lgth++)
		nb /= 10;
	return (lgth);
}

/**
 * cust_strcmp - A function that compares two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if same string
 */
int cust_strcmp(char *s1, char *s2)
{
	int ret_val = 0, idx;

	if (s1 == NULL || s2 == NULL)
		return (1);
	if (cust_strlen(s1) != cust_strlen(s2))
		return (1);
	for (idx = 0; s1[idx]; idx++)
	{
		if (s1[idx] != s2[idx])
		{
			ret_val = s1[idx] - s2[idx];
			break;
		}
		else
			continue;
	}
	return (ret_val);
}

/**
 * reverse_array - A function that reverses an array of integers
 * @array: Array to be reversed
 * @elt: Elements in the array
 */
void reverse_array(char *array, int elt)
{
	int idx, retval;

	for (idx = 0; idx < elt; idx++, elt--)
	{
		retval = array[idx];
		array[idx] = array[elt];
		array[elt] = retval;
	}
}

/**
 * cust_isalpha - A function that checks for an alphabetic character
 * @ch: Character to be checked
 * Return: 1 if lowercase and 0 otherwise
 */
int cust_isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	return (0);
}
