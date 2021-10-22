#include "main.h"

bool handle_events(t_app *app)
{
	while (SDL_PollEvent(&(app->sdl.event)))
	{
		switch(app->sdl.event.type)
		{
			case SDL_QUIT:
			{
				app->close_window = true;
			}
			break;
			case SDL_WINDOWEVENT:
			{
				switch(app->sdl.event.window.windowID)
				{
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					{
						glViewport(0, 0, app->sdl.event.window.data1, app->sdl.event.window.data2);
					}
					break;
				}
			}
			break;
			case SDL_KEYDOWN:
			{
				switch(app->sdl.event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						app->close_window = true;
					}
					break;
					case SDLK_d:
					{
						rotate_matrix(app->transformation_matrix, 10, AXIS_X)
					}
					break;
					case SDLK_a:
					{
						rotate_matrix(app->transformation_matrix, -10, AXIS_X)
					}
					break;
					case SDLK_w:
					{
						rotate_matrix(app->transformation_matrix, 10, AXIS_Y)
					}
					break;
					case SDLK_s:
					{
						rotate_matrix(app->transformation_matrix, -10, AXIS_Y)
					}
					break;
					case SDLK_r:
					{
						rotate_matrix(app->transformation_matrix, 10, AXIS_Z);
					}
					break;
					case SDLK_f:
					{
						rotate_matrix(app->transformation_matrix, -10, AXIS_Z);
					}
					break;
					case SDLK_RIGHT:
					{
						translate_matrix(app->transformation_matrix, { 0.1f, 0.0f, 0.0f });
					}
					break;
					case SDLK_LEFT:
					{
						translate_matrix(app->transformation_matrix, { -0.1f, 0.0f, 0.0f });
					}
					break;
					case SDLK_UP:
					{
						translate_matrix(app->transformation_matrix, { 0.0f, 0.1f, 0.0f });
					}
					break;
					case SDLK_DOWN:
					{
						translate_matrix(app->transformation_matrix, { 0.0f, -0.1f, 0.0f });
					}
					break;
					case SDLK_EQUALS:
					{
						scale_matrix(app->transformation_matrix, { 0.1f, 0.1f, 0.1f });
					}
					break;
					case SDLK_MINUS:
					{
						scale_matrix(app->transformation_matrix, { -0.1f, -0.1f, -0.1f });
					}
					break;
				}
			}
			break;
		}
	}
	return true;
}
