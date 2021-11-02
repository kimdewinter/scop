#include "main.h"

void set_bool(GLuint shader_program, const char *name, const bool value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), (int)value);
}

void set_int(GLuint shader_program, const char *name, const int value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), value);
}

void set_float(GLuint shader_program, const char *name, const float value)
{
	glUniform1f(glGetUniformLocation(shader_program, name), value);
}
