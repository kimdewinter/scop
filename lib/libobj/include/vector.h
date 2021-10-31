#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct s_vector
{
	void *vec;
	size_t cap;
	size_t used;
} t_vector;

t_vector *vector_init(const size_t initial_bytes);
bool vector_append(t_vector *vec, void const*const ptr, size_t size);
void vector_delete(t_vector **vec);

#endif
