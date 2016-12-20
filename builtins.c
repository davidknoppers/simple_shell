#include "shell.h"
/**
  * is_builtin - checks if cmd is a builtin
  * @cmd: command to find
  * Return: On success - pointer to function, On Failure - NULL pointer
 (* other useful shell builtins:
 (* pwd, echo, pushd, popd, type
 (* * requires ^Z
 (* fg, bg
 (*  * Requires ^R
 (* reverse-i-search **HISTORY**
*/
int (*is_builtin(char *cmd))()
{
	unsigned int i;
	builtin_cmds_t builds[] = {
		{"exit", _exit_with_grace},
		{"env", _env},
		{"cd", _cd},
		{"alias", _alias},
		{"history", _history},
		{"help", _help},
		{"bowie", bowie},
		{NULL, NULL}
	};

	i = 0;
	while (*builds[i].fun != NULL)
	{
		if (_strncmp(builds[i].cmd_str, cmd, _strlen(builds[i].cmd_str)) == 0)
			return (builds[i].fun);
		i++;
	}
	return (NULL);
}
/**
  * _exit_with_grace - Frees any remaining malloc'd spaces, and exits
  * @linkedlist_path: Linked list to free.
  * @buffer: buffer to free
  * @tokens: Check for other inputs
 (* * CHANGE TO VARIADIC LIST.
  * Return: -1 if exit fails.
  */
int _exit_with_grace(char **tokens, env_t *linkedlist_path, char *buffer)
{
	int exit_status;

	exit_status = tokens[1] ? _atoi(tokens[1]) : 0;
	printf("exit status = %d\n", exit_status);
	free_list(linkedlist_path);
	linkedlist_path = NULL;
	printf("linked list freed\n");
	free(buffer);
	buffer = NULL;
	printf("*buffer freed\n");
	free(tokens);
	tokens = NULL;
	printf("**tokens freed\n");
	printf("All frees successful!\n");
	exit(exit_status);
	perror("Exit failed\n");
	return(-1);
}
/**
  * _env - prints out the current environment
  * Return: 0 on success, -1 on catastrophic failure
  */
int _env(void)
{
	char **envir;

	envir = environ;
	if (!envir || !environ)
		return (-1);
	for ( ; *envir; envir++)
	{
		write(STDOUT_FILENO, *envir, _strlen(*envir));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
/**
  * _cd - changes working directory
  * @str: argument list
  */
int _cd(char **tokens)
{
	int dir_exists;
	char *target;
	char *home;

	home = getenv("HOME");
	target = tokens[1] ? (_strncmp(tokens[1], "~", 1) ? tokens[1] : home ) : home;
	if (target == home)
		chdir(target);
	else if((dir_exists = access(target, F_OK)) == 0)
			chdir(target);
	else
		perror("Could not find directory\n");
	return (0);
}
/**
  * _alias - sets aliases or prints them out when no options are supplied
  * @str: argument list
  */
int _alias(char *str)
{
	printf("alias skeleton works: %s\n", str);
	return (0);
}
/**
  * _history - prints out history with no options,
  *  or does other operations on the history file
  * @str: argument list
  */
int _history(void)
{
	printf("history: manipulate or view the history of commands\n ");
	printf("'history', without any options, displays the list");
	printf("of previously used commands, and the number of those commands.\n");
	printf("'history -c' clears the history\n");
	printf("See the list of history entries in bash with 'help history'\n");
	return (0);
}
/**
  * _help - display help pages for builtin commands
  * @str: argument list
  */
int _help(void)
{
	printf("help with no arguments prints a list of builtins\n");
	printf("Options: -d, -s, -m, Arguments: PATTERN\n");
	printf("If no arguments match PATTERN, return 1\n");
	return (0);
}
int bowie(void)
{
	int txt_file, total, read_status;
	size_t letters = 7483;
	char *filename = "bowie.txt";
	char buffer[BUFSIZE];

	if (filename == NULL)
		return (0);
	txt_file = open(filename, O_RDONLY);
	if (txt_file == -1)
		return (0);
	total = 0;
	read_status = 1;
	while (letters > BUFSIZE && read_status != 0)
	{
		read_status = read(txt_file, buffer, BUFSIZE);
		write(STDOUT_FILENO, buffer, read_status);
		total += read_status;
		letters -= BUFSIZE;
	}
	read_status = read(txt_file, buffer, letters);
	write(STDOUT_FILENO, buffer, read_status);
	total += read_status;
	close(txt_file);
	return (total);
}
