#include "main.h"
#include "libmath.h"

void send_view_matrix(t_app *app)
{
	t_mat4 output;

	get_lookat_mat4(
		&output,
		&(t_vec3){
			app->cam_props.cam_pos_x,
			app->cam_props.cam_pos_y,
			app->cam_props.cam_pos_z}, // Camera position
		&(t_vec3){
			app->cam_props.track_obj ? app->obj_props.pos_x : 0.0f,
			app->cam_props.track_obj ? app->obj_props.pos_y : 0.0f,
			app->cam_props.track_obj ? app->obj_props.pos_z : 0.0f}, // Cam target
		&(t_vec3){0.0f, 1.0f, 0.0f});								 // Vector to sky/ceiling

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
	t_mat4 scaling;
	t_mat4 translation;
	t_mat4 rotation;

	get_identity_mat4(&output);
	get_scaling_mat4(
		&scaling,
		app->obj_props.scaling_x,
		app->obj_props.scaling_y,
		app->obj_props.scaling_z);
	multiply_mat4(&output, &output, &scaling);
	get_translation_mat4(
		&translation,
		app->obj_props.pos_x,
		app->obj_props.pos_y,
		app->obj_props.pos_z);
	multiply_mat4(&output, &output, &translation);
	get_rotation_mat4(
		&rotation,
		app->obj_props.rotation_x,
		app->obj_props.rotation_y,
		app->obj_props.rotation_z);
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
