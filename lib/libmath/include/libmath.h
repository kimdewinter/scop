#ifndef LIBMATH_H
#define LIBMATH_H

//WARNING: supplying bad parameters will cause assert() to abort your program

//Be mindful that an OpenGL matrix may index up->down before left->right
typedef float t_mat4[16];

typedef float t_vec3[3];

void cross_product_vec3(t_vec3 *dst, t_vec3 *src1, t_vec3 *src2);
void get_identity_mat4(t_mat4 *dst);
void get_lookat_mat4(
    t_mat4 *dst,
    t_vec3 const *const right,
    t_vec3 const *const up,
    t_vec3 const *const direction,
    t_vec3 const *const cam_pos);
void get_scaling_mat4(t_mat4 *dst, float const x, float const y, float const z);
void get_rotation_mat4(
    t_mat4 *dst,
    float const x_deg,
    float const y_deg,
    float const z_deg);
void get_projection_mat4(
    t_mat4 *dst,
    float const fov,
    float const aspect,
    float const near,
    float const far);
void get_translation_mat4(
    t_mat4 *dst,
    float const x,
    float const y,
    float const z);
void multiply_mat4(
    t_mat4 *dst,
    t_mat4 const *const src1,
    t_mat4 const *const src2);
void normalize_vec3(t_vec3 *dst, t_vec3 const *const src);
void subtract_vec3(
    t_vec3 *dst,
    t_vec3 const *const minuend,
    t_vec3 const *const subtrahend);

#endif