#include "vector.h"

//returns NULL in case of error
t_vector *vector_init(const size_t initial_bytes)
{
	t_vector *vec;

	vec = malloc(sizeof(t_vector));
	if (!vec)
	{
		write(0, "Error: misallocation in function vector_init\n", 45);
		return NULL;
	}
	vec->vec = (void *)malloc(initial_bytes);
	if (!(vec->vec))
	{
		write(0, "Error: misallocation in function vector_init\n", 45);
		return NULL;
	}
	memset(vec->vec, 0, initial_bytes);
	vec->cap = initial_bytes;
	vec->used = 0;
	return vec;
}

//returns false in case of error
static bool vector_resize(t_vector *vec, const size_t new_size)
{
	void *new_vec;

	if (!vec)
	{
		write(
			0,
			"Error: param vec is null in vector_resize\n",
			42);
		return false;
	}
	if (new_size < 1)
	{
		write(
			0,
			"Error: param new_size smaller than 1 in vector_resize\n",
			54);
		return false;
	}
	new_vec = realloc(vec->vec, new_size);
	if (!new_vec)
	{
		write(0, "Error: misreallocation in function vector_resize\n", 49);
		return false;
	}
	if (new_size > vec->cap)
	{
		memset(new_vec + vec->cap, 0, new_size - vec->cap);
	}
	vec->vec = new_vec;
	vec->cap = new_size;
	return true;
}

bool vector_append(t_vector *vec, void const*const ptr, const size_t size)
{
	while (vec->used + size > vec->cap)
	{
		vector_resize(vec, vec->cap * 2);
		vec->cap *= 2;
		memset(vec->vec + size, ptr, size);
	}
}

void vector_free(t_vector **vec)
{
	if (!vec || !(*vec))
	{
		write(
			0,
			"Error: param vec is null in vector_resize\n",
			42);
		return false;
	}
	if ((*vec)->vec)
	{
		free((*vec)->vec);
		(*vec)->vec = NULL;
	}
	(*vec)->cap = 0;
	(*vec)->used = 0;
	free(*vec);
	*vec = NULL;
}
