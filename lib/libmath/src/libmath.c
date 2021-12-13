#include "../include/libmath.h"
#include <string.h>
#include <assert.h>
#include <math.h>

//The caller must allocate the space for arg "dst"
void get_identity_mat4(t_mat4 *dst)
{
    assert(dst);
    memcpy(
        dst,
        (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
}

//The caller must allocate the space for arg "dst"
void get_scaling_mat4(t_mat4 *dst, float const x, float const y, float const z)
{
    assert(dst);
    memcpy(
        dst,
        (t_mat4){1.0f + x, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f + y, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f + z, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
}

//The caller must allocate the space for arg "dst"
void get_rotation_mat4(
    t_mat4 *dst,
    float const x_deg,
    float const y_deg,
    float const z_deg)
{
    t_mat4 x_mat;
    t_mat4 y_mat;
    t_mat4 z_mat;
    t_mat4 intermediate_mat;

    assert(dst);
    //Create x rotation matrix
    memcpy(
        &x_mat,
        (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, (float)cos((double)x_deg), (float)sin((double)x_deg), 0.0f,
                 0.0f, (float)(-(sin((double)x_deg))), (float)cos((double)x_deg), 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
    //Create y rotation matrix
    memcpy(
        &y_mat,
        (t_mat4){(float)cos((double)y_deg), 0.0f, (float)(-(sin((double)y_deg))), 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 (float)sin((double)y_deg), 0.0f, (float)cos((double)y_deg), 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
    //Create z rotation matrix
    memcpy(
        &z_mat,
        (t_mat4){(float)cos((double)z_deg), (float)sin((double)z_deg), 0.0f, 0.0f,
                 (float)(-(sin((double)z_deg))), (float)cos((double)z_deg), 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
    //Combine the matrices and output to "dst"
    multiply_mat4(&intermediate_mat, &x_mat, &y_mat);
    multiply_mat4(dst, &intermediate_mat, &z_mat);
}

//The caller must allocate the space for arg "dst"
void get_translation_mat4(
    t_mat4 *dst,
    float const x,
    float const y,
    float const z)
{
    assert(dst);
    memcpy(
        dst,
        (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 0.0f, 0.0f, 1.0f, 0.0f,
                 0.0f + x, 0.0f + y, 0.0f + z, 1.0f},
        sizeof(t_mat4));
}

//The caller must allocate the space for arg "dst"
void get_projection_mat4(
    t_mat4 *dst,
    float const fov,
    float const aspect,
    float const near,
    float const far)
{
    float f = (float)tan(fov / 2.0f);

    assert(dst);
    memcpy(
        dst,
        (t_mat4){1.0f / (f * aspect), 0.0f, 0.0f, 0.0f,
                 0.0f, 1.0f / f, 0.0f, 0.0f,
                 0.0f, 0.0f, -(far + near) / (far - near), -1.0f,
                 0.0f, 0.0f, -(2.0f * far * near) / (far - near), 1.0f},
        sizeof(t_mat4));
}

//The caller must allocate the space for arg "dst"
//"dst" is allowed to be the same as "src1" or "src2"
void multiply_mat4(
    t_mat4 *dst,
    t_mat4 const *const src1,
    t_mat4 const *const src2)
{
    t_mat4 output;

    assert(dst && src1 && src2);
    memset(&output, 0, sizeof(t_mat4));
    for (unsigned int y = 0; y < 4; y++)
        for (unsigned int x = 0; x < 4; x++)
            for (unsigned int i = 0; i < 4; i++)
            {
                output[y * 4 + x] +=
                    (*src1)[y * 4 + i] * (*src2)[i * 4 + x];
            }
    memcpy(dst, &output, sizeof(t_mat4));
}

void normalize_vec3(t_vec3 *dst, t_vec3 const *const src)
{
    float mod = 0.0f;
    double magnitude;

    assert(dst && src);
    for (size_t i = 0; i < 3; ++i)
        mod += (*src)[i] * (*src)[i];
    magnitude = sqrt(mod);
    for (size_t i = 0; i < 3; ++i)
        (*dst)[i] = (*src)[i] / magnitude;
}

void cross_product_vec3(float *dst, float *src1, float *src2)
{
    assert(dst && src1 && src2);
    dst[0] = src1[1] * src2[2] - src1[2] * src2[1];
    dst[1] = src1[2] * src2[0] - src1[0] * src2[2];
    dst[2] = src1[0] * src2[1] - src1[1] * src2[0];
}
