#include "main.h"

void construct_t_app(t_app *app)
{
	ft_memset(app, 0, sizeof(app));
	app->screen_width = DEFAULT_SCREEN_WIDTH;
	app->screen_height = DEFAULT_SCREEN_HEIGHT;
}
