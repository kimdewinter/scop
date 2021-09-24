#ifndef MAIN_H

# define MAIN_H
# define PROGRAM_NAME "scop"
# define DEFAULT_SCREEN_WIDTH 800
# define DEFAULT_SCREEN_HEIGHT 600

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
	int screen_width;
	int screen_height;
} t_app;

unsigned int compile_shader_program(
	const char* vertex_shader_filename,
	const char* fragment_shader_filename);
void construct_t_app(t_app *app);
bool create_context(t_app *app);
bool create_window(t_app *app);
bool initialize_sdl(void);
void set_sdl_precreation_attributes(void);
bool set_sdl_postcreation_attributes(void);
void shutdown_sdl(t_app *app);

# ifdef DEBUG
void print_opengl_info(void);
# endif

#endif
