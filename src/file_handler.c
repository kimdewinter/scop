#include <stdio.h>
#include <stdlib.h>

//returns NULL if error
char *file_to_string(const char *file_name)
{
	FILE *file_pointer;
	long file_length;
	char *file_contents;

	file_pointer = fopen(file_name, "r");
	if (!file_pointer)
	{
		printf("Error calling fopen() on file \"%s\"\n", file_name);
		return NULL;
	}

	if (fseek(file_pointer, 0, SEEK_END) != 0)
	{
		printf("Error calling fseek() on file \"%s\"\n", file_name);
		return NULL;
	}

	file_length = ftell(file_pointer);
	if (file_length == -1L)
	{
		printf("Error calling ftell() on file \"%s\"\n", file_name);
		return NULL;
	}

	if (fseek(file_pointer, 0, SEEK_SET) != 0)
	{
		printf("Error calling fseek() on file \"%s\"\n", file_name);
		return NULL;
	}

	file_contents = malloc((file_length + 1) * sizeof(char));
	if (!file_contents)
	{
		printf("Misallocation error in function file_to_string\n");
		return NULL;
	}

	if (fread(
		file_contents,
		sizeof(char),
		file_length,
		file_pointer) != (size_t)file_length)
	{
		printf("Error calling fread on file \"%s\"\n", file_name);
		if (file_contents)
			free(file_contents);
		return NULL;
	}

	if (fclose(file_pointer) != 0)
	{
		printf("Error calling fclose on file \"%s\"\n", file_name);
		if (file_contents)
			free(file_contents);
		return NULL;
	}

	file_contents[file_length] = '\0';
	return file_contents;
}
