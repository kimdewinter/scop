#include "main.h"

void multiply_square_matrices(
	const unsigned int size,
	float *dst,
	const float *src1,
	const float *src2)
{
	memset(dst, 0, 16 * sizeof(float));
	for(unsigned int y = 0; y < size; y++)
	{
		for(unsigned int x = 0; x < size; x++)
		{
			for(unsigned int i = 0; i < size; i++)
			{
				dst[y * size + x] += src1[y * size + i] * src2[i * size + x];
			}
		}
	}
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
	float translation_matrix[16];
	float rotation_matrix[16];
	float scaling_matrix[16];
	float x[16];
	float y[16];
	float intermediate_matrix[16];
	float final_matrix[16];

	//create matrix that translates vertices
	identity_matrix(translation_matrix);
	translate_matrix(translation_matrix, (float[3]){ app->translation_x, app->translation_y, app->translation_z });
	//create matrix that rotates vertices (may be susceptible to gimbal lock)
	identity_matrix(x);
	rotate_matrix(x, app->rotation_x, AXIS_X);
	identity_matrix(y);
	rotate_matrix(y, app->rotation_y, AXIS_Y);
	multiply_square_matrices(4, rotation_matrix, x, y);
	// rotate_matrix(rotation_matrix, app->rotation_z, AXIS_Z);
	//create matrix that scales vertices
	identity_matrix(scaling_matrix);
	scale_matrix(scaling_matrix, (float[3]){ app->scaling_x, app->scaling_y, app->scaling_z });

	//multiply scaling with rotating matrix
	multiply_square_matrices(
		4,
		intermediate_matrix,
		translation_matrix,
		rotation_matrix);
	//multiply matrix made above with translation matrix
	multiply_square_matrices(
		4,
		final_matrix,
		intermediate_matrix,
		scaling_matrix);

	//send the final combined matrix to the shader program
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "transform"),
		1,
		GL_FALSE,
		final_matrix);
}
