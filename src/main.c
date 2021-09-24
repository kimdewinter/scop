#include "main.h"

static int shutdown(t_app *app, int success)
{
	shutdown_sdl(app);
	return success;
}

int main(int argc, char *argv[])
{
	t_app app;

    (void)argc;//Remove this line before submission
    (void)argv;//Remove this line before submission
	construct_t_app(&app);
	if (!get_context_and_window(&app))
		return shutdown(&app, EXIT_FAILURE);
    return shutdown(&app, EXIT_SUCCESS);
}
