#include "main.h"

bool load_vertices(t_app *app)
{
	app->vertices_length = 18;
	app->vertices = (float *)malloc(app->vertices_length * sizeof(float));
	if (!app->vertices)
	{
		printf("Misallocation error in function load_vertices\n");
		return false;
	}
	app->vertices[0] = 0.5f;
	app->vertices[1] = -0.5f;
	app->vertices[2] = 0.0f;
	app->vertices[3] = 1.0f;
	app->vertices[4] = 0.0f;
	app->vertices[5] = 0.0f;
	app->vertices[6] = -0.5f;
	app->vertices[7] = -0.5f;
	app->vertices[8] = 0.0f;
	app->vertices[9] = 0.0f;
	app->vertices[10] = 1.0f;
	app->vertices[11] = 0.0f;
	app->vertices[12] = 0.0f;
	app->vertices[13] = 0.5f;
	app->vertices[14] = 0.0f;
	app->vertices[15] = 0.0f;
	app->vertices[16] = 0.0f;
	app->vertices[17] = 1.0f;
	return true;
}
