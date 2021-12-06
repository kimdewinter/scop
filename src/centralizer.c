#include "main.h"

static float find_highest(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float highest = vertices[starting_index];

    for (
        unsigned int i = starting_index + VERTEX_ATTRIBUTES;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        if (vertices[i] > highest)
            highest = vertices[i];
    }
    return (highest);
}

static float find_lowest(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float lowest = vertices[starting_index];

    for (
        unsigned int i = starting_index + VERTEX_ATTRIBUTES;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        if (vertices[i] < lowest)
            lowest = vertices[i];
    }
    return (lowest);
}

static float find_center(
    const float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    float lowest;
    float highest;

    lowest = find_lowest(vertices, vertices_length, starting_index);
    highest = find_highest(vertices, vertices_length, starting_index);
    return ((highest - lowest) / 2);
}

static void shift_attribute(
    const float shift_value,
    float *vertices,
    const unsigned int vertices_length,
    const unsigned int starting_index)
{
    for (
        unsigned int i = starting_index;
        i < vertices_length;
        i += VERTEX_ATTRIBUTES)
    {
        vertices[i] -= shift_value;
    }
}

static void shift_vertices(
    const float centers[VERTEX_ATTRIBUTES],
    float *vertices,
    const float vertices_length)
{
    for (int i = 0; i < VERTEX_ATTRIBUTES; i++)
        shift_attribute(centers[i], vertices, vertices_length, i);
}

void centralize(t_app *app)
{
    float centers[VERTEX_ATTRIBUTES];

    for (int i = 0; i < VERTEX_ATTRIBUTES; i++)
        centers[i] = find_center(app->vertices, app->vertices_length, i);
    shift_vertices(centers, app->vertices, app->vertices_length);
}
