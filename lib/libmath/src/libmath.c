#include "../include/libmath.h"
#include <string.h>
#include <assert.h>
#include <math.h>

//The caller must allocate the space for arg "dst"
void get_identity_mat4(t_mat4 *dst)
{
    assert(dst);
    memset(dst, 0, sizeof(t_mat4));
    (*dst)[0] += 1.0f;
    (*dst)[5] += 1.0f;
    (*dst)[10] += 1.0f;
    (*dst)[15] += 1.0f;
    // memcpy(
    //     dst,
    //     (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
    //              0.0f, 1.0f, 0.0f, 0.0f,
    //              0.0f, 0.0f, 1.0f, 0.0f,
    //              0.0f, 0.0f, 0.0f, 1.0f},
    //     sizeof(t_mat4));
}

//The caller must allocate the space for arg "dst"
void get_scaling_mat4(t_mat4 *dst, float const x, float const y, float const z)
{
    assert(dst);
    get_identity_mat4(dst);
    (*dst)[0] += x;
    (*dst)[5] += y;
    (*dst)[10] += z;
    // memcpy(
    //     dst,
    //     (t_mat4){1.0f + x, 0.0f, 0.0f, 0.0f,
    //              0.0f, 1.0f + y, 0.0f, 0.0f,
    //              0.0f, 0.0f, 1.0f + z, 0.0f,
    //              0.0f, 0.0f, 0.0f, 1.0f},
    //     sizeof(t_mat4));
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
    get_identity_mat4(&x_mat);
    x_mat[5] = cos((double)x_deg);
    x_mat[6] = sin((double)x_deg);
    x_mat[9] = -sin((double)x_deg);
    x_mat[10] = cos((double)x_deg);
    // memcpy(
    //     &x_mat,
    //     (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
    //              0.0f, (float)cos((double)x_deg), (float)sin((double)x_deg), 0.0f,
    //              0.0f, (float)(-(sin((double)x_deg))), (float)cos((double)x_deg), 0.0f,
    //              0.0f, 0.0f, 0.0f, 1.0f},
    //     sizeof(t_mat4));

    //Create y rotation matrix
    get_identity_mat4(&y_mat);
    y_mat[0] = cos((double)y_deg);
    y_mat[2] = -sin((double)y_deg);
    y_mat[8] = sin((double)y_deg);
    y_mat[10] = cos((double)y_deg);
    // memcpy(
    //     &y_mat,
    //     (t_mat4){(float)cos((double)y_deg), 0.0f, (float)(-(sin((double)y_deg))), 0.0f,
    //              0.0f, 1.0f, 0.0f, 0.0f,
    //              (float)sin((double)y_deg), 0.0f, (float)cos((double)y_deg), 0.0f,
    //              0.0f, 0.0f, 0.0f, 1.0f},
    //     sizeof(t_mat4));

    //Create z rotation matrix
    get_identity_mat4(&z_mat);
    z_mat[0] = cos((double)z_deg);
    z_mat[1] = sin((double)z_deg);
    z_mat[4] = -sin((double)z_deg);
    z_mat[5] = cos((double)z_deg);
    // memcpy(
    //     &z_mat,
    //     (t_mat4){(float)cos((double)z_deg), (float)sin((double)z_deg), 0.0f, 0.0f,
    //              (float)(-(sin((double)z_deg))), (float)cos((double)z_deg), 0.0f, 0.0f,
    //              0.0f, 0.0f, 1.0f, 0.0f,
    //              0.0f, 0.0f, 0.0f, 1.0f},
    //     sizeof(t_mat4));

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
    get_identity_mat4(dst);
    (*dst)[12] += x;
    (*dst)[13] += y;
    (*dst)[14] += z;
    // memcpy(
    //     dst,
    //     (t_mat4){1.0f, 0.0f, 0.0f, 0.0f,
    //              0.0f, 1.0f, 0.0f, 0.0f,
    //              0.0f, 0.0f, 1.0f, 0.0f,
    //              0.0f + x, 0.0f + y, 0.0f + z, 1.0f},
    //     sizeof(t_mat4));
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

// #include <stdio.h>

// int main(void)
// {
//     t_mat4 test1;
//     t_mat4 test2;

//     get_identity_mat4(&test1);
//     get_identity_mat4(&test2);
//     test1[1] = 3.0f;
//     test2[1] = 2.0f;
//     multiply_mat4(&test2, &test1, &test2);
//     for (int i = 0; i < 16; i++)
//     {
//         printf("#%i is: %f\n", i, (double)test2[i]);
//     }
//     return (0);
// }