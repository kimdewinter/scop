#ifdef DEBUG

#include "main.h"
#include <stdio.h>

static void print_opengl_version()
{
	int major;
	int minor;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("Running OpenGL version %d.%d\n", major, minor);
}

static void print_opengl_extensions()
{
	int l;

	glGetIntegerv(GL_NUM_EXTENSIONS, &l);
	printf("Using OpenGL extensions:\n");
	for (int i = 0; i < l; i++)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
}

static void print_context_profile_mask(void)
{
	int mask;

	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &mask);
	ft_printf("GL Context Profile Mask: %b\n", mask);
}

void print_opengl_info(void)
{
	print_opengl_version();
	printf("Using OpenGL implementation by %s\n", glGetString(GL_VENDOR));
	printf("Using renderer %s\n", glGetString(GL_RENDERER));
	print_context_profile_mask();
	printf(
		"Primary version of GLSL supported is %s",
		glGetString(GL_SHADING_LANGUAGE_VERSION));
	print_opengl_extensions();
}

#endif
