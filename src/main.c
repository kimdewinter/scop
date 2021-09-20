#include "../inc/main.h"

int main(int argc, char *argv[])
{
    SDL_Event event;
    SDL_GLContext context;
    SDL_Window *window;

	//Initialize SDL and attributes
    SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// SDL_GL_SetSwapInterval(1);

	//Create window and context
    window = SDL_CreateWindow(
		PROGRAM_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCR_WIDTH,
		SCR_HEIGHT,
		SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	float points[] = {
		0.0f,  0.5f,  0.0f,
		0.5f, -0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// const char* vertex_shader = "#version 400\nin vec3 vp;\nvoid main() {\ngl_Position = vec4(vp, 1.0);\n}\n";
	const char* vertex_shader =
	"#version 410\n"
	"in vec3 vp;\n"
	"void main() {\n"
	"  gl_Position = vec4(vp, 1.0);\n"
	"}\n\0";
	// const char* fragment_shader = "#version 400\nout vec4 frag_colour;\nvoid main() {\nfrag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n}\n";
	const char* fragment_shader =
	"#version 410\n"
	"out vec4 frag_colour;\n"
	"void main() {\n"
	"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);\n"
	"}\n\0";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram(shader_programme);

	/* Main loop. */
    while (1) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//draw stuff here
		glUseProgram(shader_programme);
		glBindVertexArray(vao);
		//draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, 3);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break;
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					break;
			}
		}
		//swap buffer onto the window
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    (void)argc;// Remove line before submission
    (void)argv;// Remove line before submission
    return EXIT_SUCCESS;
}
