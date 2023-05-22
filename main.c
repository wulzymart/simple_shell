#include "main.h"

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

	env_list = build_env_list(&env_list, environ);
	while (1 && !p)
	{
		if (ac == 1)
		_put("$ ");
		if (getline(&line, &n, stdin) == -1)
			break;
		p = !isatty(STDIN_FILENO);
		sv = pre_proc(line, delim, env_list, &cmd_cnt, &exstat, fd);
		if (!sv)
			continue;
		an_exec(sv, env_list, &cmd_cnt, &exstat);
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
