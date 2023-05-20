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
	char *line = NULL, *delim = " \n", p = 0; /*p from pipe*/
	size_t n = 0, cmd_cnt = 1, exstat = 0;

	(void)ac;
	env_list = build_env_list(&env_list, environ);
	while (1 && !p)
	{
		_put("$ ");
		if (_getline(&line, &n, stdin) == -1)
			break;
		p = !isatty(STDIN_FILENO);
		av = pre_proc(line, delim, env_list, &cmd_cnt, &exstat);
		if (!av)
			continue;
		an_exec(av, env_list, &cmd_cnt, &exstat);
		v_free(av);
		free(line);
		line = NULL;
	}
	if (!p)
		_putchar('\n');
	if (env_list)
		free_envlist(env_list);
	return (0);
}
