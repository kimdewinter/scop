#include "libobj_internal.h"

bool extract_vertex(t_reader *reader)
{
	float vertex[3];

	if (!reader->line)
		return (false);
	
	//ensure line starts with "v "
	if (strcmp("v ", reader->line) != 0)
		return (false);
	reader->line += 2;

	//first float
	if (!is_float(reader->line))
		return (false);
	vertex[0] = atof(reader->line);
	reader->line = skip_float(reader->line);

	//ensure float is followed by a ' '
	if (*reader->line != ' ')
		return (false);
	reader->line++;

	//second float
	if (!is_float(reader->line))
		return (false);
	vertex[1] = atof(reader->line);
	reader->line = skip_float(reader->line);

	//ensure float is followed by a ' '
	if (*reader->line != ' ')
		return (false);
	reader->line++;

	//third float
	if (!is_float(reader->line))
		return (false);
	vertex[2] = atof(reader->line);
	reader->line = skip_float(reader->line);

	//ensure end of line
	if (!(*reader->line == '\n' || *reader->line == '\0'))
		return (false);

	//add vertex to vector
	if (!vector_append(reader->vertices, &vertex, 3 * sizeof(float)))
		return false;
	return (true);
}

bool extract_face(t_reader *reader)
{
	
}
