#ifndef LIBMATH_H
#define LIBMATH_H

//Be mindful that an OpenGL matrix indexes up->down before left->right
typedef float t_mat4[16];

typedef float t_vec3[3];

void cross_product_vec3(float *dst, float *src1, float *src2);
void get_identity_mat4(t_mat4 *dst);
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

#endif
