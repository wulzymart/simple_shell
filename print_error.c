#include "main.h"

/**
 * _putchar_e - writes the character c to stdout
 * @c: the character to print
 *
 * Return: on success 1
 * on error, -1 is returned, and error is set appropriately
 */
int _putchar_e(char c)
{
	return (write(2, &c, 1));
}

/**
 * _puts_e - prints string followed by new line
 * @str: string to print
 * Return: return number of characters printed
 */
int _puts_e(const char *str)
{
	int i = 0, c = 0;

	while (*(str + i))
	{
		c += _putchar_e(*(str + i));
		i++;
	}
	c += _putchar_e('\n');
	return (c);
}

/**
 * _put_e - prints string but not followed by new line
 * @str: string to print
 * Return: return number of characters printed
 */
int _put_e(const char *str)
{
	int i = 0, c = 0;

	while (*(str + i))
	{
		c += _putchar_e(*(str + i));
		i++;
	}
	return (c);
}

/**
 * print_digits_e - print any given number8
 * Description: print any number
 * @n: number to print
 * Return: void
 */

void print_digits_e(unsigned int n)
{
	if (n < 10)
		_putchar_e(n + '0');
	else
	{
		if ((n / 10) < 10)
		{
			_putchar_e(n / 10 + '0');
			_putchar_e(n % 10 + '0');
		}
		else
		{
			print_digits_e(n / 10);
			_putchar_e(n % 10 + '0');
		}
	}
}
