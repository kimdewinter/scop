#ifndef LIBMATH_H
#define LIBMATH_H

//Be mindful that an OpenGL matrix indexes up->down before left->right
typedef float t_mat4[16];

void get_identity_mat4(t_mat4 *dst);
void get_scaling_mat4(t_mat4 *dst, float const x, float const y, float const z);
void get_rotation_mat4(
    t_mat4 *dst,
    float const x_deg,
    float const y_deg,
    float const z_deg);
void get_translation_mat4(
    t_mat4 *dst,
    float const x,
    float const y,
    float const z);
void multiply_mat4(
    t_mat4 *dst,
    t_mat4 const *const src1,
    t_mat4 const *const src2);

#endif
