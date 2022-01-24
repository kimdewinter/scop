#include "main.h"
#include "libmath.h"
#include "cglm.h"

void send_view_matrix(t_app *app)
{
	t_mat4 output;

	get_lookat_mat4(
		&output,
		&(t_vec3){camX, camY, camZ},  // Camera position
		&(t_vec3){0.0f, 0.0f, 0.0f},  // Camera target position
		&(t_vec3){0.0f, 1.0f, 0.0f}); // Vector to sky/ceiling

	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "viewmatrix"),
		1,
		GL_FALSE,
		(const GLfloat *)output);
}

void send_model_matrix(t_app *app)
{
	t_mat4 output;
	t_mat4 translation;
	t_mat4 rotation;

	get_identity_mat4(&output);
	get_translation_mat4(
		&translation,
		app->orientation.translation_x,
		app->orientation.translation_y,
		app->orientation.translation_z);
	multiply_mat4(&output, &output, &translation);
	get_rotation_mat4(&rotation, 0.0f, 0.0f, radians(90));
	multiply_mat4(&output, &output, &rotation);

	//Send "output" to the shader program
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "modelmatrix"),
		1,
		GL_FALSE,
		(const GLfloat *)output);
}

void send_projection_matrix(t_app *app)
{
	t_mat4 output;

	// Configure "output" as a projection matrix
	get_projection_mat4(
		&output,
		radians(DEFAULT_FOV),
		DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT,
		PROJECTION_NEAR,
		PROJECTION_FAR);

	//Send matrix to shader program
	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "projectionmatrix"),
		1,
		GL_FALSE,
		(const GLfloat *)output);
}
