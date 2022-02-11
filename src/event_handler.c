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
	case SDLK_c:
	{
		center_object(&(app->obj_props));
	}
	break;
	case SDLK_s:
	{
		app->obj_props.pos_z += 0.1f;
	}
	break;
	case SDLK_w:
	{
		app->obj_props.pos_z -= 0.1f;
	}
	break;
	case SDLK_d:
	{
		app->obj_props.pos_x += 0.1f;
	}
	break;
	case SDLK_a:
	{
		app->obj_props.pos_x -= 0.1f;
	}
	break;
	case SDLK_e:
	{
		app->obj_props.pos_y += 0.1f;
	}
	break;
	case SDLK_q:
	{
		app->obj_props.pos_y -= 0.1f;
	}
	break;
	case SDLK_r:
	{
		app->obj_props.rotation_z += 0.1f;
	}
	break;
	case SDLK_y:
	{
		app->obj_props.rotation_z -= 0.1f;
	}
	break;
	case SDLK_t:
	{
		app->obj_props.rotation_x -= 0.1f;
	}
	break;
	case SDLK_g:
	{
		app->obj_props.rotation_x += 0.1f;
	}
	break;
	case SDLK_h:
	{
		app->obj_props.rotation_y += 0.1f;
	}
	break;
	case SDLK_f:
	{
		app->obj_props.rotation_y -= 0.1f;
	}
	break;
	case SDLK_x:
	{
		app->obj_props.scaling_x += 0.01f;
		app->obj_props.scaling_y += 0.01f;
		app->obj_props.scaling_z += 0.01f;
	}
	break;
	case SDLK_z:
	{
		app->obj_props.scaling_x -= 0.01f;
		app->obj_props.scaling_y -= 0.01f;
		app->obj_props.scaling_z -= 0.01f;
	}
	break;
	case SDLK_v:
	{
		reset_camera(&app->cam_props);
	}
	break;
	case SDLK_n:
	{
		app->cam_props.track_obj = (app->cam_props.track_obj) ? false : true;
	}
	break;
	case SDLK_m:
	{
		if (app->texture_file_name && !app->obj_props.display_texture)
		{
			set_uniform_int(app->shader_program, "texture_provided", 1);
			app->obj_props.display_texture = true;
		}
		else
		{
			set_uniform_int(app->shader_program, "texture_provided", 0);
			app->obj_props.display_texture = false;
		}
	}
	break;
	case SDLK_k:
	{
		app->cam_props.cam_pos_z += 0.1f;
	}
	break;
	case SDLK_i:
	{
		app->cam_props.cam_pos_z -= 0.1f;
	}
	break;
	case SDLK_l:
	{
		app->cam_props.cam_pos_x += 0.1f;
	}
	break;
	case SDLK_j:
	{
		app->cam_props.cam_pos_x -= 0.1f;
	}
	break;
	case SDLK_o:
	{
		app->cam_props.cam_pos_y += 0.1f;
	}
	break;
	case SDLK_u:
	{
		app->cam_props.cam_pos_y -= 0.1f;
	}
	break;
		return (true);
	}
	return (true);
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
