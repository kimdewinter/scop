#include "main.h"
#include <math.h>

void rotate_matrix(
	float matrix[16],
	const float rotation_degrees,
	t_axis rotation_axis)
{
	switch(rotation_axis)
	{
		case AXIS_X:
		{
			matrix[5] = cos((double)rotation_degrees);
			matrix[6] = sin((double)rotation_degrees);
			matrix[9] = -sin((double)rotation_degrees);
			matrix[10] = cos((double)rotation_degrees);
		}
		break;
		case AXIS_Y:
		{
			matrix[0] = cos((double)rotation_degrees);
			matrix[2] = -sin((double)rotation_degrees);
			matrix[8] = sin((double)rotation_degrees);
			matrix[10] = cos((double)rotation_degrees);
		}
		break;
		case AXIS_Z:
		{
			matrix[0] = cos((double)rotation_degrees);
			matrix[1] = sin((double)rotation_degrees);
			matrix[4] = -sin((double)rotation_degrees);
			matrix[5] = cos((double)rotation_degrees);
		}
		break;
	}
}

void translate_matrix(float matrix[16], const float translation_vector[3])
{
	matrix[12] = translation_vector[0];
	matrix[13] = translation_vector[1];
	matrix[14] = translation_vector[2];
}

void scale_matrix(float matrix[16], const float scale_multipliers[3])
{
	matrix[0] = scale_multipliers[0];
	matrix[5] = scale_multipliers[1];
	matrix[10] = scale_multipliers[2];
}

void identity_matrix(float matrix[16])
{
	ft_memset(matrix, 0, sizeof(matrix));
	matrix[0] = 1.0f;
	matrix[5] = 1.0f;
	matrix[10] = 1.0f;
	matrix[15] = 1.0f;
}

void execute_transformation(t_app *app)
{
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "transform"),
		1,
		GL_FALSE,
		app->transformation_matrix);
}
