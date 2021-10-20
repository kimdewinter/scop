#include "matrix_handler.h"
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

void rotate(t_app *app)
{
	float mat4[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// float test_rotate_vec[3] = { 0.0f, 0.0f, 1.0f };
	float test_scale_vec[3] = { 0.5f, 0.5f, 0.5f };

	rotate_matrix(mat4, 90.0f, AXIS_Z);
	scale_matrix(mat4, test_scale_vec);
	unsigned int transform_location =
		glGetUniformLocation(app->shader_program, "transform");
	glUniformMatrix4fv(transform_location, 1, GL_FALSE, mat4);
}

void transform(t_app *app)
{
	float mat4[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	float test_translate_vec[3] = { 0.5f, -0.5f, 0.0f };
	// float test_rotate_vec[3] = { 0.0f, 0.0f, 1.0f };
	// float test_scale_vec[3] = { 0.5f, 0.5f, 0.5f };

	translate_matrix(mat4, test_translate_vec);
	rotate_matrix(mat4, SDL_GetTicks() / 1000, AXIS_Z);

	glUseProgram(app->shader_program);
	unsigned int transform_location = glGetUniformLocation(
		app->shader_program,
		"transform");
	glUniformMatrix4fv(transform_location, 1, GL_FALSE, mat4);
}
