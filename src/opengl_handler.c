#include "main.h"

bool init_opengl(void)
{
	GLenum error = GL_NO_ERROR;

	glClearColor(
		DEFAULT_CLEARCOLOR_RED,
		DEFAULT_CLEARCOLOR_GREEN,
		DEFAULT_CLEARCOLOR_BLUE,
		DEFAULT_CLEARCOLOR_ALPHA);
	glEnable(GL_DEPTH_TEST);
	error = glGetError();
	if (error != GL_NO_ERROR)
		return false;
	return true;
}
