#ifndef MATRIX_HANDLER_H
# define MATRIX_HANDLER_H

typedef enum e_axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z
} t_axis;

void rotate_matrix(
	float matrix[16],
	const float rotation_degrees,
	t_axis rotation_axis);
void translate_matrix(float matrix[16], const float translation_vector[3]);

#endif
