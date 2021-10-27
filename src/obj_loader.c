#include "main.h"

bool load_obj(t_app *app, char const*const file_name)
{
	FILE *fp = fopen(file_name, "r");
	char *line = NULL;
	ssize_t line_len = 0;
	size_t buf_len = 0;

	if(!fp)
	{
		printf("Error: failure to open file in load_obj\n");
		return false;
	}
	line_len = getline(&line, &buf_len, fp);
	while (line_len > 0)
	{
		if (strcmp("v ", line) == 0)
		{
			if (!extract_vertex(line))
				return false;
		}
		else if (strcmp("f ", line) == 0)
		{
			if (!extract_faces(line))
				return false;
		}
		line_len = getline(&line, &buf_len, fp);
	}
}
