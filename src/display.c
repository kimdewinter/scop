#include "../inc/main.h"

void display(SDL_Window *mainwindow)
{
	/* INPUT VERTEX */
	
	//create the shape
	const float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	//create Vertex Buffer Object and data on the GPU
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/* VERTEX SHADER */

	//write shader source code in GLSL and store in string
	const char *vertexShaderSource = "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

	//create vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//attach shader source code to shader object, and compile
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//check if compile succesful; if not, print error
	int success;
	//char infoLog[512];
	(void)mainwindow;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
}
