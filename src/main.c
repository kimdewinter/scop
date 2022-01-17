#include "main.h"
#include "libmath.h"
#include "cglm.h"

static int shutdown(t_app *app, int exit_return)
{
	if (app->obj_file_name)
		free(app->obj_file_name);
	if (app->vertices)
		free(app->vertices);
	if (app->indices)
		free(app->indices);
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
	t_vec3 result1;
	subtract_vec3(&result1, &(t_vec3){0.0f, 0.0f, 0.0f}, &(t_vec3){0.5f, 0.0f, 0.5f});
	printf("libmath isolated subtract test output:");
	printf("%f\t%f\t%f\n", result1[0], result1[1], result1[2]);

	t_vec3 result2;
	glm_vec3_sub((t_vec3){0.0f, 0.0f, 0.0f}, (t_vec3){0.5f, 0.0f, 0.5f}, (float *)&result2);
	printf("cglm isolated subtract test output:");
	printf("%f\t%f\t%f\n", result2[0], result2[1], result2[2]);
	printf("\n");

	normalize_vec3(&result1, &result1);
	printf("libmath isolated normalize test output:");
	printf("%f\t%f\t%f\n", result1[0], result1[1], result1[2]);

	glm_vec3_normalize((float *)&result2);
	printf("cglm isolated normalize test output:");
	printf("%f\t%f\t%f\n", result2[0], result2[1], result2[2]);
	printf("\n");

	t_mat4 lmath_output;
	get_identity_mat4(&lmath_output);
	get_lookat_mat4(
		&lmath_output,
		&(t_vec3){0.5f, 0.0f, 0.5f},
		&(t_vec3){0.0f, 0.0f, 0.0f},
		&(t_vec3){0.0f, 1.0f, 0.0f});
	printf("lmath output:\n");
	printf("%f\t%f\t%f\t%f\n", lmath_output[0], lmath_output[4], lmath_output[8], lmath_output[12]);
	printf("%f\t%f\t%f\t%f\n", lmath_output[1], lmath_output[5], lmath_output[9], lmath_output[13]);
	printf("%f\t%f\t%f\t%f\n", lmath_output[2], lmath_output[6], lmath_output[10], lmath_output[14]);
	printf("%f\t%f\t%f\t%f\n", lmath_output[3], lmath_output[7], lmath_output[11], lmath_output[15]);
	printf("\n");

	vec4 output[4];
	vec3 eye;
	vec3 center;
	vec3 up;

	glm_mat4_identity(output);
	glm_vec3((float[4]){0.5f, 0.0f, 0.5f, 0.0f}, eye);
	glm_vec3((float[4]){0.0f, 0.0f, 0.0f, 0.0f}, center);
	glm_vec3((float[4]){0.0f, 1.0f, 0.0f, 0.0f}, up);
	glm_lookat(eye, center, up, output);
	printf("glm output:\n");
	printf("%f\t%f\t%f\t%f\n", output[0][0], output[1][0], output[2][0], output[3][0]);
	printf("%f\t%f\t%f\t%f\n", output[0][1], output[1][1], output[2][1], output[3][1]);
	printf("%f\t%f\t%f\t%f\n", output[0][2], output[1][2], output[2][2], output[3][2]);
	printf("%f\t%f\t%f\t%f\n", output[0][3], output[1][3], output[2][3], output[3][3]);
	exit(EXIT_SUCCESS);

	t_app app;

#if __linux__
	gladLoadGLLoader(SDL_GL_GetProcAddress);
#endif
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
		send_view_matrix(&app);
		send_model_matrix(&app);
		render(&app);
	}
	return (shutdown(&app, EXIT_SUCCESS));
}
