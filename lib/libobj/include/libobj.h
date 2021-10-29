#ifndef LIBOBJ_H
# define LIBOBJ_H

typedef struct s_obj
{
	float *vertices;
	unsigned int vertex_attributes;//3 for xyz, 4 for xyzw
	unsigned int vertices_len;
	unsigned char *indices;
	unsigned int indices_len;
} t_obj;

t_obj *obj_import(char const*const file_name);//returns NULL if error
void obj_delete(t_obj **obj_ptr);

#endif
