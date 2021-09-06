/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/04 16:28:28 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/09/06 17:13:15 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <OpenGL/gl.h>
#define PROGRAM_NAME "scop"

void sdldie(const char *msg)
{
    ft_printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void checkSDLError(int line)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		ft_printf("SDL Error: %s\n", error);
    	if (line != -1)
			ft_printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}

int main(int argc, char *argv[])
{
    SDL_Window		*mainwindow;
    SDL_GLContext	maincontext;
    SDL_Event       e;
    int             quit;
    enum e_colour   colour;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)//Initialize SDL's Video subsystem
        sdldie("Unable to initialize SDL");

    // Request opengl 4.1 context with a Core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Turn on double buffering with a 24bit Z buffer
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // Create our window centered at 512x512 resolution
    mainwindow = SDL_CreateWindow(
		PROGRAM_NAME,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
        1280,
		720,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow)
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    // Create our opengl context and attach it to our window
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);

    // This makes our buffer swap syncronized with the monitor vertical refresh
    SDL_GL_SetSwapInterval(1);

    quit = 0;
    colour = e_colour_red;
    //While application is running
    while (!quit)
    {

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT ||
				(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
            {
                quit = 1;
            }
        }
    }

    // Delete our opengl context, destroy our window, and shutdown SDL
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    (void)argc;// Remove line before submission
    (void)argv;// Remove line before submission
    return EXIT_SUCCESS;
}
