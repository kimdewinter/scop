#include "main.h"
#include "stb_image.h"

bool parse_texture_arg(t_app *app, int argc, char *argv[])
{
	if (argc < 2)
	{
		fprintf(
			stdout,
			"Error: %s received too few parameters\n",
			PROGRAM_NAME
		);
		return (false);
	}
	else if (argc == 2)
		return (true);
	else if (argc > 3)
	{
		fprintf(
			stdout,
			"Error: %s received too many parameters\n",
			PROGRAM_NAME
		);
		return (false);
	}
	app->texture_file_name = strdup(argv[2]);
	return (true);
}

bool load_texture(t_app *app)
{
	int width, height, nrChannels;

	// load and create a texture 
	// -------------------------
	glGenTextures(1, &app->texture);
	glBindTexture(GL_TEXTURE_2D, app->texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(
		app->texture_file_name,
		&width,
		&height,
		&nrChannels,
		0
	);
	if (data)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture\n");
	}
	stbi_image_free(data);

	glUseProgram(app->shader_program);
	glUniform1i(glGetUniformLocation(app->shader_program, "texture1"), 0);

	return true;
}

// bool load_texture_new(t_app *app, char const * const file_name)
// {
// 	GLuint texture;
// 	int width, height;
// 	unsigned char *data;
// 	FILE *file;

// 	file = fopen(file_name, "rb");
// 	if (!file)
// 		return false;
// 	width 
// }
