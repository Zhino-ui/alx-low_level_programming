#include "main.h"

/**
 * create_file - file creation.
 * @filename: address of the filename.
 * @text_content: pointer to string to write the file
 * Return: -1 - if function fails
 *	else - 1.
 */

int create_file(const char *filename, char *text_content)
{
	int td, w, len = 0;

	if (filename == NULL)
	{
		return (-1);
	}
	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
		{
			len++;
		}
	}
	td = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0600);
	w = write(td, text_content, len);

	if (td == -1 || w == -1)
	{
		return (-1);
	}
	close(td);
	return (1);
}
