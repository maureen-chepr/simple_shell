#include "coque.h"

/**
 * cust_strdup - A function that returns a pointer to a newly allocated space
 * in memory, which contains a copy of the string given as a parameter
 * @stg: String
 * Return: Returns a pointer to the string, or NULL if insufficient memory
 */
char *cust_strdup(char *stg)
{
	unsigned int size;
	char *stg1;

	if (stg == NULL)
		return (NULL);
	size = cust_strlen(stg) + 1;
	stg1 = (char *)malloc(size * sizeof(char));
	if (stg1 == NULL)
		return (NULL);
	cust_memcpy(stg1, stg, size);
	return (stg1);
}

/**
 * cust_strchr - A function that locates a character in a string
 * @str: String
 * @ch: Character in a string
 * Return: NULL
 */
char *cust_strchr(char *str, char ch)
{
	int idx;

	for (idx = 0; str[idx] >= '\0'; idx++)
	{
		if (str[idx] == ch)
			return (&str[idx]);
	}
	return ('\0');
}

/**
 * cust_strcpy - A function that copies the string pointed to by src
 * @dest: Buffer pointer
 * @src: String pointed
 * Return: dest
 */
char *cust_strcpy(char *dest, char *src)
{
	int c = 0, idx;

	while (*(src + c) != '\0')
		c++;
	for (idx = 0; idx < c ; idx++)
		dest[idx] = src[idx];
	dest[c] = '\0';
	return (dest);
}

/**
 * cust_strcat - A function that concatenates two strings
 * @dest: First string
 * @src: Second string
 * Return: String
 */
char *cust_strcat(char *dest, char *src)
{
	int idx, strlgth1, strlgth2;

	strlgth1 = cust_strlen(dest);
	strlgth2 = cust_strlen(src);
	for (idx = 0; idx <= strlgth2; idx++)
	{
		dest[strlgth1 + idx] = src[idx];
	}
	return (dest);
}

/**
 * cust_strncmp - A function that compares the first n chars of s1 and s2
 * and returns an integer
 * @s1: First string
 * @s2: Second string
 * @n: Number of chars
 * Return: n
 */
int cust_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
