#include "coque.h"

/**
 * find_route - A function that looks for executable command in the path
 * @comd: Input command
 * Return: 0 on success, otherwise 1
 */
int find_route(char **comd)
{
	struct stat buffer;
	char *pthcmd, *route, *result;

	route = cust_getenv("PATH");
	result = cust_strtok(route, ":");
	while (result != NULL)
	{
		pthcmd = cmd_build(*comd, result);
		if (stat(pthcmd, &buffer) == 0)
		{
			*comd = cust_strdup(pthcmd);
			free(pthcmd);
			free(route);
			route = NULL;
			return (0);
		}
		free(pthcmd);
		result = cust_strtok(NULL, ":");
	}
	free(route);
	return (1);
}

/**
 * cmd_build - A function that constructs the full path of an
 * executable command
 * @parse: A command to be excecuted
 * @dir: Directory of the command
 * Return: NULL or command full path
 */
char *cmd_build(char *parse, char *dir)
{
	size_t lgth, lgth1, lgth2;
	char *comd;

	lgth1 = cust_strlen(dir);
	lgth2 = cust_strlen(parse);
	lgth = lgth1 + lgth2 + 2;
	comd = malloc(sizeof(char) * lgth);
	if (comd == NULL)
		return (NULL);
	cust_memset(comd, 0, lgth);
	comd = cust_strcat(comd, dir);
	comd = cust_strcat(comd, "/");
	comd = cust_strcat(comd, parse);
	return (comd);
}

/**
 * cust_getenv - A function that retrieves the value of an
 * environment variable by its name
 * @nom: Name of the environment variable
 * Return: result
 */
char *cust_getenv(char *nom)
{
	int idx = 0;
	size_t a, b, lgthnom, lgthval;
	char *result;

	lgthnom = cust_strlen(nom);
	while (environ[idx] != NULL)
	{
		if (cust_strncmp(nom, environ[idx], lgthnom) == 0)
		{
			lgthval = cust_strlen(environ[idx]) - lgthnom;
			result = malloc(sizeof(char) * lgthval);
			if (!result)
			{
				free(result);
				perror("No allocation possible!");
				return (NULL);
			}
			a = lgthnom + 1;
			b = 0;
			while (environ[idx][a] != '\0')
			{
				result[b] = environ[idx][a];
				a++;
				b++;
			}
			result[lgthval] = '\0';
			break;
		}
		idx++;
	}
	return (result);
}

/**
 * dis_echo - A function that excute echo
 * @comd: Input command
 * Return: 0 on success, otherwise -1
 */
int dis_echo(char **comd)
{
	int result;
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve("/bin/echo", comd, environ) == -1)
			return (-1);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		return (-1);
	while (!WIFEXITED(result) && !WIFSIGNALED(result))
		waitpid(pid, &result, WUNTRACED);
	return (1);
}

/**
 * file_exit - A function that exits a file
 * @cmdline: A line in the file
 * @comd: Input command
 * @fdes: File descriptor
 */
void file_exit(char **comd, char *cmdline, FILE *fdes)
{
	int status, idx;

	if (comd[1] == NULL)
	{
		free(cmdline);
		free(comd);
		fclose(fdes);
		exit(errno);
	}
	for (idx = 0; comd[1][idx] != '\0'; idx++)
	{
		if (cust_isalpha(comd[1][idx]) < 0)
			perror("Wrong number");
	}
	status = cust_atoi(comd[1]);
	free(cmdline);
	free(comd);
	fclose(fdes);
	exit(status);
}

