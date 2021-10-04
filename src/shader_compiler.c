#include "main.h"

bool compile_shader_program(
	GLuint *shader_program,
	const char *vertex_shader_filename,
	const char *fragment_shader_filename)
{
	GLuint vertex_shader;
	GLchar *vertex_source;
	GLuint fragment_shader;
	GLchar *fragment_source;
	GLint success;
	GLchar info_log[512];

	// Compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	vertex_source = file_to_string(vertex_shader_filename);
	if (!vertex_source)
		return false;
	glShaderSource(vertex_shader, 1, (const GLchar *const *)&vertex_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
		printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
		if (vertex_source)
			free(vertex_source);
		return false;
	}

	// Compile fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	fragment_source = file_to_string(fragment_shader_filename);
	if (!fragment_source)
		return false;
	glShaderSource(fragment_shader, 1, (const GLchar *const *)&fragment_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
		printf("ERROR::FRAGMENT::VERTEX::COMPILATION_FAILED\n%s\n", info_log);
		glDeleteShader(vertex_shader);
		if (vertex_source)
			free(vertex_source);
		if (fragment_source)
			free(fragment_source);
		return false;
	}

	// Link shaders to create shader program
	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vertex_shader);
	glAttachShader(*shader_program, fragment_shader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", info_log);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		if (vertex_source)
			free(vertex_source);
		if (fragment_source)
			free(fragment_source);
		return false;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (vertex_source)
		free(vertex_source);
	if (fragment_source)
		free(fragment_source);
	return true;
}
