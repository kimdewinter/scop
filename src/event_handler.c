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
						app->translation_x += 0.1f;
					}
					break;
					case SDLK_a:
					{
						app->translation_x -= 0.1f;
					}
					break;
					case SDLK_w:
					{
						app->translation_y += 0.1f;
					}
					break;
					case SDLK_s:
					{
						app->translation_y -= 0.1f;
					}
					break;
					case SDLK_r:
					{
						app->scaling_x += 0.1f;
						app->scaling_y += 0.1f;
						app->scaling_z += 0.1f;
					}
					break;
					case SDLK_f:
					{
						app->scaling_x -= 0.1f;
						app->scaling_y -= 0.1f;
						app->scaling_z -= 0.1f;
					}
					break;
					case SDLK_RIGHT:
					{
						app->rotation_y -= 0.1f;
					}
					break;
					case SDLK_LEFT:
					{
						app->rotation_y += 0.1f;
					}
					break;
					case SDLK_UP:
					{
						app->rotation_x += 0.1f;
					}
					break;
					case SDLK_DOWN:
					{
						app->rotation_x += 0.1f;
					}
					break;
				}
			}
			break;
		}
	}
	return true;
}
