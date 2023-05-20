#include "main.h"

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _puts - prints string followed by new line
 * @str: string to print
 * Return: return number of charcters printed
 */

int _puts(const char *str)
{
	int i = 0, c = 0;

	while (*(str + i))
	{
		c += _putchar(*(str + i));
		i++;
	}
	c += _putchar('\n');
	return (c);
}
/**
 * _put - prints string but not followed by new line
 * @str: string to print
 * Return: return number of charcters printed
 */

int _put(const char *str)
{
	int i = 0, c = 0;

	while (*(str + i))
	{
		c += _putchar(*(str + i));
		i++;
	}
	return (c);
}
/**
 * print_digits - print any given number8
 * Description: print  any number
 * @n: number to print
 * Return: void
 */

void print_digits(unsigned int n)
{
	if (n < 10)
		_putchar(n + '0');
	else
	{
		if ((n / 10) < 10)
		{
			_putchar(n / 10 + '0');
			_putchar(n % 10 + '0');
		}
		else
		{
			print_digits(n / 10);
			_putchar(n % 10 + '0');
		}
	}
}
/**
 * print - prints a evector
 * @av: vector
*/
void print(char **av)
{
	int i;

	for (i = 0 ; av[i] ; i++)
	{
		_puts(av[i]);
	}
}
