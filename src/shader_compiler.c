#include "main.h"

static bool create_and_link_shader_program(
	GLuint *shader_program,
	const GLuint vertex_shader,
	const GLuint fragment_shader)
{
	GLint success;
	GLchar info_log[512];

	*shader_program = glCreateProgram();
	glAttachShader(*shader_program, vertex_shader);
	glAttachShader(*shader_program, fragment_shader);
	glLinkProgram(*shader_program);
	glGetProgramiv(*shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(*shader_program, 512, NULL, info_log);
		fprintf(
			stdout,
			"ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n",
			info_log);
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (false);
	}
	return (true);
}

static bool compile_shader(
	GLuint *dst,
	const char *shader_filename,
	const GLenum shader_type)
{
	GLuint shader;
	GLchar *source;
	GLint success;
	GLchar info_log[512];

	shader = glCreateShader(shader_type);
	source = file_to_string(shader_filename);
	if (!source)
		return (false);
	glShaderSource(
		shader,
		1,
		(const GLchar *const *)&source,
		NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info_log);
		fprintf(
			stdout,
			"ERROR::SHADER::COMPILATION_FAILED\n%s\n",
			info_log);
		if (source)
			free(source);
		return (false);
	}
	*dst = shader;
	free(source);
	return (true);
}

// Compiled shader program is returned through parameter shader_program
bool compile_shader_program(
	GLuint *shader_program,
	const char *vertex_shader_filename,
	const char *fragment_shader_filename)
{
	GLuint vertex_shader = 0;
	GLuint fragment_shader = 0;

	// Compile individual shaders
	if (!compile_shader(
			&vertex_shader,
			vertex_shader_filename,
			GL_VERTEX_SHADER))
	{
		return (false);
	}
	if (!compile_shader(
			&fragment_shader,
			fragment_shader_filename,
			GL_FRAGMENT_SHADER))
	{
		glDeleteShader(vertex_shader);
		return (false);
	}

	// Create shader program and link shaders to it
	if (!create_and_link_shader_program(
			shader_program,
			vertex_shader,
			fragment_shader))
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return (false);
	}

	// Clean up shaders which aren't necessary anymore
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return (true);
}
