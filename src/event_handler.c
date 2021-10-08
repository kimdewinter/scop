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
				}
			}
			break;
		}
	}
	return true;
}
