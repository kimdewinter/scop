#include "vector.h"
#include <string.h>
#include <stdio.h>

//returns NULL in case of error
t_vector *vector_init(const size_t initial_bytes)
{
	t_vector *vec;

	if (initial_bytes < 1)
	{
		fprintf(
			stdout,
			"Error: initial_bytes of less than 1 in function vector_init\n");
		return (NULL);
	}
	vec = (t_vector *)calloc(1, sizeof(t_vector));
	if (!vec)
	{
		fprintf(stdout, "Error: misallocation in function vector_init\n");
		return (NULL);
	}
	vec->vec = (void *)calloc(1, initial_bytes);
	if (!vec->vec)
	{
		fprintf(stdout, "Error: misallocation in function vector_init\n");
		return (NULL);
	}
	vec->cap = initial_bytes;
	return (vec);
}

//returns false in case of error
static bool vector_resize(t_vector *vec, const size_t new_size)
{
	void *new_vec;

	if (!vec || !new_size)
	{
		fprintf(stdout, "Error: param vec is null in vector_resize\n");
		return (false);
	}
	if (new_size < 1)
	{
		fprintf(
			stdout,
			"Error: param new_size smaller than 1 in vector_resize\n");
		return (false);
	}
	new_vec = realloc(vec->vec, new_size);
	if (!new_vec)
	{
		fprintf(stdout, "Error: misreallocation in function vector_resize\n");
		return (false);
	}
	if (new_size > vec->cap)
		memset(new_vec + vec->cap, 0, new_size - vec->cap);
	vec->vec = new_vec;
	vec->cap = new_size;
	return (true);
}

//call vector_init() once before any vector_append() calls
//returns false in case of error
bool vector_append(
	t_vector **vec,
	void const * const data,
	const size_t data_size)
{
	size_t new_size;

	if (!vec || !(*vec) || !data || !data_size)
	{
		printf("%p\n%p\n%p\n%zu\n", vec, *vec, data, data_size);
		fprintf(stdout, "Error: invalid param in vector_append\n");
		return (false);
	}
	new_size = (*vec)->cap;
	while (new_size < (*vec)->used + data_size)
		new_size *= 2;
	if (!vector_resize(*vec, new_size))
		return (false);
	memcpy((*vec)->vec + (*vec)->used, data, data_size);
	(*vec)->used += data_size;
	return (true);
}

void vector_delete(t_vector **vec)
{
	if ((*vec)->vec)
		free((*vec)->vec);
	memset(*vec, 0, sizeof(t_vector));
	free(*vec);
	*vec = NULL;
}
