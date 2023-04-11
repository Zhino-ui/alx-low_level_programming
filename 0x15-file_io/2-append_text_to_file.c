#include "main.h"

/*
 * _strlen - find string length
 * @string: string
 * Return: value of string
 */

int _strlen(char *str)
{
	int len;

	for (len = 0; str[len] != '\0';)
	{
		len++;
	}
	return (len);
}

/*
 * append_text_to_file - appends text to file if exits
 * @filename: name of file
 * @text_content: contents of a file
 * Return: prints 1 on success and -1 on fail
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int td;
	int w;

	if (!filename)
		return (-1);

	td = open(filename, O_WRONLY | O_APPEND);
	if (td == -1)
	{
		return (-1);
	}
	if (!text_content)
	{
		close(td);
		return (1);
	}

	w = write(td, text_content, _strlen(text_content));
	if (w == -1 || w != _strlen(text_content))
	{
		close(td);
		return (-1);
	}
	close(td);
	return (1);
}
