#include "main.h"

static bool import_image(
	const char *file_name,
	unsigned char **dst_data,
	unsigned int *dst_width,
	unsigned int *dst_height)
{
	//Data read from the header of the BMP file
	unsigned char header[54]; //Each BMP file begins by a 54-bytes header
	unsigned int dataPos;	  //Position in the file where the actual data begins
	unsigned int width, height;
	unsigned char *data;
	unsigned int imageSize; //= width * height * 3
	FILE *file = fopen(file_name, "r");

	if (!file)
	{
		fprintf(stdout, "Error: failed to open texture file\n");
		return (false);
	}
	if (fread(header, sizeof(unsigned char), 54, file) != 54 ||
		header[0] != 'B' ||
		header[1] != 'M')
	{
		fclose(file);
		fprintf(stdout, "Error: texture must be a valid .bmp file\n");
		return (false);
	}

	//Read ints from the byte array
	dataPos = *(int *)&(header[0x0A]);
	imageSize = *(int *)&(header[0x22]);
	width = *(int *)&(header[0x12]);
	height = *(int *)&(header[0x16]);

	//Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = width * height * 3; //3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54;
	//The BMP header is done that way

	//Create a buffer
	data = (unsigned char *)malloc(imageSize * sizeof(unsigned char));
	if (!data)
	{
		fclose(file);
		fprintf(stdout, "Error: misallocation in import_image\n");
		return (false);
	}

	//Read the actual data from the file into the buffer
	fread(data, sizeof(unsigned char), imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);

	*dst_data = data;
	*dst_width = width;
	*dst_height = height;
	return (true);
}

bool load_texture(t_app *app)
{
	unsigned char *data;
	unsigned int width, height;

	//Set uniform "texture_provided" to 0 until texture is correctly prepared
	glUseProgram(app->shader_program);
	set_uniform_int(app->shader_program, "texture_provided", 0);
	app->obj_props.display_texture = false;
	//Check if texture file is provided as one of executable's arguments
	if (!app->texture_file_name)
		return (true);

	//Generate texture object to work with
	glGenTextures(1, &app->texture);
	//Set all upcoming GL_TEXTURE_2D operations to affect this texture object
	glBindTexture(GL_TEXTURE_2D, app->texture);
	//Set texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//set texture wrapping to GL_REPEAT(default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Load image, create texture and generate mipmaps
	if (import_image(
			app->texture_file_name,
			&data,
			&width,
			&height) &&
		data)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_BGRA,
			GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		return (false);

	free(data);
	//Tell shader that a texture has been provided
	glUseProgram(app->shader_program);
	set_uniform_int(app->shader_program, "texture_provided", 1);
	app->obj_props.display_texture = true;
	//Tell shader that the texture object it must use has ID 0
	set_uniform_int(app->shader_program, "texture1", 0);
	return (true);
}
