#include "main.h"

bool load_vertices(t_app *app)
{
	app->vertices_length = 32;
	app->vertices = (float *)malloc(app->vertices_length * sizeof(float));
	if (!app->vertices)
	{
		printf("Misallocation error in function load_vertices\n");
		return false;
	}
	app->vertices[0] = 0.5f;
	app->vertices[1] = 0.5f;
	app->vertices[2] = 0.0f;
	app->vertices[3] = 1.0f;
	app->vertices[4] = 0.0f;
	app->vertices[5] = 0.0f;
	app->vertices[6] = 1.0f;
	app->vertices[7] = 1.0f;
	app->vertices[8] = 0.5f;
	app->vertices[9] = -0.5f;
	app->vertices[10] = 0.0f;
	app->vertices[11] = 0.0f;
	app->vertices[12] = 1.0f;
	app->vertices[13] = 0.0f;
	app->vertices[14] = 1.0f;
	app->vertices[15] = 0.0f;
	app->vertices[16] = -0.5f;
	app->vertices[17] = -0.5f;
	app->vertices[18] = 0.0f;
	app->vertices[19] = 0.0f;
	app->vertices[20] = 0.0f;
	app->vertices[21] = 1.0f;
	app->vertices[22] = 0.0f;
	app->vertices[23] = 0.0f;
	app->vertices[24] = -0.5f;
	app->vertices[25] = 0.5f;
	app->vertices[26] = 0.0f;
	app->vertices[27] = 1.0f;
	app->vertices[28] = 1.0f;
	app->vertices[29] = 0.0f;
	app->vertices[30] = 0.0f;
	app->vertices[31] = 1.0f;
	return true;
}
