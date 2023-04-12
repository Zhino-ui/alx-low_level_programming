#include "main.h"

/*
 * get_endianness - checks size of endian
 * return: value
 */

int get_endianness(void)
{
	unsigned int j = 1;
	char *k = (char *) &j;

	return (*k);
}
