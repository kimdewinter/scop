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
	t_vec3 cam_direction;

	//Get the necessary information to call get_lookat_mat4()
	app->camera.cam_pos[0] = 0.0f;
	app->camera.cam_pos[1] = 0.0f;
	app->camera.cam_pos[2] = 3.0f;

	app->camera.cam_target[0] = 0.0f;
	app->camera.cam_target[1] = 0.0f;
	app->camera.cam_target[2] = 0.0f;

	subtract_vec3(&cam_direction, &app->camera.cam_pos, &app->camera.cam_target);
	normalize_vec3(&cam_direction, &cam_direction);

	app->camera.cam_up[0] = 0.0f;
	app->camera.cam_up[1] = 1.0f;
	app->camera.cam_up[2] = 0.0f;

	cross_product_vec3(
		&app->camera.cam_right,
		&app->camera.cam_up,
		&cam_direction);
	normalize_vec3(&app->camera.cam_right, &app->camera.cam_right);

	get_lookat_mat4(
		&output,
		&app->camera.cam_right,
		&app->camera.cam_up,
		&cam_direction,
		&app->camera.cam_pos);

	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "viewmatrix"),
		1,
		GL_FALSE,
		output);

	//Add world space transformation to matrix
	// view_matrix = multiply_matrices(
	// 	view_matrix,
	// 	get_translation_matrix(
	// 		-app->obj_pos[0],
	// 		-app->obj_pos[1],
	// 		-app->obj_pos[2]));
}

//  send_view_matrix(t_app *app)
// {
// 	t_mat4 view_matrix = get_identity_matrix();
// 	float cam_direction[3];

// 	app->camera.cam_pos[0] = 0.0f;
// 	app->camera.cam_pos[1] = 0.0f;
// 	app->camera.cam_pos[2] = 3.0f;

// 	app->camera.cam_target[0] = 0.0f;
// 	app->camera.cam_target[1] = 0.0f;
// 	app->camera.cam_target[2] = 0.0f;

// 	cam_direction[0] = app->camera.cam_pos[0] - app->camera.cam_target[0];
// 	cam_direction[1] = app->camera.cam_pos[1] - app->camera.cam_target[1];
// 	cam_direction[2] = app->camera.cam_pos[2] - app->camera.cam_target[2];
// 	normalize_vector(&cam_direction, &cam_direction, 3);

// 	app->camera.cam_up[0] = 0.0f;
// 	app->camera.cam_up[1] = 1.0f;
// 	app->camera.cam_up[2] = 0.0f;

// 	cross_product_vectors(
// 		app->camera.cam_right,
// 		app->camera.cam_up,
// 		&cam_direction);
// 	normalize_vector(&app->camera.cam_right, &app->camera.cam_right, 3);

// 	//Add world space transformation to matrix
// 	view_matrix = multiply_matrices(
// 		view_matrix,
// 		get_translation_matrix(
// 			-app->obj_pos[0],
// 			-app->obj_pos[1],
// 			-app->obj_pos[2]));
// }
