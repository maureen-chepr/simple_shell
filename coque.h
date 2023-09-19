#ifndef COQUE_H
#define COQUE_H

/* External variable */

extern char **environ;

/* Defining Macros */

#define BUFSIZE 1024
#define DELIM " \t\r\n\a"
#define prints(ch) (write(STDOUT_FILENO, ch, cust_strlen(ch)))
#define MAX_COMMAND_LENGTH 1000

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

/*	Custom builtins	*/
int cust_cd(char **comd, int prevstatus);
void  shell_exit(char **comd, char *input, char **cmdargs, int count);
int shell_help(char **comd, int prevstatus);
int print_env(char **comd, int prevstatus);
int shell_echo(char **comd, int status);

/*	Input functions	*/
char *cust_getline();
void _fhashtag(char *buffer);
int cmd_records(char *input);
void clear_env(char **var_env);
int shell_hist(char **cmd, int status);

/*	Memory functions*/
void *cust_realloc(void *p, unsigned int prevlgth, unsigned int newlgth);
void clear_mem(char **comd, char *cmdline);
char *cust_memcpy(char *dest, char *src, unsigned int n);
void *cust_calloc(unsigned int arr_size);
void *set_array(void *arr, int bval, unsigned int lgth);

/*	More strings	*/
int cust_strcmp(char *s1, char *s2);
int cust_isalpha(int ch);
char *cust_itoa(unsigned int integer, int base);
void reverse_array(char *array, int elt);
int size_int(int nb);

/*	More functions	*/
int find_route(char **comd);
char *cmd_build(char *parse, char *dir);
char *cust_getenv(char *nom);
void file_exit(char **comd, char *cmdline, FILE *fdes);
int dis_echo(char **comd);

/*	String functions	*/
char *cust_strcpy(char *dest, char *src);
char *cust_strcat(char *dest, char *src);
char *cust_strchr(char *str, char ch);
int cust_strncmp(const char *s1, const char *s2, size_t n);
char *cust_strdup(char *stg);

/*	Display functions	*/
void print_no(int n);
void print_int(int n);
void print_error(char **cmdargs, int result, char **comd);
char **_token(char *input);
void dis_error(char *input, int count, char **cmdargs);

/*	Runtime functions	*/
int _handle(char **comd, int prevstatus);
int exc_comd(char **comd, char *input, int count, char **cmdargs);
void sig_handle(int signal);
void _rfile(char *fname, char **cmdargs);
void process_comd(char *cmdline, int val, FILE *fptr, char **cmdargs);

/*	Set environment	*/
int shell_setenv(char **input, int prevstatus);
int shell_unsetenv(char **input, int prevstatus);
int cust_setenv(char *nom, char *val, int prev);
int cust_unsetenv(char *nom);
int cust_isdigit(int c);

/*	Supplementary functions	*/
int write_char(char ch);
char *cust_strncpy(char *dest, char *src, int n);
int cust_strlen(char *s);
int cust_atoi(char *s);
void cust_puts(char *stg);

/*	Tokenise functions	*/
unsigned int find_match(char ch, const char *stg);
int is_builtin(char **comd);
char *cust_strtok(char *stg, const char *sep);
void shell_env(char **array);
char *cust_memset(char *s, char b, unsigned int n);

/*	Shell main function	*/
int main(int arg, char **cmdargs);
void cmd_prompt(void);

/**
 * struct more_builtin - Structure defined for bulitin functions
 * @cmdname: Built in command
 * @funct: Pointer to the specific builtin function
 */
typedef struct more_builtin
{
	char *cmdname;
	int (*funct)(char **cmdline, int prevstatus);
} built_func;

#endif
