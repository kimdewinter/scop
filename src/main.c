#include "main.h"

static int shutdown(t_app *app, int exit_return)
{
	if (app->obj_file_name)
		free(app->obj_file_name);
	if (app->texture_file_name)
	{
		free(app->texture_file_name);
		glDeleteTextures(1, &app->texture);
	}
	if (app->vertices)
		free(app->vertices);
	if (app->indices)
		free(app->indices);
	glDeleteBuffers(1, &app->VBO);
	glDeleteVertexArrays(1, &app->VAO);
	if (app->indices_length > 0)
		glDeleteBuffers(1, &app->EBO);
	if (app->shader_program)
		glDeleteProgram(app->shader_program);
	shutdown_sdl(app);
	return (exit_return);
}

static inline void render(t_app *app)
{
	glClearColor(
		DEFAULT_CLEARCOLOR_RED,
		DEFAULT_CLEARCOLOR_GREEN,
		DEFAULT_CLEARCOLOR_BLUE,
		DEFAULT_CLEARCOLOR_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, app->texture);
	glUseProgram(app->shader_program);
	glBindVertexArray(app->VAO); //No need to bind it every time since there's only a single VAO
	if (app->indices_length > 0)
		glDrawElements(
			GL_TRIANGLES,
			app->indices_length,
			GL_UNSIGNED_INT,
			0);
	else
		glDrawArrays(GL_TRIANGLES, 0, app->vertices_length);
	//glBindVertexArray(0); //No need to unbind it every time since there's only a single VAO
	SDL_GL_SwapWindow(app->sdl.window);
}

int main(int argc, char const **const argv)
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
			VERTEX_SHADER_FILE_NAME,
			FRAGMENT_SHADER_FILE_NAME))
		return (shutdown(&app, EXIT_FAILURE));
	if (!load_obj(&app, app.obj_file_name))
		return (shutdown(&app, EXIT_FAILURE));
	if (!load_buffer(&app))
		return (shutdown(&app, EXIT_FAILURE));
	send_projection_matrix(&app);
	if (!load_texture(&app))
		return (shutdown(&app, EXIT_FAILURE));
	glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	app.close_window = false;
	while (!app.close_window)
	{
		if (!handle_events(&app))
			(shutdown(&app, EXIT_FAILURE));
		send_model_matrix(&app);
		// send_view_matrix(&app);
		render(&app);
	}
	return (shutdown(&app, EXIT_SUCCESS));
}
