#include "libobj.h"
#include "libobj_internal.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

static t_obj *construct_obj(t_reader const *const reader)
{
	t_obj *obj;

	//check that there is actual data to package into the t_obj
	if (!reader->vertices || reader->vertices->used < 1)
	{
		fprintf(stdout, "Error: no vertices in reader in construct_obj\n");
		return NULL;
	}

	obj = (t_obj *)calloc(1, sizeof(t_obj));
	//check for misallocation
	if (!obj)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		return NULL;
	}

	//copy vertices from reader's t_vector to obj's float array
	obj->vertices_len = reader->vertices->used / sizeof(float);
	obj->vertices = (float *)malloc(obj->vertices_len * sizeof(float));
	if (!obj->vertices)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		obj_delete(&obj);
		return NULL;
	}
	memcpy(
		obj->vertices,
		reader->vertices->vec,
		reader->vertices->used);

	//check if there are indices to copy as well; if not, we're done and return
	if (!reader->indices || reader->indices->used < 1)
		return obj;

	//copy indices from reader's t_vector to obj's unsigned char array
	obj->indices_len = reader->indices->used / sizeof(unsigned int);
	obj->indices =
		(unsigned int *)malloc(obj->indices_len * sizeof(unsigned int));
	if (!obj->indices)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		obj_delete(&obj);
		return NULL;
	}
	memcpy(
		obj->indices,
		reader->indices->vec,
		reader->indices->used);
	return obj;
}

void obj_delete(t_obj **obj_ptr)
{
	if ((*obj_ptr)->vertices)
		free((*obj_ptr)->vertices);
	if ((*obj_ptr)->indices)
		free((*obj_ptr)->indices);
	memset(*obj_ptr, 0, sizeof(t_obj));
	free(*obj_ptr);
	*obj_ptr = NULL;
}

//arguments are allowed to be NULL
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
	if (obj && *obj)
		obj_delete(obj);
}

//in case of error, returns false
static bool construct_reader(t_reader *reader, char const *const file_name)
{
	memset(reader, 0, sizeof(t_reader));
	reader->fp = fopen(file_name, "r");
	reader->vertices = vector_init(3 * sizeof(float));
	reader->indices = vector_init(3 * sizeof(unsigned int));
	if (!reader->fp || !reader->vertices || !reader->indices)
		return (false);
	return (true);
}

//in case of error, returns NULL
t_obj *obj_import(char const *const file_name, bool const use_element_array)
{
	t_reader reader;
	t_obj *obj = NULL;

	//set up t_reader (zero variables, open file)
	if (!construct_reader(&reader, file_name))
	{
		cleanup(&reader, &obj);
		return (NULL);
	}

	//start reading
	reader.line_len = getline(&reader.line, &reader.buf_len, reader.fp);
	while (reader.line_len > 0)
	{
		if (strncmp("v ", reader.line, 2) == 0)
		{
			if (!extract_vertex(&reader))
			{
				cleanup(&reader, &obj);
				return (NULL);
			}
		}
		else if (strncmp("f ", reader.line, 2) == 0)
		{
			if (!extract_face(&reader))
			{
				cleanup(&reader, &obj);
				return (NULL);
			}
		}
		reader.line_len = getline(&reader.line, &reader.buf_len, reader.fp);
	}

	//if necessary, convert multiple-used indices into extra vertices
	if (reader.vertices->used &&
		reader.indices->used &&
		!use_element_array)
	{
		if (!convert_element_array_to_extra_vertices(&reader))
		{
			cleanup(&reader, &obj);
			return (NULL);
		}
	}

	//move data from t_reader into t_obj and return the latter
	obj = (reader.vertices->used) ? construct_obj(&reader) : NULL;
	cleanup(&reader, NULL);
	return (obj);
}
