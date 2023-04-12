#include "main.h"

/*
 * flip_bits - counts numbers
 * @n: first number
 * @m: second number
 * Return: value
 */

unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	int t, counter = 0;
	unsigned long int new;
	unsigned long int core = n ^ m;

	for (t = 63; t >= 0; t--)
	{
		new = core >> t;
		if (new & 1)
		{
			counter++;
		}
	}
		return (counter);
}
