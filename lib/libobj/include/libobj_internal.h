#ifndef LIBOBJ_INTERNAL_H
# define LIBOBJ_INTERNAL_H

# include "libobj.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_vector
{
	void *vec;
	size_t cap;
	size_t used;
} t_vector;

typedef struct s_reader
{
	FILE *fp;
	t_vector *vertices;
	unsigned int vertex_attributes;
	t_vector *indices;
	char *line;
	ssize_t line_len;
	size_t buf_len;
} t_reader;

t_vector *vector_init(const size_t initial_bytes);
bool vector_append(t_vector *vec, void const*const ptr, size_t size);
void vector_delete(t_vector **vec);

#endif