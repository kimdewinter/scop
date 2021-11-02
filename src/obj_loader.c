#include "main.h"
#include "libobj.h"

bool load_obj(t_app *app, char const*const file_name)
{
	t_obj *obj = obj_import(file_name);

	if (!obj)
		return (false);
	app->vertices_length = obj->vertices_len;
	app->vertices = obj->vertices;
	app->indices_length = obj->indices_len;
	app->indices = obj->indices;
	free(obj);
	obj = NULL;
	return (true);
}
