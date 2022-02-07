#include "main.h"

//Selects one out of 8 shades of gray
static void copy_color(float dst[3], unsigned int const seed)
{
    switch (seed % 8)
    {
    case 0:
        convert_hex_to_float_color(dst, 220, 220, 220);
        return;
    case 1:
        convert_hex_to_float_color(dst, 211, 211, 211);
        return;
    case 2:
        convert_hex_to_float_color(dst, 192, 192, 192);
        return;
    case 3:
        convert_hex_to_float_color(dst, 169, 169, 169);
        return;
    case 4:
        convert_hex_to_float_color(dst, 128, 128, 128);
        return;
    case 5:
        convert_hex_to_float_color(dst, 105, 105, 105);
        return;
    case 6:
        convert_hex_to_float_color(dst, 119, 136, 153);
        return;
    case 7:
        convert_hex_to_float_color(dst, 112, 128, 144);
        return;
    }
}

//Convert single vertex from XYZ to XYZRGB
static void convert_vertex(
    float dst[6],
    float const src[3],
    unsigned int const seed)
{
    memcpy(dst, src, sizeof(float) * 3);
    copy_color(&dst[3], seed);
}

static void convert_face(
    float dst[18],
    float const src[9],
    unsigned int const seed)
{
    for (int i = 0; i < 3; i++)
        convert_vertex(&dst[i * 6], &src[i * 3], seed);
}

//Convert XYZ vertices array to XYZRGB
//A vertex had 3 floats, a face 9 (since a face has 3 vertices)
//Thus the new vertex has 6 floats, the new face 18
bool prepare_vertices(t_app *app)
{
    float *new;

    if (app->vertices_length % 3 != 0)
    {
        fprintf(stdout, "Error: vertices_length is not divisible by 3;\
        a face must have 3 vertices\n");
        return (false);
    }
    new = calloc(1, sizeof(float) * app->vertices_length * 2);
    if (!new)
    {
        fprintf(stdout, "Misallocation error in function prepare_vertices\n");
        return (false);
    }
    for (unsigned int i = 0; i * 9 < app->vertices_length - 8; i = i + 1)
        convert_face(&new[i * 18], &app->vertices[i * 9], i);
    free(app->vertices);
    app->vertices = new;
    app->vertices_length *= 2;
    return (true);
}
