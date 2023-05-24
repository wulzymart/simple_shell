#include "main.h"
/**
 * sigint_handler - handles ctrl + C signal
 * @n: unused int
*/
void sigint_handler(int n)
{
	(void)n;
	_put("\n$ ");
}
/**
 * main - simple shell project
 * @ac: arguement count
 * @av: arguement vector
 * Return: 0 if success
*/
int main(int ac, char **av)
{
	var_list *env_list = NULL;
	char **sv, *line = NULL, *delim = " \n", p = 0; /*p from pipe*/
	size_t n = 0, cmd_cnt = 1, exstat = 0;
	FILE *fd;

	signal(SIGINT, sigint_handler);
	(void)av;
	fd = stdin;
	env_list = build_env_list(&env_list, environ);
	while (1 && !p)
	{
		p = !isatty(STDIN_FILENO);
		if (ac == 1 && !p)
		_put("$ ");
		if (_getline(&line, &n, fd) == -1)
			break;
		sv = pre_proc(line, delim, env_list, &cmd_cnt, &exstat, fd);
		if (!sv)
			continue;
		an_exec(sv, env_list, &cmd_cnt, &exstat, line);
		v_free(sv);
		free(line);
		line = NULL;
	}
	if (!p)
		_putchar('\n');
	if (env_list)
		free_envlist(env_list);
	return (0);
}
