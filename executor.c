#include "main.h"
/**
 * get_cmd_path - gets full path of arg string if found
 * @str: arguement string
 * @env_list: list link of environments
 * Return: full path to string, or NULL
*/
char *get_cmd_path(char *str, var_list *env_list)
{
	char *path, **paths, *cmd_pt;
	struct stat statbuf;
	int i;

	if (stat(str, &statbuf) == 0)
		return (str);
	path = _getenv(&env_list, "PATH");
	if (!path)
		return (NULL);
	paths = strsplt(path, ":");
	if (!paths)
	{
		free(path);
		return (NULL);
	}
	for (i = 0 ; paths[i] ; i++)
	{
		cmd_pt = malloc(sizeof(char) * (_strlen(paths[i]) + _strlen(str) + 2));
		if (!cmd_pt)
			return (NULL);
		cmd_pt = _strcpy(cmd_pt, paths[i]);
		cmd_pt = _strcat(cmd_pt, "/");
		cmd_pt = _strcat(cmd_pt, str);
		cmd_pt = _strcat(cmd_pt, "\0");
		if (stat(cmd_pt, &statbuf) == 0)
		{
			free(paths);
			free(path);
			return (cmd_pt);
		}
		free(cmd_pt);
	}
	free(paths);
	free(path);
	return (NULL);
}
/**
 * execute - executes any passed arguement count
 * @av: arguement vector
 * @env_list: environment list
 * @cmd_cnt: command count
 * Return: 0 if success, -1
*/
int execute(char **av, var_list *env_list, size_t *cmd_cnt)
{
	int (*f)(char **av, size_t cmd_count, var_list *head), i;
	char *path;
	int a, e = 0, status;

	f = inb_functs(av[0]);
	if (f != NULL)
	{
		i = f(av, *cmd_cnt, env_list);
		*cmd_cnt = *cmd_cnt + 1;
		if (i == 1)
			return (1);
		return (0);
	}
	path = get_cmd_path(av[0], env_list);
	if (!path)
	{
		print_err_nf(_getenv(&env_list, "_"), *cmd_cnt, av[0], "not found");
		*cmd_cnt = *cmd_cnt + 1;
		return (1);
	}
	a = fork();
	if (a == 0)
	{
		av[0] = _strdup(path);
		e = execve(av[0], av, var_list2vector(&env_list));
		print_err(_getenv(&env_list, "_"), *cmd_cnt,
		"Error executing command");
	}
	else
	{
			wait(&status);
			free(path);
			*cmd_cnt = *cmd_cnt + 1;
	}
	if ((WIFEXITED(status) && WEXITSTATUS(status) != 0) || e != 0)
		return (1);

	return (0);
}