#include "main.h"

static void combine_matrices(
	float final_matrix[16],
	const float matrix_a[16],
	const float matrix_b[16],
	const float matrix_c[16])
{
	//finish this function
}

static void translate_matrix(float matrix[16], const float translation_vector[3])
{
	matrix[12] += translation_vector[0];
	matrix[13] += translation_vector[1];
	matrix[14] += translation_vector[2];
}

static void rotate_matrix(
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

static void scale_matrix(float matrix[16], const float scale_multipliers[3])
{
	matrix[0] += scale_multipliers[0];
	matrix[5] += scale_multipliers[1];
	matrix[10] += scale_multipliers[2];
}

static void identity_matrix(float matrix[16])
{
	ft_memset(matrix, 0, 16 * sizeof(float));
	matrix[0] += 1.0f;
	matrix[5] += 1.0f;
	matrix[10] += 1.0f;
	matrix[15] += 1.0f;
}

void handle_transformations(t_app *app)
{
	float scaling_matrix[16];
	float rotation_matrix[16];
	float translation_matrix[16];
	float combined_matrixp[16];

	identity_matrix(&scaling_matrix);
	identity_matrix(&rotation_matrix);
	identity_matrix(&translation_matrix);
	scale_matrix(&scaling_matrix, (float[3]){ app->scaling_x, app->scaling_y, app->scaling_z });
	rotate_matrix(&rotation_matrix, (float[3]]){ app->rotation_x, app->rotation_y, app->rotation_z });
	translate_matrix(&translate_matrix, (float[3]){ app->translation_x, app->translation_y, app->translation_z });
	combine_matrices(&scaling_matrix, &rotation_matrix, &translation_matrix);*
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "transform"),
		1,
		GL_FALSE,
		combined_matrix);
}
