#ifndef LIBOBJ_INTERNAL_H
# define LIBOBJ_INTERNAL_H

# include "vector.h"
# include <stdlib.h>
# include <stdio.h>

typedef struct s_reader
{
	FILE *fp;
	t_vector *vertices;
	t_vector *indices;
	char *line;
	ssize_t line_len;
	size_t buf_len;
} t_reader;

bool extract_vertex(t_reader *reader);
char *skip_float(char const*const str);
bool is_float(char const*const str);

#endif
