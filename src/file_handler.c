#include <stdio.h>
#include <stdlib.h>

//Returns NULL if error
char *file_to_string(char const *const file_name)
{
	FILE *file_pointer;
	long file_length;
	char *file_contents;

	file_pointer = fopen(file_name, "r");
	if (!file_pointer)
	{
		fprintf(stdout, "Error calling fopen() on file \"%s\"\n", file_name);
		return (NULL);
	}

	if (fseek(file_pointer, 0, SEEK_END) != 0)
	{
		fprintf(stdout, "Error calling fseek() on file \"%s\"\n", file_name);
		return (NULL);
	}

	file_length = ftell(file_pointer);
	if (file_length == -1L)
	{
		fprintf(stdout, "Error calling ftell() on file \"%s\"\n", file_name);
		return (NULL);
	}

	if (fseek(file_pointer, 0, SEEK_SET) != 0)
	{
		fprintf(stdout, "Error calling fseek() on file \"%s\"\n", file_name);
		return (NULL);
	}

	file_contents = malloc((file_length + 1) * sizeof(char));
	if (!file_contents)
	{
		fprintf(stdout, "Misallocation error in function file_to_string\n");
		return (NULL);
	}

	if (fread(
			file_contents,
			sizeof(char),
			file_length,
			file_pointer) != (size_t)file_length)
	{
		fprintf(stdout, "Error calling fread on file \"%s\"\n", file_name);
		if (file_contents)
			free(file_contents);
		return (NULL);
	}

	if (fclose(file_pointer) != 0)
	{
		fprintf(stdout, "Error calling fclose on file \"%s\"\n", file_name);
		if (file_contents)
			free(file_contents);
		return (NULL);
	}

	file_contents[file_length] = '\0';
	return (file_contents);
}
