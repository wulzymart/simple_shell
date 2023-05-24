#include "main.h"
/**
 * _strlen - count length of string
 * @s: string to be counted address of string
 * Return: returns the length
 */
int _strlen(const char *s)
{
	int i = 0;

	while (*(s + i))
	{
		i++;
	}
	return (i);
}
/**
 * main - entry point
 * @ac: arguement count
 * @av: arguement vector
 * @env: environment
 * Return: 0
*/
int main(int ac, char **av, char **env)
{
	char *line = NULL, *sv[2];
	size_t n = 0;
	pid_t a;
	struct stat buff;

	(void)ac;
	while (1)
	{
		_put("$ ");
		if (getline(&line, &n, stdin) == -1)
			break;
		line[_strlen(line) - 1] = 0;
		if (stat(line, &buff) == -1)
		{
			_put(av[0]);
			_puts(": No such file or directory");
		}
		sv[0] = line;
		sv[1] = NULL;
		a = fork();
		if (a == 0)
			execve(line, sv, env);
		else
			wait(NULL);
		free(line);
		line = NULL;
	}
	_putchar('\n');
	return (0);
}
