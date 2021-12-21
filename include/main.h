#ifndef MAIN_H

#define MAIN_H
#define PROGRAM_NAME "scop"
#define VERTEX_SHADER_FILE_NAME "vertex_shader.vert"
#define FRAGMENT_SHADER_FILE_NAME "fragment_shader.frag"
#define WIREFRAME_MODE 0
#define VERTEX_ATTRIBUTES 3
#define DEFAULT_SCREEN_WIDTH 1280
#define DEFAULT_SCREEN_HEIGHT 900
#define DEFAULT_FOV 70
#define DEFAULT_CLEARCOLOR_RED 0.0f
#define DEFAULT_CLEARCOLOR_GREEN 0.3f
#define DEFAULT_CLEARCOLOR_BLUE 0.3f
#define DEFAULT_CLEARCOLOR_ALPHA 1.0f

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#if __linux__
#include <glad.h>
#endif
#if __APPLE__
#include <OpenGL/gl3.h>
#endif

typedef struct s_sdl
{
	SDL_Window *window;
	SDL_GLContext context;
	SDL_Event event;
} t_sdl;

typedef struct s_orientation
{
	float scaling_x;
	float scaling_y;
	float scaling_z;
	float rotation_x;
	float rotation_y;
	float rotation_z;
	float translation_x;
	float translation_y;
	float translation_z;
} t_orientation;

typedef struct s_camera
{
	float cam_pos[3];
	float cam_target[3];
	float cam_right[3];
	float cam_up[3];
} t_camera;

typedef struct s_app
{
	char *obj_file_name;
	char *texture_file_name;
	GLuint texture;
	float *vertices;
	unsigned int vertices_length;
	unsigned int *indices;
	unsigned int indices_length;
	struct s_orientation orientation;
	float obj_pos[3];
	struct s_camera camera;
	bool close_window;
	GLuint VBO; //Vertex Buffer Object
	GLuint VAO; //Vertex Buffer Array
	GLuint EBO; //Element Buffer Object
	GLuint shader_program;
	struct s_sdl sdl;
} t_app;

void centralize(t_app *app);
bool compile_shader_program(
	GLuint *shader_program,
	const char *vertex_shader_filename,
	const char *fragment_shader_filename);
bool get_context_and_window(t_app *app);
bool handle_events(t_app *app);
bool init_opengl(void);
bool is_float(char *const str);
bool load_buffer(t_app *app);
bool load_indices(t_app *app);
bool load_obj(t_app *app, char const *const file_name);
bool load_texture(t_app *app);
bool load_vertices(t_app *app, char const *const file_name);
bool parse_main_args(t_app *app, const int argc, char const **const argv);
char *file_to_string(char const *const file_name);
char *skip_float(char *const str);
void send_model_matrix(t_app *app);
void send_projection_matrix(t_app *app);
void send_view_matrix(t_app *app);
void set_uniform_bool(GLuint shader_program, const char *name, const bool value);
void set_uniform_float(GLuint shader_program, const char *name, const float value);
void set_uniform_int(GLuint shader_program, const char *name, const int value);
void shutdown_sdl(t_app *app);
#ifdef DEBUG
void print_opengl_info(void);
#endif

#endif
