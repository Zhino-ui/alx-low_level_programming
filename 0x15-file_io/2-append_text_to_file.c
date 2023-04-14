#include "main.h"

/*
 * append_text_to_file - appends text to file
 * @filename: file
 * @text_content : text content
 * Return:-1 if fail or NULL else 1
 */

int append_text_to_file(const char *filename, char *text_content)
{
	int op, wi, len = 0;

	if (filename == NULL)
		return (-1);

	if (text_content != NULL)
	{
		for (len = 0; text_content[len];)
			len++;
	}

	op = open(filename, O_WRONLY | O_APPEND);
	wi = write(op, text_content, len);

	if (op == -1 || wi == -1)
		return (-1);

	close(op);

	return (1);
}
