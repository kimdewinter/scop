#include "main.h"

static bool handle_keydown_event(t_app *app)
{
	switch (app->sdl.event.key.keysym.sym)
	{
	case SDLK_ESCAPE:
	{
		app->close_window = true;
	}
	break;
	case SDLK_b:
	{
		balance_vertices(app);
	}
	break;
	case SDLK_c:
	{
		balance_vertices(&app->obj_props);
	}
	break;
	case SDLK_UP:
	{
		app->obj_props.pos_z += 0.1f;
	}
	break;
	case SDLK_DOWN:
	{
		app->obj_props.pos_z -= 0.1f;
	}
	break;
	case SDLK_LEFT:
	{
		app->obj_props.pos_x -= 0.1f;
	}
	break;
	case SDLK_RIGHT:
	{
		app->obj_props.pos_x += 0.1f;
	}
	break;
	case SDLK_RSHIFT:
	{
		app->obj_props.pos_y += 0.1f;
	}
	break;
	case SDLK_RCTRL:
	{
		app->obj_props.pos_y -= 0.1f;
	}
	break;
	case SDLK_PAGEUP:
	{
		app->obj_props.scaling_x += 0.01f;
		app->obj_props.scaling_y += 0.01f;
		app->obj_props.scaling_z += 0.01f;
	}
	break;
	case SDLK_PAGEDOWN:
	{
		app->obj_props.scaling_x -= 0.01f;
		app->obj_props.scaling_y -= 0.01f;
		app->obj_props.scaling_z -= 0.01f;
	}
	break;
	case SDLK_r:
	{
		reset_camera(&app->cam_props);
	}
	break;
	case SDLK_t:
	{
		app->cam_props.track_obj = (app->cam_props.track_obj) ? false : true;
	}
	break;
	case SDLK_w:
	{
		app->cam_props.cam_pos_z += 0.1f;
	}
	break;
	case SDLK_s:
	{
		app->cam_props.cam_pos_z -= 0.1f;
	}
	break;
	case SDLK_a:
	{
		app->cam_props.cam_pos_x -= 0.1f;
	}
	break;
	case SDLK_d:
	{
		app->cam_props.cam_pos_x += 0.1f;
	}
	break;
	case SDLK_LSHIFT:
	{
		app->cam_props.cam_pos_y += 0.1f;
	}
	break;
	case SDLK_LCTRL:
	{
		app->cam_props.cam_pos_z -= 0.1f;
	}
	break;
		return (true);
	}
}

static bool handle_window_event(t_app *app)
{
	switch (app->sdl.event.window.windowID)
	{
	case SDL_WINDOWEVENT_SIZE_CHANGED:
		glViewport(
			0,
			0,
			app->sdl.event.window.data1,
			app->sdl.event.window.data2);
		break;
	}
	return (true);
}

bool handle_events(t_app *app)
{
	bool no_errors = true;

	while (SDL_PollEvent(&(app->sdl.event)))
	{
		if (!no_errors)
			return (false);

		switch (app->sdl.event.type)
		{
		case SDL_QUIT:
		{
			app->close_window = true;
		}
		break;
		case SDL_WINDOWEVENT:
		{
			no_errors = handle_window_event(app);
		}
		break;
		case SDL_KEYDOWN:
		{
			no_errors = handle_keydown_event(app);
		}
		break;
		}
	}
	return true;
}
