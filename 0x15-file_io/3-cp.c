#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * __exit- exits program
 * @error: file descriptor
 * @s: string
 * @td: filename
 * Return: 0 on success
 */

int __exit(int error, char *s, int td)
{
	switch (error)
	{
		case 97:
			dprintf(STDERR_FILENO, "usage: copy file_from file_to\n");
			exit(error);
		case 98:
			dprintf(STDERR_FILENO, "Error: cannot read file %s\n", s);
			exit(error);
		case 99:
			dprintf(STDERR_FILENO, "Error: cannot write %s\n", s);
			exit(error);
		case 100:
			dprintf(STDERR_FILENO, "Error: cannot close td%d\n", td);
			exit(error);
		default:
			return (0);
	}
}

/*
 * main - copy files
 * @argc: should be 3
 * @argv: address of file to copy
 * Return: 0 success
 */

int main(int argc, char *argv[])
{
	int td_1, td_2, n_read, n_write;
	char *buffer[1024];

	if (argc != 3)
		__exit(97, NULL, 0);

	td_2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (td_2 == -1)
		__exit(99, argv[2], 0);

	td_1 = open(argv[1], O_RDONLY);
	if (td_1 == -1)
		__exit(98, argv[1], 0);

	while ((n_read = read(td_1, buffer, 1024)) != 0)
	{
		if (n_read == -1)
			__exit(98, argv[1], 0);

		n_write = write(td_2, buffer, n_read);
		if (n_write == -1)
		{
			__exit(99, argv[2], 0);
		}
	}
		close(td_2) == -1 ? (__exit(100, NULL, td_2)) : close(td_2);
		close(td_1) == -1 ? (__exit(100, NULL, td_1)) : close(td_1);
		return (0);
	}
