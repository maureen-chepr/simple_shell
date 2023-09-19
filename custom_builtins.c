#include "coque.h"
#include <ctype.h>

/**
 * cust_cd - A function that changes directory
 * @comd: input command
 * @prevstatus: Status of the last executed command
 * Return: 0 on success, otherwise 1
 */
int cust_cd(char **comd, int prevstatus)
{
	char cwd[PATH_MAX], *dir, *oldpwd;
	int res = -1;
	(void)prevstatus;

	dir = comd[1];
	if (dir == NULL)
	{
		dir = getenv("HOME");
	}
	if (cust_strcmp("-", dir) == 0)
	{
		oldpwd = getenv("OLDPWD");
		if (oldpwd != NULL)
			dir = oldpwd;
	}
	res = chdir(dir);
	if (res == -1)
	{
		perror("./hsh");
		return (1);
	}
	getcwd(cwd, sizeof(cwd));
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", cwd, 1);
	return (0);
}

/**
 * shell_exit - A function that exits the shell
 * @comd: Input command
 * @input: User input
 * @cmdargs: Argument
 * @count: Number of count
 */
void shell_exit(char **comd, char *input, char **cmdargs, int count)
{
	int idx, status;

	if (comd[1] != NULL)
	{
		for (idx = 0; comd[1][idx] != '\0'; idx++)
		{
			if (!cust_isdigit(comd[1][idx]))
			{
				print_error(cmdargs, count, comd);
				free(input);
				free(comd);
				return;
			}
		}
		status = cust_atoi(comd[1]);
	}
	else
	{
		status = 0;
	}
	free(input);
	free(comd);
	exit(status);
}

/**
 * shell_help - A function that displays help information
 * for a built-in command
 * @comd: Input command
 * @prevstatus: Status of the last executed command
 * Return: 0 on success, otherwise -1
 */
int shell_help(char **comd, int prevstatus)
{
	char ch;
	int rbyte, fdes, fwrite;
	(void)prevstatus;

	fdes = open(comd[1], O_RDONLY);
	if (fdes < 0)
	{
		perror("Error: File not descriptible!");
		return (0);
	}
	for (; rbyte > 0;)
	{
		rbyte = read(fdes, &ch, 1);
		fwrite = write(STDOUT_FILENO, &ch, rbyte);
		if (fwrite < 0)
			return (-1);
	}
	write_char('\n');
	return (0);
}

/**
 * print_env - A function that prints env variable
 * @comd: Input command
 * @prevstatus: Status of the last executed command
 * Return: 0
 */
int print_env(char **comd, int prevstatus)
{
	int lgth;
	size_t idx = 0;
	(void)comd;
	(void)prevstatus;

	while (environ[idx] != NULL)
	{
		lgth = cust_strlen(environ[idx]);
		write(1, environ[idx], lgth);
		write(STDOUT_FILENO, "\n", 1);
		idx++;
	}
	return (0);
}

/**
 * shell_echo - A function that excutes echo
 * @status: Last executed command status
 * @comd: Input command
 * Return: 0
 */
int shell_echo(char **comd, int status)
{
	unsigned int  pid = getppid();
	char *route;

	if (cust_strncmp(comd[1], "$?", 2) == 0)
	{
		print_int(status);
		prints("\n");
	}
	else if (cust_strncmp(comd[1], "$$", 2) == 0)
	{
		print_no(pid);
		prints("\n");
	}
	else if (cust_strncmp(comd[1], "$PATH", 5) == 0)
	{
		route = cust_getenv("PATH");
		prints(route);
		prints("\n");
		free(route);
	}
	else
		return (dis_echo(comd));
	return (1);
}
