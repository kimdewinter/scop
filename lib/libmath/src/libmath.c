#include "libmath.h"
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
                 0.0f, cos(x_deg), sin(x_deg), 0.0f,
                 0.0f, -sin(x_deg), cos(x_deg), 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
    //Create y rotation matrix
    memcpy(
        &y_mat,
        (t_mat4){cos(y_deg), 0.0f, -(sin(y_deg)), 0.0f,
                 0.0f, 1.0f, 0.0f, 0.0f,
                 sin(y_deg), 0.0f, cos(y_deg), 0.0f,
                 0.0f, 0.0f, 0.0f, 1.0f},
        sizeof(t_mat4));
    //Create z rotation matrix
    memcpy(
        &z_mat,
        (t_mat4){cos(z_deg), sin(z_deg), 0.0f, 0.0f,
                 -sin(z_deg), cos(z_deg), 0.0f, 0.0f,
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

//The caller must allocate the space for arg "dst"
//"dst" is allowed to be the same as "src"
void normalize_vec3(t_vec3 *dst, t_vec3 *src)
{
    assert(dst && src);
    float magnitude = sqrt(
        ((*src)[0] * (*src)[0]) +
        ((*src)[1] * (*src)[1]) +
        ((*src)[2] * (*src)[2]));
    if (magnitude == 0)
        memcpy(dst, src, sizeof(t_vec3));
    else
    {
        (*dst)[0] /= magnitude;
        (*dst)[1] /= magnitude;
        (*dst)[2] /= magnitude;
    }
}

//The caller must allocate the space for arg "dst"
//"dst" is allowed to be the same as "src1" or "src2"
void cross_product_vec3(
    t_vec3 *dst,
    t_vec3 *src1,
    t_vec3 *src2)
{
    assert(dst && src1 && src2);
    (*dst)[0] = (*src1)[1] * (*src2)[2] - (*src1)[2] * (*src2)[1];
    (*dst)[1] = (*src1)[2] * (*src2)[0] - (*src1)[0] * (*src2)[2];
    (*dst)[2] = (*src1)[0] * (*src2)[1] - (*src1)[1] * (*src2)[0];
}

//The caller must allocate the space for arg "dst"
//"dst" is allowed to be the same as "minuend" or "subtrahend"
void subtract_vec3(
    t_vec3 *dst,
    t_vec3 const *const minuend,
    t_vec3 const *const subtrahend)
{
    assert(dst && minuend && subtrahend);
    for (size_t i = 0; i < 3; i++)
        (*dst)[i] = (*minuend)[i] - (*subtrahend)[i];
}

void get_lookat_mat4(
    t_mat4 *dst,
    t_vec3 *cam_pos,
    t_vec3 *target,
    t_vec3 *up)
{
    t_vec3 forward;
    t_vec3 right;

    //Get axis from camera to target
    subtract_vec3(&forward, target, cam_pos);
    normalize_vec3(&forward, &forward);

    //Normalize up axis
    normalize_vec3(up, up);

    //Get axis to the right
    cross_product_vec3(&right, &forward, up);
    normalize_vec3(&right, &right);

    //Return the lookat matrix
    memset(dst, 0, sizeof(t_mat4));
    //top row
    (*dst)[0] = right[0];
    (*dst)[4] = right[1];
    (*dst)[8] = right[2];
    //second row
    (*dst)[1] = (*up)[0];
    (*dst)[5] = (*up)[1];
    (*dst)[9] = (*up)[2];
    //third row
    (*dst)[2] = -(forward[0]);
    (*dst)[6] = -(forward[1]);
    (*dst)[10] = -(forward[2]);
    //fourth row
    (*dst)[3] = -(
        right[0] * (*cam_pos)[0] +
        right[1] * (*cam_pos)[1] +
        right[2] * (*cam_pos)[2]);
    (*dst)[7] = -(
        (*up)[0] * (*cam_pos)[0] +
        (*up)[1] * (*cam_pos)[1] +
        (*up)[2] * (*cam_pos)[2]);
    (*dst)[11] = (forward[0] * (*cam_pos)[0] +
                  forward[1] * (*cam_pos)[1] +
                  forward[2] * (*cam_pos)[2]);
    (*dst)[15] = 1.0f;
}
