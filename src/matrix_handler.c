#include "main.h"
#include <math.h>



void rotation_matrix()

void execute_transformation(t_app *app)
{
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "transform"),
		1,
		GL_FALSE,
		app->transformation_matrix);
}
