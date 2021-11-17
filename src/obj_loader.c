#include "main.h"
#include "libobj.h"

bool parse_obj_arg(t_app *app, int argc, char *argv[])
{
	size_t len;

	if (argc < 2)
	{
		fprintf(
			stdout,
			"Error: %s received too few parameters\n",
			PROGRAM_NAME
		);
		return (false);
	}
	else if (argc > 3)
	{
		fprintf(
			stdout,
			"Error: %s received too many parameters\n",
			PROGRAM_NAME
		);
		return (false);
	}
	len = strlen(argv[1]);
	if (len < 5 || strncmp(".obj", &argv[1][len - 4], 4) != 0)
	{
		fprintf(
			stdout,
			"Error: %s must receive filename with .obj filename extension\n",
			PROGRAM_NAME
		);
		return (false);
	}
	app->obj_file_name = strdup(argv[1]);
	return (true);
}

bool load_obj(t_app *app, char const * const file_name)
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
