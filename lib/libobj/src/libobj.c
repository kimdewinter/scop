#include "libobj.h"
#include "libobj_internal.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

static t_obj *construct_obj(t_reader const*const reader)
{
	t_obj *obj = (t_obj *)calloc(1, sizeof(t_obj));

	if (!obj)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		return NULL;
	}

	if (!reader->vertices || reader->vertices->used < 1)
	{
		fprintf(stdout, "Error: no vertices in reader in construct_obj\n");
		free(obj);
		obj = NULL;
		return NULL;
	}

	//copy vertices from reader's t_vector to obj's float array
	obj->vertices_len = reader->vertices->used / sizeof(float);
	obj->vertices = (float *)malloc(obj->vertices_len * sizeof(float));
	if (!obj->vertices)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		free(obj);
		obj = NULL;
		return NULL;
	}
	memcpy(obj->vertices, reader->vertices->vec, obj->vertices_len * sizeof(float));

	if (!reader->indices || reader->indices->used < 1)
		return obj;

	//copy indices from reader's t_vector to obj's unsigned char array
	obj->indices_len = reader->indices->used / sizeof(unsigned int);
	obj->indices =
		(unsigned int *)malloc(obj->indices_len * sizeof(unsigned int));
	if (!obj->indices)
	{
		fprintf(stdout, "Error: misallocation in construct_obj\n");
		free(obj->vertices);
		obj->vertices = NULL;
		free(obj);
		obj = NULL;
		return NULL;
	}
	memcpy(
		obj->indices,
		reader->indices->vec,
		obj->indices_len * sizeof(unsigned int));
	return obj;
}

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
		fprintf(stdout, "Warning: obj_delete received null-pointer argument\n");
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
	{
		printf("derp\n");
		obj_delete(obj);
	}
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
	unsigned int *test = NULL;

	if (!construct_reader(&reader, file_name))
	{
		cleanup(&reader, &obj);
		return (NULL);
	}

	//start reading
	reader.line_len = getline(&reader.line, &reader.buf_len, reader.fp);
	while (reader.line_len > 0)
	{
		if (reader.indices)
		{
			test = (unsigned int *)reader.indices->vec;
			printf("START PRINTING\n\n");
			for (int i = 0; i < (int)reader.indices->used / (int)sizeof(unsigned int); i++)
			{
				if (i % 3 == 0 && i > 0)
					printf("\n");
				printf("%d ", test[i]);
			}
		}
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
	obj = construct_obj(&reader);
	cleanup(&reader, NULL);
	return (obj);
}
