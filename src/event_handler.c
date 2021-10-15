#include "main.h"
#include "matrix_handler.h"

static void do_thing(void)
{
	float oldvec[4] = { 0.25f, 0.30f, 0.35f, 1.0f };
	float trans[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	// float translation_vec[4] = { 1.0f, 1.0f, 0.0f };
	float newvec[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// translate_matrix(trans, translation_vec);
	rotate_matrix(trans, 42, AXIS_Z);
	for (int i = 0; i < 16; i++)
	{
			if (i % 4 != 3)
				newvec[i / 4] += trans[i] * oldvec[i % 4];
	}
	for (int i = 0; i < 4; i++)
	{
		printf("%f\n", newvec[i]);
	}
}

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
					case SDLK_SPACE:
					{
						do_thing();
					}
					break;
				}
			}
			break;
		}
	}
	return true;
}
