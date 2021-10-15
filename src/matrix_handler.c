#include "matrix_handler.h"
#include <math.h>

void translate_matrix(float matrix[16], const float translation_vector[3])
{
	matrix[3] = translation_vector[0];
	matrix[7] = translation_vector[1];
	matrix[11] = translation_vector[2];
}

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
			matrix[6] = -sin((double)rotation_degrees);
			matrix[9] = sin((double)rotation_degrees);
			matrix[10] = cos((double)rotation_degrees);
		}
		break;
		case AXIS_Y:
		{
			matrix[0] = cos((double)rotation_degrees);
			matrix[2] = sin((double)rotation_degrees);
			matrix[8] = -sin((double)rotation_degrees);
			matrix[10] = cos((double)rotation_degrees);
		}
		break;
		case AXIS_Z:
		{
			matrix[0] = cos((double)rotation_degrees);
			matrix[1] = -sin((double)rotation_degrees);
			matrix[4] = sin((double)rotation_degrees);
			matrix[5] = cos((double)rotation_degrees);
		}
		break;
	}
}
