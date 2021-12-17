#include "libmath.h"
#include <math.h>
#include <stdlib.h>

int main(void)
{
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
}
