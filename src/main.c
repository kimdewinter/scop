#include "main.h"

static int shutdown(t_app *app, int exit_return)
{
	shutdown_sdl(app);
	if (app->shader_program)
		glDeleteProgram(app->shader_program);
	if (app->vertices)
		free(app->vertices);
	if (app->indices)
		free(app->indices);
	if (app->obj_file_name)
		free(app->obj_file_name);
	if (app->texture_file_name)
		free(app->texture_file_name);
	return (exit_return);
}

int main(int argc, char const ** const argv)
{
	t_app app;

	memset(&app, 0, sizeof(t_app));
	if (!parse_main_args(&app, argc, argv))
		return (shutdown(&app, EXIT_FAILURE));
	if (!get_context_and_window(&app))
		return (shutdown(&app, EXIT_FAILURE));
	if (!init_opengl())
		return (shutdown(&app, EXIT_FAILURE));
	if (!compile_shader_program(
		&app.shader_program,
		"vertex_shader.vert",
		"fragment_shader.frag"
	))
		return (shutdown(&app, EXIT_FAILURE));
	if (!load_obj(&app, app.obj_file_name))
		return (shutdown(&app, EXIT_FAILURE));
	if (!load_buffer(&app))
		return (shutdown(&app, EXIT_FAILURE));
	if (app.texture_file_name)
	{
		if (!load_texture(&app))
			return (shutdown(&app, EXIT_FAILURE));
		glUniform1i(
			glGetUniformLocation(app.shader_program, "texture_provided"),
			1
		);
	}
	else
	{
		glUniform1i(
			glGetUniformLocation(app.shader_program, "texture_provided"),
			0
		);
	}
	glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	app.close_window = false;
	while (!app.close_window)
	{
		if (!handle_events(&app))
			(shutdown(&app, EXIT_FAILURE));
		handle_transformations(&app);
		// render
        // ------
        glClearColor(
			DEFAULT_CLEARCOLOR_RED,
			DEFAULT_CLEARCOLOR_GREEN,
			DEFAULT_CLEARCOLOR_BLUE,
			DEFAULT_CLEARCOLOR_ALPHA
		);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, app.texture);

        // draw our first triangle
        glUseProgram(app.shader_program);
        glBindVertexArray(app.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		if (app.indices_length > 0)
			glDrawElements(
				GL_TRIANGLES,
				app.indices_length,
				GL_UNSIGNED_INT,
				0
			);
		else
			glDrawArrays(GL_TRIANGLES, 0, app.vertices_length);
        // glBindVertexArray(0); // no need to unbind it every time
		SDL_GL_SwapWindow(app.sdl.window);
	}

	// optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &app.VAO);
    glDeleteBuffers(1, &app.VBO);
	if (app.indices_length > 0)
    	glDeleteBuffers(1, &app.EBO);
    glDeleteProgram(app.shader_program);

    return (shutdown(&app, EXIT_SUCCESS));
}
