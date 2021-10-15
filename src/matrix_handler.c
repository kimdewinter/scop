#include "main.h"

void translate_matrix(float matrix[16], const float translation_vector[3])
{
	matrix[3] = translation_vector[0];
	matrix[7] = translation_vector[1];
	matrix[11] = translation_vector[2];
}
