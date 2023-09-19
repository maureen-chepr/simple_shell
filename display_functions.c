#include "coque.h"
/**
 * print_no - A function that prints numbers
 * @n: The integer to be printed
 */
void print_no(int n)
{
	unsigned int int1;

	int1 = n;
	if (n < 0)
	{
		write_char(45);
		int1 = -n;
	}
	if (int1 / 10 != 0)
	{
		print_no(int1 / 10);
	}
	write_char((int1 % 10) + 48);
}

/**
 * print_int - A function that prints an integer
 * @n: Integer to be printed
 */
void print_int(int n)
{
	unsigned int n1;

	if (n < 0)
	{
		n1 = -n;
		write_char('-');
	}
	else
	{
		n1 = n;
	}
	if (n1 / 10)
	{
		print_no(n1 / 10);
	}
	write_char((n1 % 10) + '0');
}


/**
 * print_error - A function that prints an error message
 * @cmdargs: Argument
 * @result: A program running the shell
 * @comd: Command specifier
 */
void print_error(char **cmdargs, int result, char **comd)
{
	char *prevstatus = cust_itoa(result, 10);

	prints(cmdargs[0]);
	prints(": ");
	prints(prevstatus);
	prints(": ");
	prints(comd[0]);
	prints(": Illegal number: ");
	prints(comd[1]);
	prints("\n");
	free(prevstatus);
}

/**
 * _token - A function that tokenizes a line of input
 * @input: User input
 * Return: NULL or array of characters
 */
char **_token(char *input)
{
	char **prev, *new;
	int idx = 0, bsize = BUFSIZE;

	prev = malloc(sizeof(char *) * bsize);
	if (input == NULL || prev == NULL)
	{
		perror("hsh");
		return (NULL);
	}
	new = cust_strtok(input, "\n ");
	while (new != NULL)
	{
		prev[idx] = new;
		new = cust_strtok(NULL, "\n ");
		idx++;
	}
	prev[idx] = NULL;
	return (prev);
}

/**
 * dis_error - A function that displays command error
 * @input: User input
 * @count: Number of count
 * @cmdargs: Argument
 */
void dis_error(char *input, int count, char **cmdargs)
{
	char *prevstatus;

	prints(cmdargs[0]);
	prints(": ");
	prevstatus = cust_itoa(count, 10);
	prints(prevstatus);
	free(prevstatus);
	prints("1: ");
	prints(input);
	prints(": not found\n");
}
