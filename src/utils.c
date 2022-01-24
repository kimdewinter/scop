#include "main.h"
#include <float.h>

void set_uniform_bool(GLuint shader_program, const char *name, const bool value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), (int)value);
}

void set_uniform_int(GLuint shader_program, const char *name, const int value)
{
	glUniform1i(glGetUniformLocation(shader_program, name), value);
}

void set_uniform_float(GLuint shader_program, const char *name, const float value)
{
	glUniform1f(glGetUniformLocation(shader_program, name), value);
}

void center_object(t_obj_props *obj)
{
	obj->pos_x = 0.0f;
	obj->pos_y = 0.0f;
	obj->pos_z = 0.0f;
	obj->scaling_x = 0.0f;
	obj->scaling_y = 0.0f;
	obj->scaling_z = 0.0f;
	obj->rotation_x = 0.0f;
	obj->rotation_y = 0.0f;
	obj->rotation_z = 0.0f;
}

void reset_camera(t_cam_props *cam)
{
	cam->track_obj = false;
	cam->cam_pos_x = DEFAULT_CAM_POS_X;
	cam->cam_pos_y = DEFAULT_CAM_POS_Y;
	cam->cam_pos_z = DEFAULT_CAM_POS_Z;
	cam->cam_target_x = 0.0f;
	cam->cam_target_y = 0.0f;
	cam->cam_target_z = 0.0f;
	cam->cam_up_x = 0.0f;
	cam->cam_up_y = 1.0f;
	cam->cam_up_z = 0.0f;
}
