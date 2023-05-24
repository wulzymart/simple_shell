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
 * get_file - gets file descriptor
 * @av: arguement vector
 * @ac: arguement count
 * Return: file descriptor or -1 if error
*/
int get_file(int ac, char **av)
{
	int fd;

	if (ac > 2)
	{
		perror("Usage: simple_shell [filename]");
		exit(98);
	}
	if (ac == 1)
		fd = STDIN_FILENO;
	else
		fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		_put_e(av[0]);
		_put_e(": 0: cannot open ");
		_put_e(av[1]);
		_puts_e(": No such file");
		exit(98);

	}
	return (fd);
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
	int fd = get_file(ac, av);

	/*signal(SIGINT, sigint_handler);*/
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
