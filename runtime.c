#include "coque.h"

/**
 * exc_comd - A function that excutes a shell command
 * @comd: Input Command
 * @input: User input
 * @count: Count command not found
 * @cmdargs: Argument
 * Return: 0 on success, 1 for null command, and -1 for wrong Command
 */
int exc_comd(char **comd, char *input, int count, char **cmdargs)
{
	pid_t pid;
	int result;

	pid = fork();
	if (pid == -1 || *comd == NULL)
	{
		if (pid == -1)
			perror("Error: No child process!");
		return (-1);
	}
	if (pid == 0)
	{
		if (cust_strncmp(*comd, "./", 2) != 0 &&
				cust_strncmp(*comd, "/", 1) != 0)
			find_route(comd);
		if (execve(*comd, comd, environ) == -1)
		{
			dis_error(comd[0], count, cmdargs);
			free(input);
			free(comd);
			exit(EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	wait(&result);
	return (0);
}

/**
 * _rfile - A function that reads a command from a file
 * @fname: The filename
 * @cmdargs: Argument
 */
void _rfile(char *fname, char **cmdargs)
{
	FILE *fptr;
	size_t lgth = 0;
	int val = 0;
	char *cmdline = NULL;

	fptr = fopen(fname, "r");
	if (fptr == NULL)
		exit(EXIT_FAILURE);
	for (; (getline(&cmdline, &lgth, fptr)) != -1; val++)
		process_comd(cmdline, val, fptr, cmdargs);
	if (cmdline)
		free(cmdline);
	fclose(fptr);
	exit(0);
}

/**
 * _handle - A function that handles a builtin command
 * @comd: Input command
 * @prevstatus: Status code of the last executed command
 * Return: 0 on success, otherwise -1
 */
int _handle(char **comd, int prevstatus)
{
	built_func built[] = {
		{"env", print_env},
		{"help", shell_help},
		{"cd", cust_cd},
		{"history", shell_hist},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"echo", shell_echo},
		{NULL, NULL}
	};
	int idx;

	for (idx = 0; built[idx].cmdname; idx++)
	{
		if (cust_strcmp(comd[0], built[idx].cmdname) == 0)
			return (built[idx].funct(comd, prevstatus));
	}
	return (-1);
}

/**
 * process_comd - A function that checks if it is a built-in command or not
 * and executes based on the command
 * @cmdline: A line in the file
 * @val: Counter
 * @fptr: File pointer
 * @cmdargs: Argument
 */
void process_comd(char *cmdline, int val, FILE *fptr, char **cmdargs)
{
	int stats = 0;
	char **comd;

	comd = _token(cmdline);
	if (cust_strncmp(comd[0], "exit", 4) == 0)
		file_exit(comd, cmdline, fptr);
	else if (is_builtin(comd) == 0)
	{
		stats = _handle(comd, stats);
		free(comd);
	}
	else
	{
		stats = exc_comd(comd, cmdline, val, cmdargs);
		free(comd);
	}
}

/**
 * sig_handle - A function that handles signal
 * @signal: Signal
 */
void sig_handle(int signal)
{
	if (signal == SIGINT)
		prints("\n$ ");
}
