#include "main.h"

bool initialize_sdl(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void set_sdl_precreation_attributes(void)
{
	//Specify OpenGL version #.#
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    //Use OpenGL's Core profile (disable deprecated Fixed Function Pipeline)
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	//Use Forward Compatible mode (don't support deprecated functionality)
	SDL_GL_SetAttribute(
		SDL_GL_CONTEXT_FLAGS,
		SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}

bool set_sdl_postcreation_attributes(void)
{
	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		ft_printf(
			"Warning: Unable to set VSync! SDL Error: %s\n",
			SDL_GetError());
		return false;
	}
	return true;
}

bool create_window(t_app *app)
{
    app->sdl.window = SDL_CreateWindow(
		PROGRAM_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		app->screen_width,
		app->screen_height,
		SDL_WINDOW_OPENGL);
	if (app->sdl.window == NULL)
	{
		ft_printf(
			"Window could not be created! SDL Error: %s\n",
			SDL_GetError());
		return false;
	}
	return true;
}

bool create_context(t_app *app)
{
	app->sdl.context = SDL_GL_CreateContext(app->sdl.window);
	if (app->sdl.context == NULL)
	{
		ft_printf(
			"OpenGL context could not be created! SDL Error: %s\n",
			SDL_GetError());
		return false;
	}
	return true;
}

void shutdown_sdl(t_app *app)
{
	SDL_GL_DeleteContext(app->sdl.context);
    SDL_DestroyWindow(app->sdl.window);
    SDL_Quit();
}