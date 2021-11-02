#include "libobj_internal.h"
#include <string.h>

bool extract_vertex(t_reader *reader)
{
	float vertex[3];
	char *walker = reader->line;

	if (!walker)
	{
		printf("Error: reader->line is NULL in extract_vertex\n");
		return (false);
	}
	
	//ensure line starts with "v "
	if (strncmp("v ", walker, 2) != 0)
		return (true);
	walker += 2;

	//first float
	if (!is_float(walker))
		return (true);
	vertex[0] = atof(walker);
	walker = skip_float(walker);

	//ensure float is followed by a ' '
	if (*walker != ' ')
		return (true);
	walker++;

	//second float
	if (!is_float(walker))
		return (true);
	vertex[1] = atof(walker);
	walker = skip_float(walker);

	//ensure float is followed by a ' '
	if (*walker != ' ')
		return (true);
	walker++;

	//third float
	if (!is_float(walker))
		return (true);
	vertex[2] = atof(walker);
	walker = skip_float(walker);

	//ensure end of line
	if (!(*walker == '\n' || *walker == '\0'))
		return (true);

	//add vertex to vector
	if (!vector_append(&reader->vertices, &vertex, 3 * sizeof(float)))
		return false;
	return (true);
}

bool extract_face(t_reader *reader)
{
	unsigned int triangle_one[3];
	unsigned int triangle_two[3];
	char *walker = reader->line;

	if(!walker)
	{
		printf("Error: reader->line is NULL in extract_face\n");
		return (false);
	}

	//ensure line starts with "f "
	if(strncmp("f ", walker, 2) != 0)
		return (true);
	walker += 2;

	//first uint
	if (!is_uint(walker))
		return (true);
	triangle_one[0] = atoi(walker);
	walker = skip_uint(walker);

	//ensure uint is followed by a ' '
	if (*walker != ' ')
		return (true);
	walker++;

	//second uint
	if (!is_uint(walker))
		return (true);
	triangle_one[1] = atoi(walker);
	triangle_two[0] = atoi(walker);
	walker = skip_uint(walker);

	//ensure uint is followed by a ' '
	if (*walker != ' ')
		return (true);
	walker++;

	//third uint
	if (!is_uint(walker))
		return (true);
	triangle_one[2] = atoi(walker);
	triangle_two[1] = atoi(walker);
	walker = skip_uint(walker);

	//check if end of line, which means only three face-elements are given
	//and we can submit only triangle_one
	if (*walker == '\n' || *walker == '\0')
	{
		if (!vector_append(
			&reader->indices,
			&triangle_one,
			3 * sizeof(unsigned int)))
		{
			return (false);
		}
		return (true);
	}

	//continue assuming four face-elements are given
	//which means we are dealing with a cube made up out of two triangles

	//ensure uint is followed by a ' '
	if (*walker != ' ')
		return (true);
	walker++;

	//fourth uint (note: triangle_one[2] is overwritten)
	if (!is_uint(walker))
		return (true);
	triangle_one[2] = atoi(walker);
	triangle_two[2] = atoi(walker);
	walker = skip_uint(walker);

	//ensure end of line
	if (!(*walker == '\n' || *walker == '\0'))
		return (true);

	if (!vector_append(
		&reader->indices,
		&triangle_one,
		3 * sizeof(unsigned int)) ||
		!vector_append(
		&reader->indices,
		&triangle_two,
		3 * sizeof(unsigned int)))
	{
		return (false);
	}

	return (true);
}

/*
to transform two triangles into a square,
use the indices like this:

unsigned int indices[] = {
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
};
*/