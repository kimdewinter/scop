#include "main.h"
#include "matrix_handler.h"

static int shutdown(t_app *app, int exit_return)
{
	shutdown_sdl(app);
	if (app->shader_program)
		glDeleteProgram(app->shader_program);
	return exit_return;
}

int main(int argc, char *argv[])
{
	t_app app;

    (void)argc;//Remove this line before submission
    (void)argv;//Remove this line before submission	
	construct_t_app(&app);
	if (!get_context_and_window(&app))
		return shutdown(&app, EXIT_FAILURE);
	if (!init_opengl())
		return shutdown(&app, EXIT_FAILURE);
	if (!compile_shader_program(
		&app.shader_program,
		"vertex_shader.vert",
		"fragment_shader.frag"))
		return shutdown(&app, EXIT_FAILURE);
	if (!load_vertices(&app))
		return shutdown(&app, EXIT_FAILURE);
	// if (!load_indices(&app))
		// return shutdown(&app, EXIT_FAILURE);
	if (!load_buffers(&app))
		return shutdown(&app, EXIT_FAILURE);
	if (!load_textures(&app))
		return shutdown(&app, EXIT_FAILURE);
	glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

	app.close_window = false;
	while(!app.close_window)
	{
		if (!handle_events(&app))
			shutdown(&app, EXIT_FAILURE);
		// render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, app.texture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, app.texture2);

		transform(&app);

        // draw our first triangle
        glUseProgram(app.shader_program);
        glBindVertexArray(app.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time
		SDL_GL_SwapWindow(app.sdl.window);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &app.VAO);
    glDeleteBuffers(1, &app.VBO);
    // glDeleteBuffers(1, &app.EBO);
    glDeleteProgram(app.shader_program);

    return shutdown(&app, EXIT_SUCCESS);
}
