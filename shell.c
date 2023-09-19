#include "coque.h"

/**
 * main - Entry point simple shell
 * @arg: Number of arguments
 * @cmdargs: Argument
 * Return: Status
 */
int main(int arg, char **cmdargs)
{
	char *input, **comd;
	int count = 0, status = 1, stats = 0;
	(void)arg;

	if (cmdargs[1] != NULL)
		_rfile(cmdargs[1], cmdargs);
	signal(SIGINT, sig_handle);
	while (status)
	{
		count++;
		if (isatty(STDIN_FILENO))
			cmd_prompt();
		input = cust_getline();
		if (input[0] == '\0')
			continue;
		cmd_records(input);
		comd = _token(input);
		if (cust_strcmp(comd[0], "exit") == 0)
		{
			shell_exit(comd, input, cmdargs, count);
		}
		else if (is_builtin(comd) == 0)
		{
			stats = _handle(comd, stats);
			clear_mem(comd, input);
			continue;
		}
		else
			stats = exc_comd(comd, input, count, cmdargs);
		clear_mem(comd, input);
	}
	return (status);
}

/**
 * cmd_prompt - A function that displays the prompt
 */
void cmd_prompt(void)
{
	prints("coque$ ");
}
