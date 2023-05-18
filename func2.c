#include "main.h"
/**
 * _strcspn - determine the length of the prefix substring
 * @str1: first string
 * @str2: second string
 * Return: count
 */
size_t _strcspn(const char *str1, const char *str2)
{
	const char *p1, *p2;
	size_t count = 0;

	for (p1 = str1; *p1 != '\0'; p1++)
	{
		for (p2 = str2; *p2 != '\0'; p2++)
		{
			if (*p1 == *p2)
				return (count);
		}
		count++;
	}

	return (count);
}
/**
 * _strncmp - compares two strings
 * @str1: pointer to the first string to be compared.
 * @str2: pointer to the second string to be compared.
 * @n: maximum number of characters to compare
 * Return: Always 0.
 */
int _strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}

		if (str1[i] == '\0')
		{
			return (0);
		}
	}
	return (0);
}
/**
 * _atoi - converts a string to integer
 * @str: string to convert
 * Return: result
 */
int _atoi(char *str)
{
        int result = 0;
        int sign = 1;
        int i = 0;
        /*Handle negative numbers*/
        if (str[0] == '-')
        {
                sign = -1;
                i++;
        }
        /*Iterate through string and convert to integer*/
        for (; str[i] != '\0'; i++)
        {
                if (str[i] < '0' || str[i] > '9')
                {
                        break;
                }
                result = result * 10 + (str[i] - '0');
        }

        return (sign * result);
}
