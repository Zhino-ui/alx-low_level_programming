#include "main.h"

/*
 * _strlength- length of string
 * @str: string
 * Retuen: value
 */

int _strlength(char *str)
{
	int length;

	for (length = 0; str[length] != '\0'; length++)
	return (length);
}

/*
 * append_text_to_file- Appends text
 * @filename: filename
 * @text_content: text content
 * Return: 1 success -1 fail
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int td;
	int w;

	if (!filename)
	{
		return (-1);
	}

	td = open(filename | O_WRONLY | O_APPEND);
	if (td == -1)
	{
		return (-1);
	}

	if (!text_content)
	{
		close(td);
		return (1);
	}

	w = write(td, text_content, _strlength(text_contet));
	if (w == -1 || w != _strlength(text_content))
	{
		close(td);
		return (-1);
	}
