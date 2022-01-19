#include "main.h"
#include "libmath.h"
#include "cglm.h"

void send_model_matrix(t_app *app)
{
	// t_mat4 output;
	// t_mat4 scaling;
	// t_mat4 rotation;
	// t_mat4 translation;

	// get_identity_mat4(&output);

	// //Add scaling to "output"
	// get_scaling_mat4(
	// 	&scaling,
	// 	app->orientation.scaling_x,
	// 	app->orientation.scaling_y,
	// 	app->orientation.scaling_z);
	// multiply_mat4(&output, &output, &scaling);

	// //Add rotation to "output"
	// get_rotation_mat4(
	// 	&rotation,
	// 	app->orientation.rotation_x,
	// 	app->orientation.rotation_y,
	// 	app->orientation.rotation_z);
	// multiply_mat4(&output, &output, &rotation);

	// //Add translation to "output"
	// get_translation_mat4(
	// 	&translation,
	// 	app->orientation.translation_x,
	// 	app->orientation.translation_y,
	// 	app->orientation.translation_z);
	// multiply_mat4(&output, &output, &translation);
	vec4 output[4];
	float translation[3];
	float rotation_axis[3];

	glm_mat4_identity(output);
	glm_vec3(
		(float[4]){
			app->orientation.translation_x,
			app->orientation.translation_y,
			app->orientation.translation_z,
			0.0f},
		translation);
	glm_translate(output, translation);
	glm_vec3(
		(float[4]){
			1.0f,
			0.3f,
			0.5f,
			0.0f},
		rotation_axis);
	glm_rotate(
		output,
		0.0f, //for testing with slight rotation, use e.g. 0.3490659f
		rotation_axis);

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
		DEFAULT_FOV,
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

void send_view_matrix(t_app *app)
{
	t_mat4 output;

	get_identity_mat4(&output); //appears unnecessary
	double radius = 10.0f;		//test-thing to turn circles
	unsigned long long time = SDL_GetTicks() / 100;
	double camX = sin((double)time) * radius; //test-thing to turn circles
	double camZ = cos((double)time) * radius; //test-thing to turn circles
	t_vec3 cam_pos;
	t_vec3 target;
	t_vec3 up;
	memcpy(cam_pos, (t_vec3){(float)camX, 0.0f, (float)camZ}, sizeof(t_vec3));
	memcpy(target, (t_vec3){0.0f, 0.0f, 0.0f}, sizeof(t_vec3));
	memcpy(up, (t_vec3){0.0f, 1.0f, 0.0f}, sizeof(t_vec3));
	get_lookat_mat4(
		&output,
		&(t_vec3){(float)camX, 0.0f, (float)camZ},
		&(t_vec3){0.0f, 0.0f, 0.0f},
		&(t_vec3){0.0f, 1.0f, 0.0f});

	glUseProgram(app->shader_program);
	glUniformMatrix4fv(
		glGetUniformLocation(app->shader_program, "viewmatrix"),
		1,
		GL_FALSE,
		(const GLfloat *)output);
}
