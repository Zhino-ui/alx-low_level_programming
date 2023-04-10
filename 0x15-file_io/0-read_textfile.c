#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - read the text file and send to stdout.
 * @filename: name of text file being read
 * @letters: letter numbers read
 * Return: w - number of bytes read and printed out
 * 0: when filename is null or when the function fails
 *
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	char *baf;
	ssize_t td;
	ssize_t w;
	ssize_t r;

	td = open(filename, O_RDONLY);
	if (td == -1)
	{
		return (0);
	}
	baf = malloc(sizeof(char) * letters);
	r = read(td, baf, letters);
	w = write(STDOUT_FILENO, baf, r);

	free(baf);
	close(td);
	return (w);
}
