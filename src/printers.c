#include "main.h"
#include <stdio.h>

void print_instructions(void)
{
	char *controls[] = {
		"Esc: close program",
		"B: balance object vertices",
		"C: re-center object",
		"Arrows/Rshift/Rctrl: translate(move) object",
		"Pageup/down: scale object",
		"R: reset camera",
		"T: toggle track object/world center",
		"WASD/Lshift/Lctrl: translate(move) camera"};

	printf("Controls:\n");
	for (size_t i = 0; i < sizeof(controls) / sizeof(char *); i++)
		printf("%s\n", controls[i]);
}

#ifdef DEBUG

static void print_opengl_version()
{
	int major;
	int minor;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	printf("OpenGL version %d.%d\n", major, minor);
}

static void print_opengl_extensions()
{
	int l;

	glGetIntegerv(GL_NUM_EXTENSIONS, &l);
	printf("OpenGL extensions:\n");
	for (int i = 0; i < l; i++)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
}

void print_opengl_info(void)
{
	int n;

	print_opengl_version();
	printf("Implementation by %s\n", glGetString(GL_VENDOR));
	printf("Using renderer %s\n", glGetString(GL_RENDERER));
	printf(
		"Primary GLSL supported is %s\n",
		glGetString(GL_SHADING_LANGUAGE_VERSION));
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n);
	printf("Maximum nr of vertex attributes supported: %d\n", n);
	print_opengl_extensions();
}

#endif
