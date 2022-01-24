#include "main.h"

bool init_opengl(void)
{
	GLenum error = GL_NO_ERROR;

//With Linux, must load GLAD before one calls gl functions
#if __linux__
	gladLoadGL();
#endif
	//Set default background color
	glClearColor(
		DEFAULT_CLEARCOLOR_RED,
		DEFAULT_CLEARCOLOR_GREEN,
		DEFAULT_CLEARCOLOR_BLUE,
		DEFAULT_CLEARCOLOR_ALPHA);

	//Make OpenGL hide things that are behind something else
	glEnable(GL_DEPTH_TEST);

	//Check if everything went ok
	error = glGetError();
	if (error != GL_NO_ERROR)
		return false;
	return true;
}
