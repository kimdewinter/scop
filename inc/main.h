#ifndef MAIN_H

# define MAIN_H
# define PROGRAM_NAME "scop"

# include "libft.h"
# include <stdlib.h>
# include <SDL2/SDL.h>
# include <OpenGL/gl.h>

enum e_colour
{
	e_colour_red,
	e_colour_green,
	e_colour_blue
};

void display(SDL_Window *mainwindow);

#endif
