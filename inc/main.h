#ifndef MAIN_H

# define MAIN_H
# define PROGRAM_NAME "scop"
# define DEFAULT_SCREEN_WIDTH 1280
# define DEFAULT_SCREEN_HEIGHT 720
# define DEFAULT_CLEARCOLOR_RED 0.0f
# define DEFAULT_CLEARCOLOR_GREEN 0.0f
# define DEFAULT_CLEARCOLOR_BLUE 0.0f
# define DEFAULT_CLEARCOLOR_ALPHA 1.0f

# include "libft.h"
# include <stdlib.h>
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <OpenGL/gl3.h>

typedef struct s_sdl
{
	SDL_Window *window;
	SDL_GLContext context;
	SDL_Event event;
} t_sdl;

typedef struct s_app
{
	struct s_sdl sdl;
	GLuint shader_program;
	float *vertices;
	unsigned int vertices_length;
	unsigned int *indices;
	unsigned int indices_length;
	GLuint VBO;//Vertex Buffer Object
	GLuint VAO;//Vertex Buffer Array
	GLuint EBO;//Element Buffer Object
	GLuint texture;
	bool close_window;
} t_app;

bool compile_shader_program(
	GLuint *shader_program,
	const char *vertex_shader_filename,
	const char *fragment_shader_filename);
void construct_t_app(t_app *app);
char *file_to_string(const char *file_name);
bool get_context_and_window(t_app *app);
bool init_opengl(void);
bool load_buffers(t_app *app);
bool load_indices(t_app *app);
bool load_textures(t_app *app);
bool load_vertices(t_app *app);
void set_bool(GLuint shader_program, const char *name, const bool value);
void set_int(GLuint shader_program, const char *name, const int value);
void set_float(GLuint shader_program, const char *name, const float value);
void shutdown_sdl(t_app *app);

# ifdef DEBUG
void print_opengl_info(void);
# endif

#endif
