#include "libobj.h"
#include "libobj_internal.h"
#include <stdio.h>
#include <stdbool.h>

bool construct_reader(t_reader *reader, char const*const file_name)
{
	reader->fp = fopen(file_name, "r");
	reader->obj = (t_obj *)calloc(1, sizeof(t_obj));
	reader->vertices = NULL;
	reader->indices = NULL;
	reader->line = NULL;
	reader->line_len = 0;
	reader->buf_len = 0;

	if (!reader->fp || reader->!obj)
	{
		cleanup(&fp, &obj, &vertices, &indices);
		return NULL;
	}

	return true;
}

void obj_delete(t_obj **obj_ptr)
{
	if (obj_ptr && *obj_ptr)
	{
		if ((*obj_ptr)->vertices)
		{
			free((*obj_ptr)->vertices);
			(*obj_ptr)->vertices = NULL;
			(*obj_ptr)->vertices_len = 0;
		}
		if ((*obj_ptr)->indices)
		{
			free((*obj_ptr)->indices);
			(*obj_ptr)->indices = NULL;
			(*obj_ptr)->indices_len = 0;
		}
		free(*obj_ptr);
		*obj_ptr = NULL;
	}
	else
		fprintf(stderr, "Warning: delete_obj received null-pointer argument\n");
}

static void cleanup(t_reader *reader)
{
	if (reader)
	{
		if (reader->fp)
		{
			fclose(reader->fp);
			reader->fp = NULL;
		}
		if (reader->obj)
			obj_delete(&reader->obj);
		if (reader->vertices)
			vector_delete(&reader->vertices);
		if (reader->indices)
			vector_delete(&reader->indices);
	}
}

//in case of error, returns NULL
t_obj *obj_import(char const*const file_name)
{
	t_reader reader;
	t_obj *obj;

	if (!reader.fp)
	{
		cleanup(&reader);
		return NULL;
	}

	//start reading
	line_len = getline(&line, &buf_len, fp);
	while (line_len > 0)
	{
		if (strcmp("v ", line) == 0)
		{
			if (!extract_vertex(line))
				return false;
		}
		else if (strcmp("f ", line) == 0)
		{
			if (!extract_faces(line))
				return false;
		}
		line_len = getline(&line, &buf_len, fp);
	}





	cleanup(&reader);
	return obj;
}
