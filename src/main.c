/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kde-wint <kde-wint@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/04 16:28:28 by kde-wint      #+#    #+#                 */
/*   Updated: 2021/08/31 18:30:05 by kde-wint      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include <stdlib.h>
#include <SDL.h>
#include <OpenGL/gl.h>
#define PROGRAM_NAME "scop"

void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void checkSDLError(int line)
{
#ifndef NDEBUG
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		printf("SDL Error: %s\n", error);
    	if (line != -1)
			printf(" + line: %i\n", line);
		SDL_ClearError();
	}
#endif
}

int main(int argc, char *argv[])
{
    SDL_Window		*mainwindow;
    SDL_GLContext	maincontext;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)//Initialize SDL's Video subsystem
        sdldie("Unable to initialize SDL");

    // Request opengl 3.2 context
    // 4.6 is the newest, Macs only support up to 4.1, 3.2 is for older Macs
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
        512,
		512,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow)
        sdldie("Unable to create window");

    checkSDLError(__LINE__);

    // Create our opengl context and attach it to our window
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);

    // This makes our buffer swap syncronized with the monitor vertical refresh
    SDL_GL_SetSwapInterval(1);

    SDL_Event e;
    SDL_PollEvent(&e);
/*
    int quit = 0;
    while(quit < 1)
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }
        }
    }
*/

    // Clear our buffer with a red background
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    // Swap our back buffer to the front
    SDL_GL_SwapWindow(mainwindow);
    // Wait 2 seconds
    SDL_Delay(2000);

    // Same as above, but green
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);

    // Same as above, but blue
    glClearColor ( 0.0, 0.0, 1.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);

    // Delete our opengl context, destroy our window, and shutdown SDL
    SDL_Delay(2000);
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    (void)argc;// Remove line before submission
    (void)argv;// Remove line before submission
    return EXIT_SUCCESS;
}
