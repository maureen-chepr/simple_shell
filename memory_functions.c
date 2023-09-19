#include "coque.h"

/**
 * cust_calloc -  A function that allocates memory for an array
 * @arr_size: Array size
 * Return: void
 */
void *cust_calloc(unsigned int arr_size)
{
	unsigned int idx = 0;
	char *arr;

	arr = malloc(arr_size);
	if ((arr_size == 0) || arr == NULL)
		return (NULL);
	while (idx < arr_size)
	{
		arr[idx] = '\0';
		idx++;
	}
	return (arr);
}

/**
 * cust_realloc - A function that changes the size of the memory block
 * pointed to by ptr to size bytes
 * @p: Pointer
 * @prevlgth: Initial length of the pointer
 * @newlgth: New length of the pointer
 * Return: Void
 */
void *cust_realloc(void *p, unsigned int prevlgth, unsigned int newlgth)
{
	void *size;

	if (newlgth == prevlgth)
		return (p);
	if (newlgth == 0)
	{
		if (p)
			free(p);
		return (NULL);
	}
	size = malloc(newlgth);
	if (size == NULL)
		return (NULL);
	if (p == NULL)
	{
		set_array(size, '\0', newlgth);
		free(p);
	}
	else
	{
		cust_memcpy(size, p, prevlgth);
		free(p);
	}
	return (size);
}

/**
 * clear_mem - A function that frees char Pointer
 * @comd: Pointer to an array
 * @cmdline: Pointer to a character
 */
void clear_mem(char **comd, char *cmdline)
{
	free(comd);
	free(cmdline);
	comd = NULL;
	cmdline = NULL;
}

/**
 * cust_memcpy - A function that copies memory area
 * @dest: Destination string
 * @src: First str
 * @n: bytes
 * Return: 0
 */
char *cust_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int idx;

	for (idx = 0; idx < n; idx++)
		*(dest + idx) = *(src + idx);
	return (dest);
}

/**
 * set_array - A function that fills an array with a byte value
 * @arr: Pointer to an array
 * @bval: Byte value
 * @lgth: Array length
 * Return: void
 */
void *set_array(void *arr, int bval, unsigned int lgth)
{
	unsigned int idx;
	char *ptr = arr;

	for (idx = 0; idx < lgth; idx++)
	{
		*ptr = bval;
		ptr++;
	}
	return (arr);
}
