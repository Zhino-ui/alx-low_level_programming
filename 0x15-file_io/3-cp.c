#include "main.h"
#include <stdio.h>
#include <stdlib.h>

char *create_buffer(char *file);
void close_file(int td);

/*
 * create_buffer- 1024 bytes
 * @filename- file
 * Return: 1 on success -1 on fail
 */

char *create_buffer(char *file)
{
	char *buf;

	buf = malloc(sizeof(char) * 1024);

	if (buf == NULL)
	{
		dprintf(STDERR_FILENO,
				"Error: cannot write to %s\n", file);
		exit(99);
	}
	return (buf);
}

/*
 * close_file - file closed
 * @td: file
 */

void close_file(int td)
{
	int c;

	c = close(td);

	if (c == -1)
	{
		dprintf(STDERR_FILENO, "Error: cannot close td %d\n", td);
		exit(100);
	}
}

/*
 * main - copy file contents to a different file
 * @argc: arguments numbers
 * @argv: array
 * Return: 0success
 * description: exit(97) - incorrect
 * file_from - exit(98) cannot be read
 * file_to - exit code(99) cannot be created
 * exit(100) - cannot be closed
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
			dprintf(STDERR_FILENO,
					"Error: cannot read file %s\n", argv[1]);
			free(buf);
			exit(98);
		}

		w = write(to, buf, r);
		if (to == -1 || w == -1)
		{
			dprintf(STDERR_FILENO,
					"error: cannot write to %s\n", argv[2]);
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
