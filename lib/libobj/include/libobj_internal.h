#ifndef LIBOBJ_INTERNAL_H
# define LIBOBJ_INTERNAL_H

# include "vector.h"
# include <stdlib.h>

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

#endif
