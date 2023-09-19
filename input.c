#include "coque.h"
/**
 * cust_getline - A function that  reads user input from the standard input
 * Return: NULL or user input
 */
char *cust_getline()
{
	int idx = 0, bsize = BUFSIZE, rbyte;
	char ch = 0;
	char *buffer = malloc(bsize);

	if (buffer == NULL)
	{
		free(buffer);
		return (NULL);
	}
	while (ch != EOF && ch != '\n')
	{
		fflush(stdin);
		rbyte = read(STDIN_FILENO, &ch, 1);
		if (rbyte == 0)
		{
			free(buffer);
			exit(EXIT_SUCCESS);
		}
		buffer[idx] = ch;
		if (buffer[0] == '\n')
		{
			free(buffer);
			return (NULL);
		}
		if (idx >= bsize)
		{
			buffer = cust_realloc(buffer, bsize, bsize + 1);
			if (buffer == NULL)
				return (NULL);
		}
		idx++;
	}
	buffer[idx] = '\0';
	_fhashtag(buffer);
	return (buffer);
}

/**
 * _fhashtag - A function that handles comments after hashtag
 * @buffer: User input
 */
void _fhashtag(char *buffer)
{
	int idx = 0, in_comment = 0, escape = 0;

	while (buffer[idx] != '\0')
	{
		if (!escape)
		{
			if (buffer[idx] == '\\')
				escape = 1;
		}
		else if (buffer[idx] == '#' && !in_comment)
		{
			buffer[idx] = '\0';
			break;
		}
		else if (buffer[idx] == '"')
			in_comment = !in_comment;
		else
			escape = 0;
		idx++;
	}
}

/**
 * cmd_records - A function that writes user input to a file that
 * stores shell history
 * @input: User input
 * Return: 0 on success, otherwise -1
 */
int cmd_records(char *input)
{
	ssize_t fdes, fwrt;
	char *fname = ".shell_cmd_record";

	if (!input || !fname)
		return (-1);
	fdes = open(fname, O_CREAT | O_RDWR | O_APPEND, 00600);
	if (fdes < 0)
		return (-1);
	fwrt = write(fdes, input, cust_strlen(input));
	if (fwrt < 0)
	{
		close(fdes);
		return (-1);
	}
	fwrt = write(fdes, "\n", 1);
	if (fwrt < 0)
	{
		close(fdes);
		return (-1);
	}
	close(fdes);
	return (1);
}

/**
 * clear_env - A function that frees the memory allocated
 * for an array of env variables
 * @var_env: Env variable
 */
void clear_env(char **var_env)
{
	int idx = 0;

	while (var_env[idx] != NULL)
	{
		free(var_env[idx]);
		idx++;
	}
}

/**
 * shell_hist - A function that shows the history of user input
 * @cmd: User command
 * @status: Latest status
 * Return: 0 on success, otherwise -1
 */
int shell_hist(char **cmd, int status)
{
	int count;
	size_t lgth = 0;
	char *prevstatus, *cmdline = NULL;
	char *fname = ".shell_cmd_record";
	FILE *fptr;

	(void)cmd;
	(void)status;
	fptr = fopen(fname, "r");
	if (fptr == NULL)
		return (-1);
	for (count = 0; (getline(&cmdline, &lgth, fptr)) != -1; count++)
	{
		count++;
		prevstatus = cust_itoa(count, 10);
		prints(prevstatus);
		free(prevstatus);
		prints(" ");
		prints(cmdline);
	}
	if (cmdline)
		free(cmdline);
	fclose(fptr);
	return (0);
}
