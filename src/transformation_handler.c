#include "main.h"
#include "libmath.h"

void send_model_matrix(t_app *app)
{
	t_mat4 output;
	t_mat4 scaling;
	t_mat4 rotation;
	t_mat4 translation;

	get_identity_mat4(&output);

	//Add scaling to "output"
	get_scaling_mat4(
		&scaling,
		app->orientation.scaling_x,
		app->orientation.scaling_y,
		app->orientation.scaling_z);
	multiply_mat4(&output, &output, &scaling);

	//Add rotation to "output"
	get_rotation_mat4(
		&rotation,
		app->orientation.rotation_x,
		app->orientation.rotation_y,
		app->orientation.rotation_z);
	multiply_mat4(&output, &output, &rotation);

	//Add translation to "output"
	get_translation_mat4(
		&translation,
		app->orientation.translation_x,
		app->orientation.translation_y,
		app->orientation.translation_z);
	multiply_mat4(&output, &output, &translation);

	//Send "output" to the shader program
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "modelmatrix"),
		1,
		GL_FALSE,
		output);
}

void send_projection_matrix(t_app *app)
{
	t_mat4 output;

	//Configure "output" as a projection matrix
	get_projection_mat4(
		&output,
		DEFAULT_FOV,
		DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT,
		0.1f,
		100.0f);

	//Send matrix to shader program
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "projectionmatrix"),
		1,
		GL_FALSE,
		output);
}

void send_view_matrix(t_app *app)
{
	t_mat4 output;

	get_identity_mat4(&output);
	float radius = 10.0f;
	float camX = sin(SDL_GetTicks() * radius);
	float camZ = cos(SDL_GetTicks() * radius);
	get_lookat_mat4(
		&output,
		&(t_vec3){camX, 0.0f, camZ},
		&(t_vec3){0.0f, 0.0f, 0.0f},
		&(t_vec3){0.0f, 1.0f, 0.0f});
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "viewmatrix"),
		1,
		GL_FALSE,
		output);
}
