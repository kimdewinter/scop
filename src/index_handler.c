#include "main.h"

bool load_indices(t_app *app)
{
	app->indices_length = 3;
	app->indices = (unsigned int *)malloc(
		app->indices_length * sizeof(unsigned int));
	if (!app->indices)
	{
		printf("Misallocation error in function load_indices\n");
		return false;
	}
	app->indices[0] = 0;
	app->indices[1] = 1;
	app->indices[2] = 2;
	return true;
}
