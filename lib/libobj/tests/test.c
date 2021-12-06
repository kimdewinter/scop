#include "libobj.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	t_obj *obj;

	obj = obj_import("tests/42.obj"); //give path and filename to obj file here
	obj = obj_import("lib/libobj/tests/42.obj");
	if (!obj)
	{
		printf("Epic fail on obj_import.\n");
		return (EXIT_FAILURE);
	}
	printf("\nPrinting vertexes:\n");
	for (int i = 0; i < (int)obj->vertices_len; i++)
	{
		if (i % 3 == 0 && i > 0)
			printf("\n");
		printf("%f ", obj->vertices[i]);
	}
	printf("\n\nPrinting indices:\n");
	for (int i = 0; i < (int)obj->indices_len; i++)
	{
		if (i % 3 == 0 && i > 0)
			printf("\n");
		printf("%d ", obj->indices[i]);
	}
	obj_delete(&obj);
	if (obj)
	{
		printf("Epic fail on obj_delete.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
