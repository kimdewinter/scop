#include "libmath.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    t_mat4 output;
    get_identity_mat4(&output);
    get_lookat_mat4(
        &output,
        &(t_vec3){0.5, 0.0f, 0.5f},
        &(t_vec3){0.0f, 0.0f, 0.0f},
        &(t_vec3){0.0f, 1.0f, 0.0f});
    printf("%f\t%f\t%f\t%f\n", output[0], output[4], output[8], output[12]);
    printf("%f\t%f\t%f\t%f\n", output[1], output[5], output[9], output[13]);
    printf("%f\t%f\t%f\t%f\n", output[2], output[6], output[10], output[14]);
    printf("%f\t%f\t%f\t%f\n", output[3], output[7], output[11], output[15]);
    exit(EXIT_SUCCESS);
    /*
    t_mat4 output;
    get_identity_mat4(&output);
    // float radius = 10.0f;
    // float camX = sin(420 * radius);
    // float camZ = cos(420 * radius);
    t_vec3 a = {0.1f, 0.0f, 0.1f};
    t_vec3 b = {0.0f, 0.0f, 0.0f};
    t_vec3 c = {0.0f, 1.0f, 0.0f};
    get_lookat_mat4(
        &output,
        &a,
        &b,
        &c);
    return (EXIT_SUCCESS);
*/
}
