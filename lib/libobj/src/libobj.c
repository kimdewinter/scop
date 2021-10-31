#include "libobj.h"
#include "libobj_internal.h"
#include <stdio.h>
#include <stdbool.h>

void obj_delete(t_obj **obj_ptr)
{
	if (obj_ptr && *obj_ptr)
	{
		if ((*obj_ptr)->vertices)
			free((*obj_ptr)->vertices);
		if ((*obj_ptr)->indices)
			free((*obj_ptr)->indices);
		memset(*obj_ptr, 0, sizeof(t_obj));
		free(*obj_ptr);
		*obj_ptr = NULL;
	}
	else
		fprintf(stderr, "Warning: delete_obj received null-pointer argument\n");
}

static void cleanup(t_reader *reader, t_obj **obj)
{
	if (reader)
	{
		if (reader->fp)
			fclose(reader->fp);
		if (reader->vertices)
			vector_delete(&reader->vertices);
		if (reader->indices)
			vector_delete(&reader->indices);
		if (reader->line)
			free(reader->line);
		memset(reader, 0, sizeof(t_reader));
	}
	if (obj)
		obj_delete(obj);
}

bool construct_reader(t_reader *reader, char const*const file_name)
{
	memset(reader, 0, sizeof(t_reader));
	reader->fp = fopen(file_name, "r");
	if (!reader->fp)
		return (false);
	return (true);
}

//in case of error, returns NULL
t_obj *obj_import(char const*const file_name)
{
	t_reader reader;
	t_obj *obj = NULL;

	if (!construct_reader(&reader, file_name))
	{
		cleanup(&reader, &obj);
		return (NULL);
	}

	//start reading
	reader.line_len = getline(&reader.line, &reader.buf_len, reader.fp);
	while (reader.line_len > 0)
	{
		if (strcmp("v ", reader.line) == 0)
		{
			if (!extract_vertex(&reader))
			{
				cleanup(&reader, &obj);
				return (NULL);
			}
		}
		else if (strcmp("f ", reader.line) == 0)
		{
			if (!extract_faces(&reader))
			{
				cleanup(&reader, &obj);
				return (NULL);
			}
		}
		reader.line_len = getline(&reader.line, &reader.buf_len, reader.fp);
	}



	cleanup(&reader, &obj);
	return (obj);
}
