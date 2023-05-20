#include "main.h"

/**
 * alloc_exec - gets arguements and executes them, helper function
 * @f: integer pointer for iteration
 * @g: integer pointer for iteration
 * @h: integer pointer for iteration
 * @d: integer pointer for return of execution
 * @sv: vector of tokens
 * @head: head of environ list
 * @count: command count
 * Return: 0 on success -1 if failed
*/
int alloc_exec(int *f, int *g, int *h, int *d, char **sv,
var_list *head, size_t *count)
{
	int i, a = *f, b = *g, c = *h;
	char **av;

	av = malloc(sizeof(char *) * (1 + a - b));
	if (!av)
		return (-1);
	av[a - b] = NULL;
	c = b;
	for (i = b ; i <  a ; i++)
	av[i - c] = sv[b++];
	*d = execute(av, head, count);
	free(av);
	*f = a;
	*g = b;
	*h = c;
	return (0);
}
/**
 * an_exec - analyzes a vector for seperators and executes as needed
 * @sv: tokens vector
 * @head: head of environ list
 * @count: command count
 * Return: 0 success, -1 failure
*/
int an_exec(char **sv, var_list *head, size_t *count)
{
	int a, b, c, d, e, sep = 0, sep1;

	for (a = 0, b = 0 ; sv[a] ; a++)
	{
		sep1 = sep;
		if (issep(sv[a], &e))
		{
			sep++;
			if (alloc_exec(&a, &b, &c, &d, sv, head, count) == -1)
				return (-1);
			b = a + 1;
			if (e > 1)
			{
				if ((e == 2 && d == 0) || (e == 3 && d == 1))
					break;
			}
		}
	}
	if (!sep)
	{
		execute(sv, head, count);
	}
	if (sep && sep == sep1)
		if (e == 1 || (e == 2 && d == 1) || (e == 3 && d == 0))
			if (alloc_exec(&a, &b, &c, &d, sv, head, count) == -1)
				return (-1);
	return (0);
}
/**
 * pre_proc - processes input before execution
 * @line: inputed lie form getline
 * @delim: delimiters for splitting
 * @head: head of environ list
 * @count: command count
 * Return: arguement vectors
*/
char **pre_proc(char *line, const char *delim, var_list *head, size_t *count)
{
	int i, d, l1, l2, m;
	char *line2 = NULL, **av, **av2;
	size_t n2;

	av = strsplt(line, delim);
	if (av)
		if (check_args(av, head, *count))
		{
			d = issep(av[v_count(av) - 1], &m);
			while (d && m > 1)
			{
				l1 = v_count(av);
				_put("> ");
				*count = *count + 1;
				if (_getline(&line2, &n2, stdin) == -1)
				{
					print_err(_getenv(&head, "_"), *count,
					"Syntax error: end of file unexpected");
					return (NULL);
				}
				av2 = strsplt(line2, delim);
				l2 = v_count(av2);
				av = _realloc(av, sizeof(char *) * (l1 + 1),
				(l1 + l2 + 1) * sizeof(char *));
				for (i = 0 ; av2[i]; i++)
					av[l1++] = av2[i];
				av[l1] = NULL;
				free(av2);
				free(line2);
				line2 = NULL;
				av2 = NULL;
				if (check_args(av, head, *count))
					d = issep(av[v_count(av) - 1], &m);
				else
					return (NULL);
			}
			return (av);
		}
	return (NULL);
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
	char *line = NULL, *delim = " \n", p = 0; /*p from pipe*/
	size_t n = 0, cmd_cnt = 1;

	(void)ac;
	env_list = build_env_list(&env_list, environ);
	while (1 && !p)
	{
		_put("$ ");
		if (_getline(&line, &n, stdin) == -1)
			break;
		p = !isatty(STDIN_FILENO);
		av = pre_proc(line, delim, env_list, &cmd_cnt);
		if (!av)
			continue;
		/*print(av);*/
		an_exec(av, env_list, &cmd_cnt);
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
