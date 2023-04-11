#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int fd);

/*
 * create_buffer - 1024 allocation
 * @file: file
 * Return : value
 */

char *create_buffer(char *file)
{
	char *buf;

	buf = malloc(sizeof(char) * 1024);

	if (buf == NULL)
	{
		dprintf(STDERR_FILENO, "error: cannot write to %s\n", file);
		exit(99);
	}
	return (buf);
}

/*
 * close_file -closes file
 * @fd: descriptor
 */

void close_file(int fd)
{
	int x;

	x = close(fd);

	if (x == -1)
	{
		dprintf(STDERR_FILENO, "error: cannot close fd %d\n", td);
		exit(100);
	}
}

/*
 * main - copy file contents to another file
 * @argc: number of arguments
 * @argv: array
 * Return: 0 on success
 * Description: exit(97) if count is incorrect.
 * exit(98): if file_from cannot be read
 * exit(99): if file_to cannot be written
 * exit(100): cannot be closes
 */

int main(int argc, char *argv[])
{
	int from, to, r, w;
	char *buf;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	buf = create_buffer(argv[2]);
	from = open(argv[1], O_RDONLY);
	r = read(from, buf, 1024);
	to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0664);

	do {
		if (from == -1 || r == -1)
		{
			dprintf(STDERR_FILENO, "error: cannot read from %s\n", argv[1]);
			free(buf);
			exit(98);
		}
		w = write(to, buf, r);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO, "error: cannot write to %s\n", argv[2]);
			free(buf);
			exit(99);
		}

		r = read(from, buf, 1024);
		to = open(argv[2], O_WRONLY | O_APPEND);
	} while (r > 0);
	free(buf);
	close_file(from);
	close_file(to);
	return (0);
}
