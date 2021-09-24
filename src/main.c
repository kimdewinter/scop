#include "main.h"

int main(int argc, char *argv[])
{
	t_app app;

    (void)argc;// Remove line before submission
    (void)argv;// Remove line before submission
	construct_t_app(&app);
	if (!initialize_sdl())
		return EXIT_FAILURE;
	set_sdl_precreation_attributes();
	if (!create_window(&app))
		return EXIT_FAILURE;
	if (!create_context(&app))
		return EXIT_FAILURE;
	if (!set_sdl_postcreation_attributes())
		return EXIT_FAILURE;
#ifdef DEBUG
	print_opengl_info();
#endif
	shutdown_sdl(&app);
    return EXIT_SUCCESS;
}
