#include "../inc/main.h"

static const GLchar* vertex_shader_source = "#version 120\nattribute vec2 coord2d;\nvoid main() {\ngl_Position = vec4(coord2d, 0.0, 1.0);\n}\n";
static const GLchar* fragment_shader_source = "#version 120\nvoid main() {\ngl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n}\n";
// const char *vertex_shader_source = "#version 410 core\nlayout (location = 0) in vec3 aPos;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}\0";
//const char *fragment_shader_source = "#version 410 core\nout vec4 FragColor;\nvoid main()\n{\nFragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n}\n\0";

static GLfloat vertices[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
};

GLuint common_get_shader_program(
    const char *vertex_shader_source,
    const char *fragment_shader_source
) {
    GLchar *log = NULL;
    GLint log_length;
	GLint success;
    GLuint fragment_shader;
	GLuint shader_program;
	GLuint vertex_shader;

    /* Vertex shader */
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &log_length);
    log = malloc(log_length);
    if (log_length > 0) {
        glGetShaderInfoLog(vertex_shader, log_length, NULL, log);
        ft_printf("vertex shader log:\n\n%s\n", log);
    }
    if (!success) {
        ft_printf("vertex shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Fragment shader */
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = realloc(log, log_length);
        glGetShaderInfoLog(fragment_shader, log_length, NULL, log);
        ft_printf("fragment shader log:\n\n%s\n", log);
    }
    if (!success) {
        ft_printf("fragment shader compile error\n");
        exit(EXIT_FAILURE);
    }

    /* Link shaders */
    shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
    glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &log_length);
    if (log_length > 0) {
        log = realloc(log, log_length);
        glGetProgramInfoLog(shader_program, log_length, NULL, log);
        ft_printf("shader link log:\n\n%s\n", log);
    }
    if (!success) {
        ft_printf("shader link error");
        exit(EXIT_FAILURE);
    }

    /* Cleanup. */
    free(log);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return shader_program;
}

int main(int argc, char *argv[])
{
    GLint attribute_coord2d;
    GLuint shader_program;
	GLuint vbo;
    SDL_Event event;
    SDL_GLContext context;
    SDL_Window *window;

	//Initialize SDL and attributes
    SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    //SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetSwapInterval(1);

	//Create window and context
    window = SDL_CreateWindow(
		PROGRAM_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCR_WIDTH,
		SCR_HEIGHT,
		SDL_WINDOW_OPENGL);
    context = SDL_GL_CreateContext(window);

    /* Shader setup. */
    shader_program = common_get_shader_program(vertex_shader_source, fragment_shader_source);
    attribute_coord2d = glGetAttribLocation(shader_program, "coord2d");

    /* Buffer setup. */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(attribute_coord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Global draw state */
	glUseProgram(shader_program);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Main loop. */
    while (1) {
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableVertexAttribArray(attribute_coord2d);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(attribute_coord2d);
        SDL_GL_SwapWindow(window);
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

    }

    /* Cleanup. */
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader_program);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    (void)argc;// Remove line before submission
    (void)argv;// Remove line before submission
    return EXIT_SUCCESS;
}
