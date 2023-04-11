#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * __exit - exit
 * @error: error
 * @s: string
 * #fd : filename
 * Return: value
 */

int __exit(int error, char *s, int fd)
{
	switch (error)
	{
		case 97:
			dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
			exit(error);
		case 98:
			dprintf(STDERR_FILENO, "Error: cannot read from %s\n", s);
			exit(error);
		case 99:
			dprintf(STDERR_FILENO, "Error: cannot write to %s\n", s);
			exit(error);
		case 100:
			dprintf(STDERR_FILENO, "Error: cannot close fd %d\n", fd);
			exit(error);
		default:
			return (0);
	}
}

/*
 * main - copy contents of a file to another
 * @argc: arguments
 * @argv: array pointer
 * Return: 0on success
 */
int main(int argc, char *argv[])
{
	int fd_1, fd_2, k_read, k_write;
	char *buf[1024];

	if (argc != 3)
		__exit(97, NULL, 0);

	fd_2 = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd_2 == -1)
	{
		__exit(99, argv[2], 0);
	}
	fd_1 = open(argv[1], O_RDONLY);
	if (fd_1 == -1)
	{
		__exit(98, argv[1], 0);
	}

	while ((k_read = read(fd_1, buf, 1024)) != 0)
	{
		if (k_read == -1)
		{
			__exit(98, argv[1], 0);
		}
		k_write = write(fd_2, buf, k_read);
		if (k_write == -1)
		{
			__exit(99, argv[2], 0);
		}
	}
	close(fd_2) == -1 ? (__exit(100, NULL, fd_2)) : close(fd_2);
	close(fd_1) == -1 ? (__exit(100, NULL, fd_1)) : close(fd_1);
	return (0);
}
