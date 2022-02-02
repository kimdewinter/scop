#ifndef LIBOBJ_H
#define LIBOBJ_H

#include <stdbool.h>

typedef struct s_obj
{
	float *vertices;
	unsigned int vertices_len;
	unsigned int *indices;
	unsigned int indices_len;
} t_obj;

// Setting "use_element_array" to false will cause this library to
// reject faces made through vector-indexing(for an EBO),
// and creates extra vertices instead
t_obj *obj_import(char const *const file_name, bool const use_element_array);
void obj_delete(t_obj **obj_ptr);

#endif
